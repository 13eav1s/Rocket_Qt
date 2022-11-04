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
    //Вывод в окно Угла при котором ракета прилетит в заданную точку
//    labelAlpha->Text = "Alpha = " + (textBoxAngle->Text);
//Вывод в окно дальности полета
//    labelXmax->Text = "X = " + Math::Round(graph[graph.size() - 1].x, 3).ToString();
//  TOD O: Надо как то вывести этот угол и дальность полета

    //Переменная для сравнения максимального элемента в цикле
    double ymax = 0;
    //Цикл для нахождения максимального элемента в Vector
    //    for each(phase var in graph)
//    if (ymax < var.y)
//        ymax = var.y;
    for (auto &var: graph) {
        if (ymax < var.y) {
            ymax = var.y;
        }
    }

//    //Рисование графика полета ракеты с помощью chart
    for (auto & coord : graph) {
        std::cout << coord.x << ' ' << coord.y << std::endl;
    }
//    {
//        //Передача значений в объект типа chart
//        chart1->Series["Rocket"]->Points->AddXY(graph[i].x, graph[i].y);//Значение Х У
//    }
//    for (int i = 0; i < size; i++)
//    {
//        //Передача значений в объект типа chart
//        chart1->Series["Rocket"]->Points->AddXY(graph[i].x, err_down[i].y);//Значение Х У
//    }
//    for (int i = 0; i < size; i++)
//    {
//        //Передача значений в объект типа chart
//        chart1->Series["Rocket"]->Points->AddXY(graph[i].x, err_up[i].y);//Значение Х У
//    }
//  TOD O: Так как чарта нет нужно вывести значения в консоль и построить график в EXCEL


//Вывод максимальной высоты при полете с округлением до тысячных
//    labelYmax->Text = "Y max = " + Math::Round(ymax, 3).ToString();
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
inverse Counting::findAlphaInv(InputBlock values, double x, double alpha_max, bool high) const {
    double a = 0, b = 90;
    if (high)
        a = alpha_max;
    else
        b = alpha_max;

    double mid = (a + b) / 2;

    double diff_b = (b) - x;
    double diff_mid = FlyLength(values, mid) - x;
    while (b - a > prec) {
        if (diff_b * diff_mid < 0)
            a = mid;
        else {
            b = mid;
            diff_b = FlyLength(values, b) - x;
        }
        mid = (a + b) / 2;
        diff_mid = FlyLength(values, mid) - x;
    }

    QVector<phase> p = Coordinates(values, mid);

    double y_max = 0;
    for (auto &var: p)
        if (var.y > y_max)
            y_max = var.y;

    return {p.back().x, y_max, mid};
}


