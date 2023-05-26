#include "ekran.h"
#include <QPainter>
#include <QMouseEvent>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <QColorDialog>

Ekran::Ekran(QWidget *parent)
    : QWidget{parent}
{
    im=QImage(1000, 1000, QImage::Format_RGB32);
    im.fill(0);
    kolor=QColor::fromRgb(255,255,255);
}

void Ekran::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.drawImage(0,0,im);}

void Ekran::mouseMoveEvent(QMouseEvent *e)
{
    p2.x=e->pos().x();
    p2.y=e->pos().y();
    if(tryb==1)
    {
        kolo();
    }
    else if(tryb==2)
    {
        linia();
    }
}

void Ekran::mousePressEvent(QMouseEvent *e)
{
    if(e->button()==Qt::LeftButton||e->button()==Qt::RightButton)
    {
        p1.x=e->pos().x();
        p1.y=e->pos().y();
        im2=im;

    }
    if(e->button()==Qt::LeftButton)
    {
        tryb=1;
    }
    else if(e->button()==Qt::RightButton)
    {
        tryb=2;
    }
    else if(e->button()==Qt::MiddleButton)
    {
        tryb=0;
        p1.x=e->pos().x();
        p1.y=e->pos().y();
        floodFill();
    }
}

void Ekran::drawPixel(int x,int y)
{
    if((x<im.width()&&x>=0)&&(y<im.height()&&y>=0))
    {
        uchar *pix=im.scanLine(y)+4*x;
        pix[0]=colorDraw.blue;
        pix[1]=colorDraw.green;
        pix[2]=colorDraw.red;
    }
}

void Ekran::kolo()
{

    im=im2;
    R=sqrt(pow((p1.x-p2.x),2)+pow((p1.y-p2.y),2));
    xe=ceil(R/sqrt(2));
    for(int x=0;x<=xe;x++)
    {
        y=sqrt(pow(R,2)-pow(x,2))+0.5;
        drawPixel(x+p1.x,y+p1.y);
        drawPixel(y+p1.x,x+p1.y);
        drawPixel(-x+p1.x,y+p1.y);
        drawPixel(y+p1.x,-x+p1.y);
        drawPixel(-x+p1.x,-y+p1.y);
        drawPixel(-y+p1.x,-x+p1.y);
        drawPixel(x+p1.x,-y+p1.y);
        drawPixel(-y+p1.x,x+p1.y);
    }
    update();

}

void Ekran::linia()
{

    im=im2;
    if(abs(p2.y-p1.y)<=abs(p2.x-p1.x))
        {
            float y=p1.y;
            float a=(float)(p2.y-p1.y)/(p2.x-p1.x);
            if(p1.x<p2.x)
            {
                for(int i=p1.x;i<=p2.x;i++)
                {
                    drawPixel(i+0.5,y+0.5);
                    y+=a;
                }
            }
            else
            {
                for(int i=p1.x;i>=p2.x;i--)
                {
                    drawPixel(i+0.5,y+0.5);
                    y-=a;
                }
            }
        }
        else
        {
            float x=p1.x;
            float a=(float)(p1.x-p2.x)/(p1.y-p2.y);
            if(p1.y<p2.y)
            {
                for(int i=p1.y;i<=p2.y;i++)
                {
                    drawPixel(x+0.5,i+0.5);
                    x+=a;
                }
            }
            else
            {
                for(int i=p1.y;i>=p2.y;i--)
                {
                    drawPixel(x+0.5,i+0.5);
                    x-=a;
                }
            }
        }
    update();
}

void Ekran::colorChange()
{
    colorDraw.red=kolor.red();
    colorDraw.green=kolor.green();
    colorDraw.blue=kolor.blue();
}

void Ekran::setColor(QColor k)
{
    kolor=k;
}

QColor Ekran::getColor()
{
    return kolor;
}

void Ekran::floodFill()
{
    uchar *pix=im.scanLine(p1.y)+4*p1.x;
    uchar *pix2;
    int xpix,ypix;
    uchar r,g,b;
    QVector<coord> pixels;
    coord punkt;
    b=pix[0];
    g=pix[1];
    r=pix[2];
    if(b!=colorDraw.blue||g!=colorDraw.green||r!=colorDraw.red)
    {
        punkt.x=p1.x;
        punkt.y=p1.y;
        pixels.push_back(punkt);
        do
        {
            xpix=pixels[0].x;
            ypix=pixels[0].y;
            pix2=im.scanLine(ypix)+4*(xpix);
            if(xpix<im.width()&&xpix>=0&&ypix<im.height()&&ypix>=0&&pix2[0]==b&&pix2[1]==g&&pix2[2]==r)
            {
                drawPixel(xpix,ypix);
                punkt.x=xpix-1;
                punkt.y=ypix;
                pixels.push_back(punkt);
                punkt.x=xpix+1;
                punkt.y=ypix;
                pixels.push_back(punkt);
                punkt.x=xpix;
                punkt.y=ypix+1;
                pixels.push_back(punkt);
                punkt.x=xpix;
                punkt.y=ypix-1;
                pixels.push_back(punkt);
            }
            pixels.pop_front();
        }
        while(!pixels.empty());
        update();
    }
}


