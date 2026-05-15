#include "tetrisboard.h"
#include "precompiled.h"

tetrisboard::tetrisboard(QWidget *parent) : QFrame(parent) {
    setFrameStyle(QFrame::Panel|QFrame::Sunken);
    setFocusPolicy(Qt::StrongFocus);
    isStarted = false;
    isPaused = false;
    cleanBoard();
    nextPart.setRandomShape();
}

void tetrisboard::start() {
    if (isPaused) return;

    player.play();

    isStarted = true;

    linesRemoved = 0;

    partsDroped = 0;

    score = 0;

    level = 1;

    isWaitingAfterLine = false;

    cleanBoard();

    emit linesRemoveChange(linesRemoved);
    emit scoreChange(score);
    emit levelChange(level);

    newPart();

    timer.start(timeoutTime(), this);
}

void tetrisboard::pause() {

}

void tetrisboard::timerEvent(QTimerEvent *event) {
    if (event -> timerId() == timer.timerId()) {
        if (isWaitingAfterLine) {
            isWaitingAfterLine = false;
            newPart();
            timer.start(timeoutTime(), this);
        } else {
            oneLineDown();
        }
    } else {
        QFrame::timerEvent(event);
    }
}

void tetrisboard::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_Left:
        tryMove(currentPart, curX - 1, curY);
        break;
    case Qt::Key_Right:
        tryMove(currentPart, curX + 1, curY);
        break;
    case Qt::Key_Down:
        tryMove(currentPart.rotateLeft(), curX, curY);
        break;
    case Qt::Key_Up:
        tryMove(currentPart.rotateRight(), curX, curY);
        break;
    default:
        QFrame::keyPressEvent(event);
    }

}

void tetrisboard::cleanBoard() {
    for (int i = 0; i < boardheight * boardwidth; ++i) {
        board[i] = noshape;
    }
}

void tetrisboard::oneLineDown() {
    if(!tryMove(currentPart, curX, curY - 1)) partDrop(0);
}

void tetrisboard::partDrop(int dropHeight) {
    for(int i = 0; i < 4; ++i) {
        int x = curX + currentPart.x(i);
        int y = curY - currentPart.y(i);
        ashape(x, y) = currentPart.part();
    }
    ++partsDroped;
    if(!isWaitingAfterLine) {
        newPart();
    }
    removeFullLine();
}

void tetrisboard::removeFullLine() {
    int numLine = 0;
    for(int i = boardheight - 1; i >= 0; --i) {
        bool isFull = true;
        for(int j = 0; j < boardwidth; ++j) {
            if(ashape(j, i) == noshape) {
                isFull = false;
                break;
            }
        }

        if(isFull) {
            for(int j = 0; j < boardwidth; ++j) {
                ashape(j, i) = noshape;
            }

            score += 1;
        }
    }
}

void tetrisboard::newPart() {
    currentPart = nextPart;
    nextPart.setRandomShape();
    showNextPart();
    curX = boardwidth / 2 + 1;
    curY = boardheight - 1 + currentPart.minY();
    if (!tryMove(currentPart, curX, curY)) {
        currentPart.setShape(noshape);
        timer.stop();
        isStarted = false;
    }
}

void tetrisboard::showNextPart() {
    if(!nextPartLabel) return;

    int dx = nextPart.maxX() - nextPart.minX() + 1;
    int dy = nextPart.maxY() - nextPart.minY() + 1;

    QPixmap pixmap(dx * squereWidth(), dy * squereHeight());

    QPainter painter(&pixmap);

    for(int i = 0; i < 4; ++i) {
        int x = nextPart.x(i) - nextPart.minX();
        int y = nextPart.y(i) - nextPart.minY();
        drawSquare(painter, x * squereWidth(), y * squereHeight(), nextPart.part());
    }

    nextPartLabel->setPixmap(pixmap);
}

bool tetrisboard::tryMove(const tetrispart &newPart, int newX, int newY) {
    for(int i = 0; i < 4; ++i) {
        int x = newX + newPart.x(i);
        int y = newY - newPart.y(i);
        if(x < 0 || x >= boardwidth || y >= boardheight || ashape(x, y) != noshape) return false;
        //if(ashape(x, y) != noshape) return false;
    }
    currentPart = newPart;
    curX = newX;
    curY = newY;
    update();
    return true;
}

void tetrisboard::setNextPartLabel(QLabel *label) {
    nextPartLabel = label;
}

void tetrisboard::paintEvent(QPaintEvent *event) {
    QFrame::paintEvent(event);
    QPainter painter(this);
    QRect rect = contentsRect();
    int boardTop = rect.bottom() - boardheight * 4;
    for(int i = 0; i < boardheight; ++i) {
        for(int j = 0; j < boardwidth; ++j) {
            tetrisshapes shape = ashape(j, boardheight - i - 1);
            if(shape != noshape) {
                drawSquare(painter, rect.left() + j * squereWidth(), boardTop + i * squereHeight() - 500, shape);
            }
        }
    }
    if(currentPart.part() != noshape) {
        for(int i = 0; i < 4; ++i) {
            int x = curX + currentPart.x(i);
            int y = curY + currentPart.y(i);
            drawSquare(painter, rect.left() + x * squereWidth(), boardTop + (boardheight - y - 1) * squereHeight() - 500, currentPart.part());
        }
    }
}

void tetrisboard::drawSquare(QPainter &painter, int x, int y, tetrisshapes shape) {
    static const QRgb colorTable[8] = { 0x000000, 0xF3EB4C, 0x58D8ED, 0xE5492A, 0x7FAF46, 0xEE9439, 0xE972B2, 0x933E8D};

    QColor color = colorTable[int(shape)];

    painter.fillRect(x + 1, y + 1, squereWidth() - 2, squereHeight() - 2, color);

    painter.setPen(color.lighter());
    painter.drawLine(x, y + squereHeight() - 1, x, y);
    painter.drawLine(x, y, x + squereWidth() - 1, y);

    painter.setPen(color.darker());
    painter.drawLine(x + 1, y + squereHeight() - 1, x + squereWidth() - 1, y + squereHeight() - 1);
    painter.drawLine(x + squereWidth() - 1, y + squereHeight() - 1, x + squereWidth() - 1, y + 1);
}