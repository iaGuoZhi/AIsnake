#define QT_NO_OPENGL
#include <QtWidgets>

#include "foreststyle.h"

forestStyle::forestStyle():CostomStyle()
{

}

void forestStyle::polish(QPalette &palette)
{
    QColor brown(212, 140, 95);
    QColor beige(236, 182, 120);
    QColor slightlyOpaqueBlack(0, 0, 0, 63);

    QPixmap backgroundImage(":/images/woodbackground.png");
    QPixmap buttonImage(":/images/woodbutton.png");
    QPixmap midImage = buttonImage;

    QPainter painter;
    painter.begin(&midImage);
    painter.setPen(Qt::NoPen);
    painter.fillRect(midImage.rect(), slightlyOpaqueBlack);
    painter.end();
//! [0]

//! [1]
    palette = QPalette(brown);

    palette.setBrush(QPalette::BrightText, Qt::white);
    palette.setBrush(QPalette::Base, beige);
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
