#ifndef TETRISWINDOW_H
#define TETRISWINDOW_H

#include "precompiled.h"

class QLCDNumber;

class QLabel;

class QPushButton;

class tetrisboard;

class TetrisWindow : public QWidget
{
Q_OBJECT

public:    
    TetrisWindow();
private:
    QLabel *createLabel(const QString &text);
    tetrisboard *board;
    QLabel *nextLabel;

    QLCDNumber *score;
    QLCDNumber *lines;
    QLCDNumber *level;

    QPushButton *start;
    QPushButton *quit;
    QPushButton *pause;
};

#endif // TETRISWINDOW_H
