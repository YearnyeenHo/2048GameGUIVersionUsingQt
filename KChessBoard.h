#ifndef __ERLINGSIBA_KCHESSBOARD_H_
#define __ERLINGSIBA_KCHESSBOARD_H_
#include"KGrid.h"
/*
4*4的棋盘
*/
class KChessBoard
{
public:

    KChessBoard();

    KChessBoard(const KChessBoard &cb);

    ~KChessBoard();

    bool Init();

    bool UnInit();

    /**
    * @brief 打印棋盘
    */
    void Print();

    void ResetChessBoard();

    KGrid GetGrid(int i, int j)const;

    /**
    * @brief 用随机数对格子设值
    */
    void SetGridAuto(int i,int j);

    void SetChessboardGrid(int iPos, int jPos, int num);

    void SetChessboard(KChessBoard cb);

    bool IsPosZero(int i, int j);

    bool CheckBorder(int i);

    /**
    * @brief 根据按键方向对格子进行分析合并
    * @param i 位置i
    * @param j 位置j
    * @param direction 按键方向
    */
    void MergeGridAndSetZero(int i,int j,int direction);
    /**
    * @brief 根据按键方向判断是否与邻居相等
    * @return 布尔值判断是否相等
    */
    bool IsEqualsNeighbor(int i, int j,int direction);
    /**
    * @brief 根据按键方向将格子往空白地方移动
    */
    void MoveToNextPossible(int iPos, int jPos, int direction);
    void AllMoveLeft();

    void AllMoveRight();

    void AllMoveUp();

    void AllMoveDown();

    void LeftMerge();

    void RightMerge();

    void UpMerge();

    void DownMerge();

    bool GenNewGridsIfPossible(int genTimes);
    /**
    * @brief 检查棋盘是否出现2048
    */
    int CurrentScore();

    bool CheckRules();

    bool IsHasEmptyGrid();

    const int GetEdgeSize()const;

    void SetEdgeSize(int nLen);

    const KChessBoard& operator =(const KChessBoard cb);

private:

    KGrid** m_ppChessboard;
    int m_nEdgeSize;
};
#endif
