//
// Created by jazula on 1/10/17.
//

#include <math.h>
#include "DegreeUtil.hpp"

double DegreeUtil::degree_to_radian(int degrees)
{
    const double halfC = M_PI / 180;
    return halfC * degrees;
}
