#ifndef __ERLINGSIBA_KPLAYER_H_
#define __ERLINGSIBA_KPLAYER_H_
#include<cstdlib>
#include<Windows.h>
#include<conio.h>
#include"KChessBoard.h"
class MainWindow;  //前置声明
class KPlayer
{
public:
    const static int NEWGRID_NUM = 1;
    const static int UP = 2;
    const static int DOWN = 4;
    const static int LEFT = 1;
    const static int RIGHT = 3;
    KPlayer();

    KPlayer(const KChessBoard& cb);

    bool Init();

    bool UnInit();

    void DoUp();

    void DoDown();

    void DoLeft();

    void DoRight();

    const KChessBoard& GetChessBoard()const;

    /**
    * @brief 接受键盘输入并更新棋盘状态
    */

    void PlayGame();

    void PlayGame(int nch);

    bool IsGameOver();

    void SetGameOverState(bool bstate);

    void ReStart();

    void SetEdgeSize(int nLen);

    bool GetReadyForNextStep();

private:

    KChessBoard m_kChessBoard;

    bool m_bGameOver;

};


#endif
