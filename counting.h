//
// Created by Leonid on 10/23/22.
//


#include <iostream>
#include <cmath>
#include "input_block.h"
#include <QVector>

#include "numeric.h"
#include "inverse.h"

#include "mainwindow.h"

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
    inverse data_target = {0, 0, 0};

    void CalculateTrajectoryCalk(InputBlock values);

    void CalculateTrajectoryAngle(InputBlock values);

    [[nodiscard]] QVector<phase> Coordinates(InputBlock values, double angle = -1, double step = -1) const;

    [[nodiscard]] QVector<phase> Error(InputBlock values, double angle = -1) const;

    [[nodiscard]] double FlyLength(InputBlock values, double angle) const;

    [[nodiscard]] inverse FindMax(InputBlock values) const;

    [[nodiscard]] inverse findAlphaInv(InputBlock values, double alpha_max) const;
};
