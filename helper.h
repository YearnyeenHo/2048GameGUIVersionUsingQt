#ifndef HELPER_H
#define HELPER_H

#include <QBrush>
#include <QFont>
#include <QPen>
#include <QWidget>
#include"KChessBoard.h"

class Helper
{
public:
    Helper();

public:
    void paint(QPainter *painter, QPaintEvent *event, const KChessBoard &kcb);
    int getGridSize();
    void setGridNum(int nNum);
    void setGridSize(int nSize);
    int getGridNum();
    int calculate(double num);

private:
    QBrush background;
    QBrush gridBrush;
    QFont textFont;
    QPen gridPen;
    QPen textPen;
    int m_nGridSize;
    int m_nGridNum;


};


#endif
