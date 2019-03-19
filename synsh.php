<?php
$synthcore = proc_open(dirname(__FILE__).'/synth', [
    '0' => ['pipe', 'r'],   // stdin
    '1' => ['pipe', 'w'],   // stdout
    '2' => ['pipe', 'w']    // stderr
], $pipes);

if (is_resource($synthcore)) {
    $stdin = $pipes[0];
    $stdout = $pipes[1];
    $stderr = $pipes[2];
    stream_set_blocking($stderr, false);

    $g_comNameTable = [];

    while (($commandStr = readline('> '))!==false) {
        echo stream_get_contents($stderr);
        readline_add_history($commandStr);
        $commandStr = preg_replace('/#.*/', '', $commandStr);
        $args = preg_split('/\s/', $commandStr, -1, PREG_SPLIT_NO_EMPTY);
        execute($args);
    }

    fclose($stdin);
    fclose($stdout);
    fclose($stderr);
    proc_close($synthcore);
}

function send($args, $onSuccess)
{
    global $stdin;
    global $stdout;
    global $stderr;

    fwrite($stdin, json_encode(['request' => ['args' => $args]])."\0");

    echo stream_get_contents($stderr);
    $responseJson = "";
    while (($ch = fgetc($stdout))!=="\0") {
        $responseJson .= $ch;
    }
    $response = json_decode($responseJson)->response;

    if (isset($response->error)) {
        echo $response->error."\n";
        return;
    }

    $onSuccess($response);
}

function isName($arg)
{
    return preg_match('/^[a-z_][0-9a-z_]*$/', $arg)===1;
}

function execute($args)
{
    // addcom (component type) as (name)
    if (count($args)==4 && $args[0]=='addcom' && $args[2]=='as' && isName($args[3])) {
        $name = $args[3];
        unset($args[2]);
        unset($args[3]);

        send($args, function ($response) use ($name) {
            $uuid = $response->uuid;

            send(['lsport', $uuid], function ($response) use ($name, $uuid) {
                $inputs = [];
                foreach ($response->inputs as $input) {
                    $inputs[$input->type] = $input->uuid;
                }

                $outputs = [];
                foreach ($response->outputs as $output) {
                    $outputs[$output->type] = $output->uuid;
                }

                $g_comNameTable[$name] = [
                    'uuid' => $uuid,
                    'inputs' => $inputs,
                    'outputs' => $outputs,
                ];
            });
        });
    }
    // default
    else {
        send($args, function ($response) {
            printResponse($response, 0);
        });
    }
}

function printResponse($response, $level)
{
    foreach ($response as $key => $value) {
        for ($i = 0; $i < $level; $i++) {
            echo " ";
        }
        echo "${key}: ";
        if (is_array($value) || is_object($value)) {
            echo "\n";
            printResponse($value, $level + 2);
        } else {
            echo print_r($value, true)."\n";
        }
    }
}
