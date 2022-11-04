#include <iostream>

#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "counting.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_calk_clicked()
{
    InputBlock values{};
    values.angle = ui->lineEdit_angle->text().toDouble();
    values.force = ui->lineEdit_force->text().toDouble();
    values.fuel = ui->lineEdit_fuel->text().toDouble();
    values.mass = ui->lineEdit_mass->text().toDouble();
    values.mass_fuel = ui->lineEdit_mass_fuel->text().toDouble();
    values.length = ui->lineEdit_length->text().toDouble();
    Counting::CalculateTrajectoryCalk(values);
}
