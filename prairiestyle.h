#ifndef PRAIRIESTYLE_H
#define PRAIRIESTYLE_H

#include "costomstyle.h"

class prairiestyle :public CostomStyle
{
    Q_OBJECT
public:
    prairiestyle();
    void polish(QPalette &palette) override;
};

#endif // PRAIRIESTYLE_H
