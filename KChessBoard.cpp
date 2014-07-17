#define UP 2
#define DOWN 4
#define LEFT 1
#define RIGHT 3
#include<stdlib.h>
#include<time.h>
#include<stdio.h>
#include"KChessBoard.h"
KChessBoard::KChessBoard()
{
    m_ppChessboard = NULL;
    m_nEdgeSize = 4;//四个格子
}

KChessBoard::KChessBoard(const KChessBoard &cb)
{
    this->Init();
    for(int i = 0; i < cb.GetEdgeSize(); ++i)
    {
        for(int j = 0; j < cb.GetEdgeSize(); ++j)
        {
             this->m_ppChessboard[i][j].SetNum(cb.GetGrid(i,j).GetNum());
        }

    }
}


KChessBoard::~KChessBoard()
{

}

bool KChessBoard::Init()
{
   if(m_ppChessboard != NULL)
   {
       UnInit();

   }
    m_ppChessboard = new KGrid * [this->GetEdgeSize()];
    if(m_ppChessboard)
    {


        int i = 0;

        while(i < GetEdgeSize())
        {
            m_ppChessboard[i] = new KGrid[this->GetEdgeSize()];
            if(NULL == m_ppChessboard[i])
                return false;

            i++;
        }
        int i1,i2,j1,j2;

        srand((unsigned)time(NULL));
        do{
            i1 = rand()%m_nEdgeSize;
            i2 = rand()%m_nEdgeSize;
            j1 = rand()%m_nEdgeSize;
            j2 = rand()%m_nEdgeSize;
        }while((i1 == i2) && (j1 == j2));

        i = 0;
        while(i < m_nEdgeSize)
        {
            int j = 0;
            while(j < m_nEdgeSize)
            {
                if((i == i1 && j == j1)||(i == i2 && j == j2))
                {
                    m_ppChessboard[i][j].SetGridAuto();
                }
                else
                {
                    m_ppChessboard[i][j].SetNum(0);
                }
                ++j;
            }
            ++i;
        }
        return true;
    }
    return false;

}
bool KChessBoard::UnInit()
{
    if(m_ppChessboard != NULL)
    {
        for(int i = 0; i < m_nEdgeSize; i++)
        {

            delete[] m_ppChessboard[i];

            m_ppChessboard[i] = NULL;
        }
        delete[] m_ppChessboard;
        m_ppChessboard = NULL;

    }
    return true;


}

void KChessBoard::Print()
{
    int i = 0;
    while(i < m_nEdgeSize)
    {
        int j = 0;
        while(j < m_nEdgeSize)
        {

            if(m_ppChessboard[i][j].GetNum() > 10)
                printf("%d ", m_ppChessboard[i][j].GetNum());
            else
                printf("%d  ", m_ppChessboard[i][j].GetNum());

            ++j;
        }
        printf("\n");
        ++i;
    }
    printf("UP:W, DOWN:S, LEFT:A,RIGHT:D.PRESS OTHER KEY TO EXIT");
}

void KChessBoard::SetChessboardGrid(int iPos, int jPos, int num)
{
    m_ppChessboard[iPos][jPos].SetNum(num);
}
bool KChessBoard::IsPosZero(int i, int j)
{

   return (CheckBorder(i) && CheckBorder(j)&&m_ppChessboard[i][j].GetNum() == 0);


}
KGrid KChessBoard::GetGrid(int i, int j)const
{
    return m_ppChessboard[i][j];

}
void KChessBoard::SetGridAuto(int i,int j)
{
    m_ppChessboard[i][j].SetGridAuto();

}
bool KChessBoard::CheckBorder(int i)
{
    if(i >= 0 && i < m_nEdgeSize)
        return true;

        return false;
}

bool KChessBoard::IsEqualsNeighbor(int i, int j,int direction)
{
     bool bIsEqual = false;

    if(!CheckBorder(i) || !CheckBorder(j))
        return bIsEqual;
    int t = m_ppChessboard[i][j].GetNum();

    switch(direction)
    {
    case UP:
        if(CheckBorder(i + 1))
        {
            if(m_ppChessboard[i + 1][j].GetNum() == t)
                bIsEqual = true;
        }

        break;

    case DOWN:
        if(CheckBorder(i - 1))
        {
            if(m_ppChessboard[i - 1][j].GetNum() == t)
                bIsEqual = true;
        }

         break;

    case LEFT:
        if(CheckBorder(j + 1))
        {
            if(m_ppChessboard[i][j + 1].GetNum() == t)
                bIsEqual = true;
        }

         break;

    case RIGHT:
        if(CheckBorder(j - 1))
        {
            if(m_ppChessboard[i][j - 1].GetNum() == t)//考察左边的格子
                bIsEqual = true;
        }

        break;
    }
     return bIsEqual;
}
void KChessBoard::MergeGridAndSetZero(int i, int j, int direction)
{
    if(!CheckBorder(i) || !CheckBorder(j))
        return;

    switch(direction)
    {
    case UP:
        if(IsEqualsNeighbor(i, j, UP))
        {
            m_ppChessboard[i][j].SetNum(m_ppChessboard[i][j].GetNum() + m_ppChessboard[i + 1][j].GetNum());//与下方合并
            m_ppChessboard[i + 1][j].SetNum(0);//将正下方清空
        }
        break;
    case DOWN:
        if(IsEqualsNeighbor(i, j, DOWN))
        {
            m_ppChessboard[i][j].SetNum(m_ppChessboard[i][j].GetNum() + m_ppChessboard[i - 1][j].GetNum());
            m_ppChessboard[i - 1][j].SetNum(0);

        }
        break;
    case LEFT:
        if(IsEqualsNeighbor(i, j, LEFT))
        {
            m_ppChessboard[i][j].SetNum(m_ppChessboard[i][j].GetNum() + m_ppChessboard[i][j + 1].GetNum());
            m_ppChessboard[i][j + 1].SetNum(0);
        }
        break;
    case RIGHT:
        if(IsEqualsNeighbor(i, j, RIGHT))
        {
            m_ppChessboard[i][j].SetNum(m_ppChessboard[i][j].GetNum() + m_ppChessboard[i][j - 1].GetNum());
            m_ppChessboard[i][j - 1].SetNum(0);
        }
        break;
    default:
        break;

    }
}
//移到最尽
void KChessBoard::MoveToNextPossible(int iPos, int jPos, int direction)
{
    int tnum = m_ppChessboard[iPos][jPos].GetNum();
    int j = jPos;
    int i = iPos;
    switch(direction)
    {

    case UP:

        while(IsPosZero(--i, jPos) && i >= 0)
        {

        }
        if((i + 1) != iPos)
        {
            m_ppChessboard[i + 1][jPos].SetNum(tnum);
            m_ppChessboard[iPos][jPos].SetNum(0);
        }
        break;
    case DOWN:

        while(IsPosZero(++i, jPos) && i < m_nEdgeSize)
        {

        }

        if((i - 1) != iPos)
        {
            m_ppChessboard[i - 1][jPos].SetNum(tnum);
            m_ppChessboard[iPos][jPos].SetNum(0);
        }
        break;
    case LEFT:

        while(IsPosZero(iPos, --j) && j >= 0)
        {

        }
        if((j + 1) != jPos)
        {
            m_ppChessboard[iPos][j + 1].SetNum(tnum);
            m_ppChessboard[iPos][jPos].SetNum(0);
        }
        break;
    case RIGHT:

        while(IsPosZero(iPos, ++j) && j < m_nEdgeSize)
        {

        }
        if((j - 1) != jPos)
        {
            m_ppChessboard[iPos][j - 1].SetNum(tnum);
            m_ppChessboard[iPos][jPos].SetNum(0);
        }
        break;
    default:
        break;

    }

}
void  KChessBoard::SetChessboard(KChessBoard cb)
{
    for(int i = 0; i < m_nEdgeSize; ++i)
    {
        for(int j = 0; j < m_nEdgeSize; ++j)
        {
            SetChessboardGrid(i, j, cb.GetGrid(i,j).GetNum());

        }


    }


}
int KChessBoard::CurrentScore()
{
    int count = 0;
    for(int i = 0; i < m_nEdgeSize; ++i)
    {  for(int j = 0; j < m_nEdgeSize; ++j)
    {
        if(m_ppChessboard[i][j].GetNum() == 2048)
            ++count;
    }
    }
    return count;
}
bool KChessBoard::IsHasEmptyGrid()
{
    for(int i = 0; i < m_nEdgeSize; ++i)
    {
        for(int j = 0; j < m_nEdgeSize; ++j)
        {
            if(m_ppChessboard[i][j].GetNum() == 0)

                return true;
        }
    }
    return false;

}
bool KChessBoard::CheckRules()
{
    for(int i = 0; i < m_nEdgeSize; ++i)
    {
        for(int j = 0; j < m_nEdgeSize; ++j)
        {
            if(CheckBorder(i - 1))
            {
                if(m_ppChessboard[i][j].GetNum() == m_ppChessboard[i - 1][j].GetNum())
                {
                    return true;
                }
            }
            if(CheckBorder(j + 1))
            {
                if(m_ppChessboard[i][j].GetNum() == m_ppChessboard[i][j + 1].GetNum())
                {
                    return true;
                }
            }
        }
    }

    return false;
}

const int KChessBoard::GetEdgeSize() const
{
    return m_nEdgeSize;

}
void KChessBoard::SetEdgeSize(int nLen)
{
    m_nEdgeSize = nLen;

}


const KChessBoard& KChessBoard::operator =(const KChessBoard cb)
{
    for(int i = 0; i < m_nEdgeSize; i++)
    {
        for(int j = 0; j < m_nEdgeSize; j++)
        {
             m_ppChessboard[i][j].SetNum((cb.GetGrid(i,j).GetNum()));
        }

    }
    return *this;

}
void KChessBoard::ResetChessBoard()
{
   this->UnInit();
   this->SetEdgeSize(8);//变成8*8
   this->Init();

}
void KChessBoard::AllMoveLeft()
{
    for(int j = 0; j < m_nEdgeSize;++j)
    {
        for(int i = 0; i < m_nEdgeSize; ++i)
        {
            MoveToNextPossible(i, j, LEFT);
        }
    }
}
void KChessBoard::AllMoveRight()
{
    for(int j = m_nEdgeSize - 1; j >= 0; j--)
    {
        for(int i=0; i< m_nEdgeSize; i++)
        {
           MoveToNextPossible(i,j,RIGHT);
        }
    }

}
void KChessBoard::AllMoveUp()
{
    for(int i = 0; i <  m_nEdgeSize; ++i)
    {
        for(int j = 0; j <  m_nEdgeSize; ++j)
        {
            MoveToNextPossible(i, j, UP);
        }
    }
}
void KChessBoard::AllMoveDown()
{
    for(int i = m_nEdgeSize - 1; i >= 0; --i)
    {
        for(int j = 0; j < m_nEdgeSize; ++j)
        {
           MoveToNextPossible(i, j, DOWN);
        }
    }
}
void KChessBoard::LeftMerge()
{
    for(int j=0; j < m_nEdgeSize; ++j)
    {
        for(int i=0; i < m_nEdgeSize; i++)
        {
            MergeGridAndSetZero(i,j,LEFT);
        }
    }
}
void KChessBoard::RightMerge()
{
    for(int j = m_nEdgeSize - 1; j >= 0; --j)
    {
        for(int i=0; i < m_nEdgeSize; i++)
        {
            MergeGridAndSetZero(i,j,RIGHT);
        }
    }
}
void KChessBoard::UpMerge()
{
    for(int i = 0; i < m_nEdgeSize; ++i)
    {
        for(int j=0; j< m_nEdgeSize; ++j)
        {

           MergeGridAndSetZero(i, j, UP);

        }
    }
}
void KChessBoard::DownMerge()
{
    for(int i = m_nEdgeSize - 1; i >= 0; --i)
    {
        for(int j = 0; j < m_nEdgeSize; ++j)
        {
            MergeGridAndSetZero(i, j, DOWN);
        }


    }
}
bool KChessBoard::GenNewGridsIfPossible(int genTimes)
{
     int ti,tj;
    for(int i = 0; i < genTimes; i++)
    {
        int ti,tj;
        if(IsHasEmptyGrid())
        {
            srand(time(NULL));
            do{
                ti = rand() % m_nEdgeSize;
                tj = rand() % m_nEdgeSize;
            }while(m_ppChessboard[ti][tj].GetNum() != 0);//在空位随机生成一个2或4

            SetGridAuto(ti, tj);
        }
        else
            return false;
    }
    return true;

}
