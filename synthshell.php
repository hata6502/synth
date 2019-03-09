<?php
stream_set_blocking(STDIN, false);
$synthcore = proc_open('./synthcore', [
    '0' => ['pipe', 'r'],   // stdin
    '1' => ['pipe', 'w'],   // stdout
    '2' => ['pipe', 'w']    // stderr
], $pipes);

if (is_resource($synthcore)) {
    $stdin = $pipes[0];
    $stdout = $pipes[1];
    $stderr = $pipes[2];
    stream_set_blocking($stdout, false);
    stream_set_blocking($stderr, false);

    $commandStr = "";
    $responseJson = "";
    while (!feof(STDIN)) {
        while (($ch = fgetc(STDIN))!==false) {
            if ($ch == "\n") {
                $args = preg_split("/\s/", $commandStr, -1, PREG_SPLIT_NO_EMPTY);
                $commandStr = "";
                execute($args);
            } else {
                $commandStr .= $ch;
            }
        }

        while (($ch = fgetc($stdout))!==false) {
            if ($ch == "\0") {
                print_r(json_decode($responseJson));
                $responseJson = "";
            } else {
                $responseJson .= $ch;
            }
        }

        echo stream_get_contents($stderr);
        usleep(10000);
    }

    fclose($stdin);
    fclose($stdout);
    fclose($stderr);
    proc_close($synthcore);
}

function execute($args)
{
    global $stdin;

    fwrite($stdin, json_encode(['request' => ['args' => $args]])."\0");
}
