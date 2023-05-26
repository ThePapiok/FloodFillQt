#ifndef EKRAN_H
#define EKRAN_H

#include <QWidget>
#include <QVector>
#include <QColor>

struct color
{
    uchar red;
    uchar green;
    uchar blue;
};

struct coord
{
    int x;
    int y;
};

class Ekran : public QWidget
{
    Q_OBJECT
public:
        explicit Ekran(QWidget *parent = nullptr);
        void kolo();
        void linia();
        void colorChange();
        void setColor(QColor k);
        QColor getColor();
        void floodFill();
protected:
        void paintEvent(QPaintEvent *);
        void mouseMoveEvent(QMouseEvent *);
        void mousePressEvent(QMouseEvent *);
private:
        QImage im,im2;
        void drawPixel(int x,int y);
        coord p1,p2;
        int R;
        int xe;
        int y;
        int tryb=0;
        color colorDraw={255,255,255};
        QColor kolor;
signals:

};

#endif // EKRAN_H
