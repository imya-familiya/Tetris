#ifndef UIMAINWINDOW_H
#define UIMAINWINDOW_H

QT_BEGIN_NAMESPACE
class uimainwindow
{
public:
    uimainwindow() {}

    QWidget *centralWidget;

    void setupUI(QMainWindow *MainWindow) {
        MainWindow -> resize(400, 460);
        centralWidget = new QWidget(MainWindow);
        MainWindow -> setCentralWidget(centralWidget);
        QMetaObject::connectSlotsByName(MainWindow);
    }
};

namespace UI {
class MainWindow : public uimainwindow {};
}

QT_END_NAMESPACE

#endif // UIMAINWINDOW_H
