#include "io.hpp"

#include <vector>
#include <cereal/cereal.hpp>

using namespace std;

#define MAX_BUFFER_SIZE (256 * 256 * 16)

struct PlayResponse
{
    vector<double> samples;

    template <class Archive>
    void serialize(Archive &archive)
    {
        archive(CEREAL_NVP(samples));
    }
};

static PlayResponse g_response;
static int g_buffer_size;

/* インライン関数にしたい */

void initPlay(vector<string> &args)
{
    if (args.size() < 3)
    {
        throw runtime_error("構文: play デルタ時間[s] サンプル数");
    }

    int request_buffer_size = stoi(args[2]);
    if (request_buffer_size < 0 || request_buffer_size > MAX_BUFFER_SIZE)
    {
        throw runtime_error("サンプル数の範囲オーバーです。");
    }
    g_buffer_size = request_buffer_size;

    g_response.samples.clear();
}

bool isContinuePlay()
{
    return g_response.samples.size() < g_buffer_size;
}

void storePlay(double sample)
{
    g_response.samples.push_back(sample);
}

void respondPlay()
{
    respond(g_response);
}
