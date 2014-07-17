#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "KPlayer.h"

class Helper;

class Widget : public QWidget
{
    Q_OBJECT

public:

    Widget(Helper *helper, QWidget *parent);

    ~Widget();

    bool Init();
public slots:

    void animate();

protected:

    void paintEvent(QPaintEvent *event);

    void keyPressEvent(QKeyEvent * event);

    void RestartGame();
private:

    int m_nCanvasSize;

    Helper *helper;

    int elapsed;

    KPlayer m_player;

};


#endif
