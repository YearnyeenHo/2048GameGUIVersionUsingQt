#ifndef WINDOW_H
#define WINDOW_H

#include "helper.h"
#include"widget.h"
#include <QWidget>


class Window : public QWidget
{
    Q_OBJECT

public:
    Window();

    Widget *native;
private:
    Helper helper;
};


#endif
