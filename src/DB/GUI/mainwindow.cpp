#include "DB/GUI/mainwindow.hpp"
#include "./ui_mainwindow.h"
#include <iostream>

// #define button

MainWindow::MainWindow(const TableWindow::tables_ptr & tables_ptr, QWidget * parent):
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  _tablewindow = new TableWindow(tables_ptr);
  connect(ui->showTablesButton,
   &QPushButton::clicked,
   [&]()
   {
     _tablewindow->show();
     _tablewindow->setFocus(Qt::FocusReason::ActiveWindowFocusReason);
   });
}

MainWindow::~MainWindow()
{
  delete ui;
}
