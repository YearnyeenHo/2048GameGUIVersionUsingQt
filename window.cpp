#include <QGridLayout>
#include <QLabel>
#include <QTimer>

#include "widget.h"
#include "window.h"

Window::Window()
{
    setWindowTitle(tr("Game 2048"));

    native = new Widget(&helper, this);

    QLabel *nativeLabel = new QLabel(tr("Native"));
    nativeLabel->setAlignment(Qt::AlignHCenter);


    QGridLayout *layout = new QGridLayout;
    layout->addWidget(native, 0, 0);

    layout->addWidget(nativeLabel, 1, 0);

    setLayout(layout);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), native, SLOT(animate()));

    timer->start(50);
}





