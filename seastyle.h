#ifndef SEASTYLE_H
#define SEASTYLE_H

#include "costomstyle.h"

class seastyle :public CostomStyle
{
    Q_OBJECT
public:
    seastyle();
    void polish(QPalette &palette) override;
};

#endif // SEASTYLE_H
