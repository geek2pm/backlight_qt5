#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <cmath>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    QFile file("/sys/class/backlight/intel_backlight/max_brightness");
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }
    QTextStream in(&file);
    QString val = in.readAll();
    file.close();

    ui->horizontalSlider->setMaximum(val.toInt());

    QFile file2("/sys/class/backlight/intel_backlight/brightness");
    if(!file2.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }
    QTextStream in2(&file2);
    QString val2 = in2.readAll();
    file2.close();
    ui->horizontalSlider->setValue(val2.toInt());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    float x =(double)100 / ui->horizontalSlider->maximum();
    int b = round(x*value);

    ui->label->setText(QString::number(b)+"%");

    QString str = QString::number(value);

//    QString cmd = "echo "+str+"> /sys/class/backlight/intel_backlight/brightness";
//    QByteArray ba = cmd.toLatin1();
//    system(ba);

    QFile file("/sys/class/backlight/intel_backlight/brightness");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    file.write(str.toUtf8());
    file.close();
}
