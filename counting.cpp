//
// Created by Leonid on 10/23/22.
//
//#pragma once

#include "counting.h"


//this->angle = Convert::ToDouble(angle);
//this->force = Convert::ToDouble(force);
//this->len = Convert::ToDouble(len);
//this->fuel_time = Convert::ToDouble(fuel_time);
//this->mass = Convert::ToDouble(mass);
//this->massfuel = Convert::ToDouble(massfuel);


void Counting::CalculateTrajectoryCalk(InputBlock values) {
    Counting ee;
    QVector<phase> graph = ee.Coordinates(values);
    QVector<phase> error = ee.Error(values);
    QVector<phase> err_up;
    QVector<phase> err_down;
    for (int i = 0; i < graph.size(); i++) {
        err_up.push_back(graph[i] + error[i]);
        err_down.push_back(graph[i] - error[i]);
    }
    err_down.back().y = 0;

    //Переменная для сравнения максимального элемента в цикле
    double ymax = 0;
    //  Цикл для нахождения максимального элемента в Vector
    for (auto &var: graph) {
        if (ymax < var.y) {
            ymax = var.y;
        }
    }

//  Вывод точек траектории полета ракеты
    for (auto & coord : graph) {
        std::cout << coord.x << ' ' << coord.y << std::endl;
    }
}


void Counting::CalculateTrajectoryAngle(InputBlock values) {
    Counting ee;
    inverse data_max = ee.FindMax(values);
    data_target = ee.findAlphaInv(values, data_max.angle);

    //Передача значений из класса counting метода Coordinates в вектор graph
    QVector <phase> graph = ee.Coordinates(values, data_target.angle);
    //Вывод графика полета ракеты
    for (auto & coord : graph)
        //Передача значений в объект типа chart
        std::cout << coord.x << ' ' << coord.y << std::endl;

}


//Метод класса counting который возвращает тип vector. Метод возвращает координаты всех точек на траектории
QVector<phase> Counting::Coordinates(InputBlock values, double angle, double step) const {

    // Проверка на то что программа начинает исполнение с нажатия на кнопку calck
    if (angle < 0)
        angle = values.angle;
    //Перевод угла из градусов в радианы
    angle *= (M_PI) / 180;

    // инициализация параметров модели
    model::mass0 = values.mass;
    //находим расход топлива за секунду (кг)
    model::rate = values.mass_fuel / values.fuel;
    model::force = values.force;
    model::g = g;
    model::angle = angle;
    if (step < 0)
        step = dt;
    numeric::h = step;

    QVector<phase> p;
    p.push_back(phase(0, 0, 0, 0));
    double t = 0;

    // разгон по направляющей
    while (p.back().x <= values.length * cos(angle)) {
        p.push_back(model::p_guide(t));
        t += step;
    }

    //находим траекторию подъема на двигателе
    while (model::rate * t <= values.mass_fuel) {
        p.push_back(numeric::next(p.back(), t));

        //проверка на то что ракета не врезалась в землю
        if (numeric::ground_check(p.back(), p[p.size() - 2]))
            break;

        t += step;
    }

    // инициализация начальных условий свободного падения
    model::p0_free = p.back();
    model::t0_free = t;

    //траектория при отработавшем двигателе
    while (!numeric::ground_check(p.back(), p[p.size() - 2])) {
        p.push_back(model::p_free(t));
        t += step;
    }
    return p;
}

QVector<phase> Counting::Error(InputBlock values, double angle) const {
    if (angle < 0)
        angle = values.angle;
    //Перевод угла из градусов в радианы
    QVector<phase> p_h = Coordinates(values, angle);
    QVector<phase> p_2h = Coordinates(values, angle, 2 * dt);

    QVector<phase> err;// = vector<phase>();
    for (int i = 0; i < p_h.size(); i++) {
        int j = i / 2;
        err.push_back(phase::absp((p_2h[j] - p_h[i]) / 15));
    }
    return err;
}

double Counting::FlyLength(InputBlock values, double angle) const {
    return Coordinates(values, angle).back().x;
}

// Метод золотого сечения
inverse Counting::FindMax(InputBlock values) const {
    double a = 0, b = 90;
    double x1 = b - (b - a) / phi;
    double x2 = a + (b - a) / phi;
    double y1 = FlyLength(values, x1);
    double y2 = FlyLength(values, x2);
    while (b - a > prec) {
        if (y1 <= y2) {
            a = x1;
            x1 = x2;
            y1 = y2;
            x2 = a + (b - a) / phi;
            y2 = FlyLength(values, x2);
        } else {
            b = x2;
            x2 = x1;
            y2 = y1;
            x1 = b - (b - a) / phi;
            y1 = FlyLength(values, x1);
        }
    }
    double alpha_max = (a + b) / 2;
    return {FlyLength(values, alpha_max), 0, alpha_max};
}

//  метод деления пополам
inverse Counting::findAlphaInv(InputBlock values, double alpha_max) const {
    double a = 0, b = 90;
    if (values.low_high_trajectory)
        a = alpha_max;
    else
        b = alpha_max;

    double mid = (a + b) / 2;

    double diff_b = (b) - values.x;
    double diff_mid = FlyLength(values, mid) - values.x;
    while (b - a > prec) {
        if (diff_b * diff_mid < 0)
            a = mid;
        else {
            b = mid;
            diff_b = FlyLength(values, b) - values.x;
        }
        mid = (a + b) / 2;
        diff_mid = FlyLength(values, mid) - values.x;
    }

    QVector<phase> p = Coordinates(values, mid);

    double y_max = 0;
    for (auto &var: p)
        if (var.y > y_max)
            y_max = var.y;

    return {p.back().x, y_max, mid};
}


