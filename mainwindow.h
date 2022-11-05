#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "input_block.h"
#include "inverse.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
    void ShowAngle();
    void ShowAngleFromAngel(inverse data_target);
    void ShowXYLabels(inverse data_target);

private:
    Ui::MainWindow *ui;

private slots:
    void on_btn_calk_clicked();
    void on_btn_alpha_clicked();
};
#endif // MAINWINDOW_H
