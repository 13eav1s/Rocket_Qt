//
// Created by Leonid on 11/4/22.
//

#include "numeric.h"

double numeric::h = 0;

phase numeric::k1(phase p, double t) {
    return model::df(p, t);
}

phase numeric::k2(phase p, double t, phase k1) {
    return model::df(p + k1 * h / 2, t + h / 2);
}

phase numeric::k3(phase p, double t, phase k2) {
    return model::df(p + k2 * h / 2, t + h / 2);
}

phase numeric::k4(phase p, double t, phase k3) {
    return model::df(p + k3 * h, t + h);
}

phase numeric::next(phase prev, double t) {
    phase _k1 = k1(prev, t);
    phase _k2 = k2(prev, t, _k1);
    phase _k3 = k3(prev, t, _k2);
    phase _k4 = k4(prev, t, _k3);

    return prev + (_k1 + _k2 * 2 + _k3 * 2 + _k4) * h / 6;
}

bool numeric::ground_check(phase &pb, phase &pa) {
    if (pb.y < 0) {
        double endx = -pa.y * (pb.x - pa.x) / (pb.y - pa.y) + pa.x;
        // скорость по хорошему тоже пересчитать
        pb = phase(pa.vx, pa.vy, endx, 0);
        return true;
    }
    return false;
}

