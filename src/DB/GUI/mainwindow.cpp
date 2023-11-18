#include "DB/GUI/mainwindow.hpp"
#include "./ui_mainwindow.h"
#include <iostream>

// #define button

MainWindow::MainWindow(const DB::Connection::shared & connection_ptr, QWidget * parent):
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  _errordialog = new ErrorDialog();

  if (!connection_ptr->is_connected())
  {
    _errordialog->updateMsg("Bad connection to PostgreSQL database");
    _errordialog->show();
    this->close();
    return;
  }

  _tables_ptr = std::make_shared< DB::Tables >(connection_ptr->worker());
  _tablewindow = new TableWindow(_tables_ptr);
  connect(ui->showTablesButton,
   &QPushButton::clicked,
   [&]()
   {
     _tablewindow->show();
     _tablewindow->setFocus(Qt::FocusReason::ActiveWindowFocusReason);
   });

  _editorwindow = new EditorWindow(_tables_ptr);
  connect(ui->editTablesButton,
   &QPushButton::clicked,
   [&]()
   {
     _editorwindow->show();
     _editorwindow->setFocus(Qt::FocusReason::ActiveWindowFocusReason);
   });

  _profitdialog = new ProfitDialog(connection_ptr);
  connect(ui->profitTablesButton,
   &QPushButton::clicked,
   [&]()
   {
     _profitdialog->show();
     _profitdialog->setFocus(Qt::FocusReason::ActiveWindowFocusReason);
   });

  _topfivedialog = new TopFiveDialog(connection_ptr);
  connect(ui->topFiveButton,
   &QPushButton::clicked,
   [&]()
   {
     _topfivedialog->show();
     _topfivedialog->setFocus(Qt::FocusReason::ActiveWindowFocusReason);
   });

  ui->centralwidget->setEnabled(false);

  _logindialog = new LoginDialog(_tables_ptr);
  _logindialog->exec();
  if (!_logindialog->isLogged())
  {
    return;
  }

  ui->username_label->setText(_logindialog->getUser().first.c_str());

  ui->centralwidget->setEnabled(true);
  this->show();
}

MainWindow::~MainWindow()
{
  delete ui;
}
