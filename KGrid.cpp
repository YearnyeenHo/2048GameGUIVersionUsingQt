#include"KGrid.h"

KGrid::KGrid(const int& nNum)
{
    m_nNum = nNum;
}

//初始为零
KGrid::KGrid()
{
    this->m_nNum = 0;
}
//随机生成
void KGrid::SetGridAuto()
{
    srand(time(NULL));
    if(rand()%1 < 0.5)
    {
        m_nNum = 2;
    }
    else
    {
        m_nNum = 4;
    }
}

int KGrid::GetNum()const
{
    return m_nNum;
}
void KGrid::SetNum(int num)
{
    this->m_nNum = num;
}


