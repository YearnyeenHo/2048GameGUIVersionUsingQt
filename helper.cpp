#define GRID_SIZE 100
#define GRID_NUM 4
#include "helper.h"
#include <QPainter>
#include <QPaintEvent>
#include <QWidget>
#include <stdlib.h>
#include<math.h>
#include"KChessBoard.h"

Helper::Helper()
{


    background = QBrush(QColor(250, 250, 250));
    gridBrush = QBrush(QColor(250,180,100));
    gridPen = QPen(Qt::white);
    gridPen.setWidth(2);
    m_nGridSize = GRID_SIZE;
    m_nGridNum = GRID_NUM;
    textPen = QPen(Qt::white);
    textFont.setPixelSize(m_nGridSize*0.6);


}

int Helper::calculate(double num)
{

    return log10((double)num)/log10((double)2);
}


void Helper::paint(QPainter *painter, QPaintEvent *event, const KChessBoard& kcb)
{
    painter->fillRect(event->rect(), background);
    painter->translate(100, 100);

    painter->save();
    painter->setPen(gridPen);
    QBrush tempBrush;

    QString str;
    int nTempNum = 0;


    for (int i = 0; i < m_nGridNum; ++i)
    {
        for(int j = 0; j< m_nGridNum; ++j)
        {

            nTempNum = kcb.GetGrid(i,j).GetNum();
            painter->setBrush(QBrush(QColor((100+50*(int)(calculate(nTempNum)%4)), 200, 100)));
            str=QString::number(nTempNum);
            painter->drawRoundedRect(QRect(5+(5+m_nGridSize)*j-100,5+(5+m_nGridSize)*i-100, m_nGridSize, m_nGridSize), 0.5, 1);
            painter->setFont(textFont);
            painter->drawText(QRect(5+(5+m_nGridSize)*j-100,5+(5+m_nGridSize)*i-100, m_nGridSize, m_nGridSize), Qt::AlignCenter, str);
         }
    }
    painter->restore();



}

int Helper::getGridSize()
{
    return m_nGridSize;

}

int Helper::getGridNum()
{

    return m_nGridNum;
}

void Helper::setGridNum(int nNum)
{
   this->m_nGridNum = nNum;
}

void Helper::setGridSize(int nSize)
{
    this->m_nGridSize = nSize;

}
