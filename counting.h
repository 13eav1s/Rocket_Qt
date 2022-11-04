//
// Created by Leonid on 10/23/22.
//


#include <iostream>
#include <cmath>
#include "input_block.h"
#include <QVector>

#include "numeric.h"
#include "inverse.h"

#ifndef ROCKET_REBASE_COUNTING_H
#define ROCKET_REBASE_COUNTING_H
//#define _USE_MATH_DEFINES

#endif //ROCKET_REBASE_COUNTING_H

class Counting {
public:
    const double g = 9.8;
    const double dt = 0.1; // Интервал в секундах с которым программа считает траекторию
    const double dt2d2 = dt * dt / 2;
    const double prec = 0.1; // точность для обратной задачи
    const double phi = (1.0 + sqrt(5)) / 2;

    static void CalculateTrajectoryCalk(InputBlock values);

    QVector<phase> Coordinates(InputBlock values, double angle = -1, double step = -1) const;

    QVector<phase> Error(InputBlock values, double angle = -1) const;

    double FlyLength(InputBlock values, double angle) const;

    inverse FindMax(InputBlock values) const;

    inverse findAlphaInv(InputBlock values, double x, double alpha_max, bool high) const;
};
