#include <QKeyEvent>
#include <QPainter>
#include <QTimer>
#include <QMessageBox>
#include <Qt>
#include "widget.h"
#include "helper.h"

Widget::Widget(Helper *helper, QWidget *parent)
    : QWidget(parent), helper(helper)
{
    elapsed = 0;
    m_nCanvasSize = 0;
    m_nCanvasSize = helper->getGridNum()*(helper->getGridSize() + 5);
    setFixedSize(m_nCanvasSize, m_nCanvasSize);
    //Init();
    setFocusPolicy(Qt::TabFocus);
    Init();
    m_player.Init();

}
bool Widget::Init()
{
    helper->setGridNum(m_player.GetChessBoard().GetEdgeSize());//根据新棋盘大小设置
    helper->setGridSize(100);
    m_nCanvasSize = helper->getGridNum()*(helper->getGridSize() + 5);
    setFixedSize(m_nCanvasSize, m_nCanvasSize);//重设窗口大小
    return true;
}
Widget::~Widget()
{
    m_player.UnInit();
}

void Widget::animate()
{
   elapsed = (elapsed + qobject_cast<QTimer*>(sender())->interval()) % 1000;
}

void Widget::keyPressEvent(QKeyEvent * event)
{
    switch (event->key())
    {
    case Qt::Key_Right:
        m_player.PlayGame(100);
        break ;
    case Qt::Key_Up:
       m_player.PlayGame(119);
        break ;
    case Qt::Key_Left:
        m_player.PlayGame(97);
        break ;
    case Qt::Key_Down:
         m_player.PlayGame(115);

        break ;
    default:

        break ;
    }
      repaint();
    if(m_player.IsGameOver())
    {
        QMessageBox msgBox;
        msgBox.setText("GameOver.");
        msgBox.exec();
         /*变成8*8*/
        RestartGame();
    }

}
void Widget::RestartGame()
{
    m_player.ReStart();
    Init();
    repaint();
}
void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    helper->paint(&painter, event, m_player.GetChessBoard());
    painter.end();
}

