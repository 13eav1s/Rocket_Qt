//
// Created by Leonid on 11/4/22.
//
#pragma once

#ifndef ROCKET_REBASE_PHASE_H
#define ROCKET_REBASE_PHASE_H


class phase {
public:
    double vx, vy, x, y;

    phase(double vx, double vy, double x, double y);

    static phase absp(phase p);

    // commutative
    phase operator+(phase p) const;

    phase operator-(phase p) const;

    // not commutative
    phase operator*(double k) const;

    phase operator/(double k) const;
};


#endif //ROCKET_REBASE_PHASE_H
