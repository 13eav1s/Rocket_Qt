//
// Created by Leonid on 11/4/22.
//

#include <cmath>
#include "phase.h"

phase::phase(double vx, double vy, double x, double y) {
    this->vx = vx;
    this->vy = vy;
    this->x = x;
    this->y = y;
}

phase phase::absp(phase p) {
    return {fabs(p.vx), fabs(p.vy), fabs(p.x), fabs(p.y)};
}

phase phase::operator+(phase p) const {
    return {vx + p.vx, vy + p.vy, x + p.x, y + p.y};
}

phase phase::operator-(phase p) const {
    return {vx - p.vx, vy - p.vy, x - p.x, y - p.y};
}

phase phase::operator*(double k) const {
    return {vx * k, vy * k, x * k, y * k};
}

phase phase::operator/(double k) const {
    return {vx / k, vy / k, x / k, y / k};
}
