#include "DB/GUI/mainwindow.hpp"
#include "./ui_mainwindow.h"
#include <iostream>

// #define button

MainWindow::MainWindow(QWidget * parent):
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
}

MainWindow::~MainWindow()
{
  delete ui;
}
