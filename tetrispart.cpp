#include "tetrispart.h"
#include "precompiled.h"

void tetrispart::setRandomShape() {
    setShape(tetrisshapes(QRandomGenerator::global()->bounded(7)+1));
}

void tetrispart::setShape(tetrisshapes shape) {
    static const int coordsTable[8][4][2] {
        { { 0, 0 },   { 0, 0 },   { 0, 0 },   { 0, 0 } },
        { { 0, -1 },  { 0, 0 },   { -1, 0 },  { -1, 1 } },
        { { 0, -1 },  { 0, 0 },   { 1, 0 },   { 1, 1 } },
        { { 0, -1 },  { 0, 0 },   { 0, 1 },   { 0, 2 } },
        { { -1, 0 },  { 0, 0 },   { 1, 0 },   { 0, 1 } },
        { { 0, 0 },   { 1, 0 },   { 0, 1 },   { 1, 1 } },
        { { -1, -1 }, { 0, -1 },  { 0, 0 },   { 0, 1 } },
        { { 1, -1 },  { 0, -1 },  { 0, 0 },   { 0, 1 } }
    };

    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 2; j++) {
            coords[i][j] = coordsTable[shape][i][j];
        }
    }

    partShape = shape;
}

int tetrispart::minX() const {
    int min = coords[0][0];

    for (int i = 1; i < 4; i++) {
        min = qMin(min, coords[i][0]);
    }

    return min;
}

int tetrispart::maxX() const {
    int max = coords[0][0];

    for (int i = 1; i < 4; i++) {
        max = qMax(max, coords[i][0]);
    }

    return max;
}

int tetrispart::minY() const {
    int min = coords[0][1];

    for (int i = 1; i < 4; i++) {
        min = qMin(min, coords[i][1]);
    }

    return min;
}

int tetrispart::maxY() const {
    int max = coords[0][1];

    for (int i = 1; i < 4; i++) {
        max = qMax(max, coords[i][1]);
    }

    return max;
}

tetrispart tetrispart::rotateLeft() const {
    if (partShape == oshape) {
        return *this;
    }
    tetrispart result;
    result.partShape = partShape;

    for(int i = 0; i < 4; i++) {
        result.setX(i, -y(i));
        result.setY(i, x(i));
    }

    return result;
}

tetrispart tetrispart::rotateRight() const {
    if (partShape == oshape) {
        return *this;
    }
    tetrispart result;
    result.partShape = partShape;

    for(int i = 0; i < 4; i++) {
        result.setX(i, y(i));
        result.setY(i, -x(i));
    }

    return result;
}
