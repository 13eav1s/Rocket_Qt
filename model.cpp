//
// Created by Leonid on 11/4/22.
//

#include "model.h"

double model::mass0, model::rate, model::force, model::g, model::angle = 0;
phase model::p0_free = phase(0, 0, 0, 0);
double model::t0_free = 0;

double model::vel(double vx, double vy) {
    return sqrt(vx * vx + vy * vy);
}

double model::mass(double t) {
    return mass0 - rate * t;
}

//производные от скорости и кординат по времени
phase model::df(phase p, double t) {
    double dvx = (p.vx * force) / mass(t) / vel(p.vx, p.vy);
    double dvy = (p.vx * force) / mass(t) / vel(p.vx, p.vy) - g;
    double dx = p.vx;
    double dy = p.vy;

    return {dvx, dvy, dx, dy};
}

// guide - направляющая
double model::s_guide(double t) {
    return force / rate * (t + (t - mass0 / rate) * log(mass0 / mass(t)))
           - g * sin(angle) * pow(t, 2) / 2;
}

double model::v_guide(double t) {
    return force / rate * log(mass0 / mass(t)) - g * sin(angle) * t;
}

phase model::p_guide(double t) {
    return {v_guide(t) * cos(angle), v_guide(t) * sin(angle),
            s_guide(t) * cos(angle), s_guide(t) * sin(angle)};
}

// free - свободное падение
phase model::p_free(double t) {
    double tau = t - t0_free;
    double vx = p0_free.vx;
    double vy = p0_free.vy - g * tau;
    double x = p0_free.x + p0_free.vx * tau;
    double y = p0_free.y + p0_free.vy * tau - g * tau * tau / 2;

    return {vx, vy, x, y};
}
