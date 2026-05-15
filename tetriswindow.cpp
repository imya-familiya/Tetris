#include "tetriswindow.h"
#include "tetrisboard.h"

TetrisWindow::TetrisWindow() {

    board = new tetrisboard;
    nextLabel = new QLabel;

    nextLabel->setFrameStyle(QFrame::Box|QFrame::Raised);
    nextLabel->setAlignment(Qt::AlignCenter);

    board->setNextPartLabel(nextLabel);

    score = new QLCDNumber(2);
    score->setSegmentStyle(QLCDNumber::Outline);
    score->setStyleSheet("background-color:black");

    lines = new QLCDNumber(2);
    lines->setSegmentStyle(QLCDNumber::Outline);
    lines->setStyleSheet("background-color:black");

    level = new QLCDNumber(2);
    level->setSegmentStyle(QLCDNumber::Outline);
    level->setStyleSheet("background-color:black");

    start = new QPushButton(tr("&start"));
    start->setFocusPolicy(Qt::NoFocus);

    pause = new QPushButton(tr("&pause"));
    pause->setFocusPolicy(Qt::NoFocus);

    quit = new QPushButton(tr("&quit"));
    quit->setFocusPolicy(Qt::NoFocus);

    connect(start, &QPushButton::clicked, board, &tetrisboard::start);
    connect(pause, &QPushButton::clicked, board, &tetrisboard::pause);
    connect(quit, &QPushButton::clicked, qApp, &QApplication::quit);

    connect(board, &tetrisboard::levelChange, level, qOverload<int>(&QLCDNumber::display));
    connect(board, &tetrisboard::linesRemoveChange, lines, qOverload<int>(&QLCDNumber::display));

    QGridLayout *layout = new QGridLayout;

    layout->addWidget(board, 0, 0, 15, 8);

    layout->addWidget(createLabel("next"), 0, 9);
    layout->addWidget(nextLabel, 1, 9);

    layout->addWidget(createLabel("level"), 2, 9);
    layout->addWidget(level, 3, 9);

    layout->addWidget(createLabel("score"), 4, 9);
    layout->addWidget(score, 5, 9);

    layout->addWidget(createLabel("lines"), 6, 9);
    layout->addWidget(lines, 7, 9);

    layout->addWidget(quit, 9, 9);
    layout->addWidget(pause, 10, 9);
    layout->addWidget(start, 11, 9);

    setLayout(layout);
}

QLabel *TetrisWindow::createLabel(const QString &text) {
    QLabel *label = new QLabel(text);
    label->setAlignment(Qt::AlignCenter);
    return label;
}