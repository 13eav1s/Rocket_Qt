//
// Created by Leonid on 11/4/22.
//
#pragma once

#include "model.h"


#ifndef ROCKET_REBASE_NUMERIC_H
#define ROCKET_REBASE_NUMERIC_H


class numeric {
public:
    static double h;

    static phase k1(phase p, double t);

    static phase k2(phase p, double t, phase k1);

    static phase k3(phase p, double t, phase k2);

    static phase k4(phase p, double t, phase k3);

    static phase next(phase prev, double t);

    static bool ground_check(phase &pb, phase &pa);

};


#endif //ROCKET_REBASE_NUMERIC_H
