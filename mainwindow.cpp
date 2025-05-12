#include "mainwindow.h"
#include <QVBoxLayout> 
#include <QWidget>
#include <random>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), labelTemperature(new QLabel("Temperature")),
      labelStatus(new QLabel("Status")), button(new QPushButton("Read Temperature")) {

    QWidget *central = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(central);
    layout->addWidget(labelTemperature);
    layout->addWidget(labelStatus);
    layout->addWidget(button);

    connect(button, &QPushButton::clicked, this, &MainWindow::readTemperature);
    setCentralWidget(central);
}

MainWindow::~MainWindow() {}

void MainWindow::readTemperature() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<float> dist(40.0f, 110.0f);

    float temp = dist(gen);
    QString tempText = QString::number(temp, 'f', 1) + " °F";
    labelTemperature->setText(tempText);

    QString status;
    if (temp < 60.0f) {
        status = "Cold";
    } else if (temp <= 85.0f) {
        status = "Normal";
    } else {
        status = "Hot";
    }

    labelStatus->setText(status);
}
