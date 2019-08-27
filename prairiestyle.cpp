#define QT_NO_OPENGL
#include <QtWidgets>

#include "prairiestyle.h"

prairiestyle::prairiestyle()
{

}

void prairiestyle::polish(QPalette &palette){
    QColor green(108,213,32);
    QColor springgree(0,238,118);
    QColor slightlyOpaqueBlack(0, 0, 0, 63);

    QPixmap backgroundImage(":/images/prairiebackground.jpeg");
    QPixmap buttonImage(":/images/prairiebutton.jpeg");
    QPixmap midImage = buttonImage;

    QPainter painter;
    painter.begin(&midImage);
    painter.setPen(Qt::NoPen);
    painter.fillRect(midImage.rect(), slightlyOpaqueBlack);
    painter.end();
//! [0]

//! [1]
    palette = QPalette(green);

    palette.setBrush(QPalette::BrightText, Qt::white);
    palette.setBrush(QPalette::Base, springgree);
    palette.setBrush(QPalette::Highlight, Qt::darkGreen);
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
