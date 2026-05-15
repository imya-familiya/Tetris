#ifndef TETRISBOARD_H
#define TETRISBOARD_H

#include "precompiled.h"
#include "tetrispart.h"

class QLabel;

class tetrisboard : public QFrame
{
Q_OBJECT
public:
    tetrisboard(QWidget *parent = nullptr);
    void setNextPartLabel(QLabel *label);
public slots:
    void start();
    void pause();
signals:
    void levelChange(int level);
    void scoreChange(int score);
    void linesRemoveChange(int numLine);
protected:
    void keyPressEvent(QKeyEvent *event) override;
    void timerEvent(QTimerEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
private:
    enum {
        boardwidth = 10,
        boardheight = 22
    };

    tetrisshapes &ashape(int x, int y) { return board[(y * boardwidth) + x]; }

    int squereWidth() { return contentsRect().width() / boardwidth; }
    int squereHeight() { return contentsRect().height() / boardheight; };

    void cleanBoard();
    void dropDown();
    void oneLineDown();
    void partDrop(int dropHeight);
    void removeFullLine();
    void newPart();
    void showNextPart();
    void drawSquare(QPainter &painter, int x, int y, tetrisshapes shape);
    QSize size() { return QSize(boardwidth * 15 + frameWidth() * 2, boardheight * 15 + frameWidth() * 2); }
    bool tryMove(const tetrispart &newPart, int newX, int newY);

    tetrisshapes board[boardwidth * boardheight];
    tetrispart currentPart;
    tetrispart nextPart;

    bool isStarted, isPaused, isWaitingAfterLine;
    int linesRemoved;
    int partsDroped;
    int score;
    int level;

    int curX, curY;

    QPointer<QLabel> nextPartLabel;

    QMediaPlayer player;

    QBasicTimer timer;

    int timeoutTime() { return 1000 / (1 + level); }
};

#endif // TETRISBOARD_H
