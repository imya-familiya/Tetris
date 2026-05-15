#ifndef TETRISPART_H
#define TETRISPART_H

enum tetrisshapes {
    noshape,
    oshape,
    ishape,
    sshape,
    zshape,
    lshape,
    jshape,
    tshape
};

class tetrispart
{
private:
    void setX(int index, int x) { coords[index][0] = x; }
    void setY(int index, int y) { coords[index][1] = y; }

    tetrisshapes partShape;
    int coords[4][2];
public:
    tetrispart() { setShape(noshape); };
    void setShape(tetrisshapes shape);
    void setRandomShape();

    tetrisshapes part() const { return partShape; }
    int x(int index) const { return coords[index][0]; }
    int y(int index) const { return coords[index][1]; }

    int minX() const;
    int maxX() const;
    int minY() const;
    int maxY() const;

    tetrispart rotateLeft() const;
    tetrispart rotateRight() const;
};

#endif // TETRISPART_H
