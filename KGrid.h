#ifndef __ERLINGSIBA_KGRID_H_
#define __ERLINGSIBA_KGRID_H_
#include<stdlib.h>
#include<time.h>

class KGrid
{
public:
    KGrid(const int& nNum);
    //初始为零
    KGrid();
    //随机生成
    void SetGridAuto();

    int GetNum()const;

    void SetNum(int num);

private:
    int m_nNum;

};
#endif
