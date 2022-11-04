//
// Created by Leonid on 11/4/22.
//

#include <cmath>
#include"phase.h"


#ifndef ROCKET_REBASE_MODEL_H
#define ROCKET_REBASE_MODEL_H


class model {
public:
    static double mass0, rate, force, g, angle;

    static double vel(double vx, double vy);

    static double mass(double t);

    // {vx, vy, x, y}
    static phase df(phase p, double t);

    // guide - направляющая
    static double s_guide(double t);

    static double v_guide(double t);

    static phase p_guide(double t);

    // free - свободное падение
    static phase p0_free;
    static double t0_free;

    static phase p_free(double t);
};


#endif //ROCKET_REBASE_MODEL_H
