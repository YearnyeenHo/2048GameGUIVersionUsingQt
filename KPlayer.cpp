#include <stdio.h>
#include "KPlayer.h"
#include "mainwindow.h"
KPlayer::KPlayer()
{
    m_bGameOver = false;
}

KPlayer::KPlayer(const KChessBoard& cb)
{
   if(this->Init())
   {
        m_kChessBoard.SetChessboard(cb);
        m_bGameOver = false;
   }

}

bool KPlayer::Init()
{
   if(m_kChessBoard.Init())
   return true;
   return false;
}

bool KPlayer::UnInit()
{
    if(m_kChessBoard.UnInit())
     return true;
     return false;
}

void KPlayer::DoUp()
{
    m_kChessBoard.AllMoveUp();
    m_kChessBoard.UpMerge();
    m_kChessBoard.AllMoveUp();
}

void KPlayer::DoDown()
{
    m_kChessBoard.AllMoveDown();
    m_kChessBoard.DownMerge();
    m_kChessBoard.AllMoveDown();
}

void KPlayer::DoLeft()
{
    m_kChessBoard.AllMoveLeft();
    m_kChessBoard.LeftMerge();
    m_kChessBoard.AllMoveLeft();
}

void KPlayer::DoRight()
{
    m_kChessBoard.AllMoveRight();
    m_kChessBoard.RightMerge();
    m_kChessBoard.AllMoveRight();
}

const KChessBoard& KPlayer::GetChessBoard() const
{
    return this->m_kChessBoard;

}

void KPlayer::PlayGame()
{
    m_kChessBoard.Print();

    char ch;
    fflush(stdin);
    while(true)
    {
        ch = getch();

        switch(ch)
        {
        case 119://Up:w
            DoUp();
            break;
        case 115: //down:s
            DoDown();

            break;
        case 97://left:a
            DoLeft();

            break;
        case 100://right:d
            DoRight();

            break;
        default:

            exit(0);

        }
        //end switch

       system("cls");

       if(!GetReadyForNextStep())
       {
         printf("GameOver(ToT)\n");
       }
         m_kChessBoard.Print();
         printf("\n score : %d ",m_kChessBoard.CurrentScore());

    }//end while


}

void KPlayer::PlayGame(int  nch)
{
    switch(nch)
    {
    case 119://Up:w
        DoUp();
        break;
    case 115: //down:s
        DoDown();

        break;
    case 97://left:a
        DoLeft();

        break;
    case 100://right:d
        DoRight();

        break;
    default:

        exit(0);

    }//end switch

    GetReadyForNextStep();
}
bool KPlayer::GetReadyForNextStep()
{
    if(!m_kChessBoard.GenNewGridsIfPossible(NEWGRID_NUM))
   {
       if(!m_kChessBoard.CheckRules())
       {
           m_bGameOver = true;
           return false;
       }

    }
    return true;
}

bool KPlayer::IsGameOver()
{
    return m_bGameOver;

}

void KPlayer::SetGameOverState(bool bState)
{
     m_bGameOver = bState;

}

void KPlayer::ReStart()
{
    m_kChessBoard.ResetChessBoard();
    m_bGameOver = false;

}

void KPlayer::SetEdgeSize(int nLen)
{
    m_kChessBoard.SetEdgeSize(nLen);
}
