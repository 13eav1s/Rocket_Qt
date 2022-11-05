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
    Counting count;
    InputBlock values{};
    values.angle = ui->lineEdit_angle->text().toDouble();
    values.force = ui->lineEdit_force->text().toDouble();
    values.fuel = ui->lineEdit_fuel->text().toDouble();
    values.mass = ui->lineEdit_mass->text().toDouble();
    values.mass_fuel = ui->lineEdit_mass_fuel->text().toDouble();
    values.length = ui->lineEdit_length->text().toDouble();
    values.x = ui->lineEdit_x->text().toDouble();
    values.low_high_trajectory = ui->radio_high->isChecked();
    count.CalculateTrajectoryCalk(values);
    MainWindow::ShowAngle();
}

void MainWindow::on_btn_alpha_clicked()
{
    Counting count;
    InputBlock values{};
    values.angle = ui->lineEdit_angle->text().toDouble();
    values.force = ui->lineEdit_force->text().toDouble();
    values.fuel = ui->lineEdit_fuel->text().toDouble();
    values.mass = ui->lineEdit_mass->text().toDouble();
    values.mass_fuel = ui->lineEdit_mass_fuel->text().toDouble();
    values.length = ui->lineEdit_length->text().toDouble();
    values.x = ui->lineEdit_x->text().toDouble();
    values.low_high_trajectory = ui->radio_high->isChecked();
    count.CalculateTrajectoryAngle(values);
    MainWindow::ShowAngleFromAngel(count.data_target);
    MainWindow::ShowXYLabels(count.data_target);
}

void MainWindow::ShowAngle() {
    ui->label_alpha->setText("Alpha = " + ui->lineEdit_angle->text());
}

void MainWindow::ShowAngleFromAngel(inverse data_target) {
    //    labelAlpha->Text = "Alpha = " + (((int)(data_target.angle * 100)) / 100.0f).ToString();
    ui->label_alpha->setText("Alpha = " + QString::number((data_target.angle * 100) / 100));
}

void MainWindow::ShowXYLabels(inverse data_target) {
    //    labelXmax->Text = "X = " + Math::Round(data_target.x, 3).ToString();
    ui->label_x_max->setText("X = " + QString::number(data_target.x, 'g', 3));
    ui->label_y_max->setText("Y = " + QString::number(data_target.y, 'g', 3));
}
