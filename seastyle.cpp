#define QT_NO_OPENGL
#include <QtWidgets>

#include "seastyle.h"

seastyle::seastyle()
{

}

void seastyle::polish(QPalette &palette)
{
    QColor blue(96,242,250);
    QColor cyan(0, 255, 255);
    QColor slightlyOpaqueBlack(0, 0, 0, 63);

    QPixmap backgroundImage(":/images/seabackground.jpg");
    QPixmap buttonImage(":/images/seabutton.jpeg");
    QPixmap midImage = buttonImage;

    QPainter painter;
    painter.begin(&midImage);
    painter.setPen(Qt::NoPen);
    painter.fillRect(midImage.rect(), slightlyOpaqueBlack);
    painter.end();
//! [0]

//! [1]
    palette = QPalette(blue);

    palette.setBrush(QPalette::BrightText, Qt::white);
    palette.setBrush(QPalette::Base, cyan);
    palette.setBrush(QPalette::Highlight, Qt::darkBlue);
    setTexture(palette, QPalette::Button, buttonImage);
    setTexture(palette, QPalette::Mid, midImage);
    setTexture(palette, QPalette::Window, backgroundImage);

    QBrush brush = palette.background();
    brush.setColor(brush.color().dark());

    palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
    palette.setBrush(QPalette::Disabled, QPalette::Text, brush);
    palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
    palette.setBrush(QPalette::Disabled, QPalette::Base, brush);
    palette.setBrush(QPalette::Disabled, QPalette::Button, brush);
    palette.setBrush(QPalette::Disabled, QPalette::Mid, brush);


}
