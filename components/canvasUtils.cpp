#include <cheerp/client.h>
std::tuple<int, int> idToArr(client::String *id)
{
    int comma = id->indexOf(",");
    int y = parseInt(id->slice(0, comma));
    int x = parseInt(id->slice(comma + 1));
    return std::make_tuple(x, y);
}

void freeIfInit(double **matrix, char isInit, int rows)
{
    if (!isInit)
    {
        return;
    }
    for (int i = 0; i < rows; free(matrix[i++]))
        ;
}
