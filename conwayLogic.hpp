#include <tuple>

int conwayKernel(int **board, std::tuple<int, int> &loc, std::tuple<int, int> &boardShape)
{
    int iMinLoc = std::get<0>(loc) - 1;
    iMinLoc = iMinLoc < 0 ? 0 : iMinLoc;

    int iMaxLoc = std::get<0>(loc) + 1;
    iMaxLoc = iMaxLoc <= std::get<0>(boardShape) ? std::get<0>(boardShape) : iMaxLoc;

    int jMinLoc = std::get<1>(loc) - 1;
    jMinLoc = jMinLoc < 0 ? 0 : iMinLoc;

    int jMaxLoc = std::get<1>(loc) + 1;
    jMaxLoc = jMaxLoc <= std::get<1>(boardShape) ? std::get<1>(boardShape) : jMaxLoc;

    int neighborCount = 0;
    for (int i = iMinLoc; i < iMaxLoc; i++)
    {
        for (int j = jMinLoc; j < jMaxLoc; j++)
        {
            neighborCount += board[i][j];
        }
    }
    int isAlive = board[std::get<0>(loc)][std::get<1>(loc)];
    if (isAlive)
    {
        return 3 <= neighborCount && neighborCount <= 4;
    }
    return neighborCount == 3;
}
