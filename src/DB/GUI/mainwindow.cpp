#include "DB/GUI/mainwindow.hpp"
#include "./ui_mainwindow.h"
#include <iostream>
#include <libxl.h>

// #define button
using namespace libxl;

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

  _logswidget = new LogsWidget();
  connect(ui->showLogsButton,
   &QPushButton::clicked,
   [&]()
   {
     _logswidget->showLogs();
     _logswidget->setFocus(Qt::FocusReason::ActiveWindowFocusReason);
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

  connect(ui->saveButton, &QPushButton::clicked, this, &MainWindow::_saveXlsx);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::_saveXlsx()
{
  Book * book = xlCreateXMLBook();
  if (book)
  {
    {
      Sheet * sheet = book->addSheet("Charges");
      if (sheet)
      {
        int i = 0;
        for (auto && header: _tables_ptr->charges().getHeaders())
        {
          sheet->writeStr(1, i++, header.c_str());
        }
        i = 2;
        for (auto && row: _tables_ptr->charges().selectAll())
        {
          sheet->writeNum(i, 0, row.id);
          sheet->writeNum(i, 1, row.amount);
          sheet->writeStr(i, 2, row.charge_data.c_str());
          sheet->writeNum(i++, 3, row.expense_item_id);
        }
      }
    }

    {
      Sheet * sheet = book->addSheet("Expense Items");
      if (sheet)
      {
        int i = 0;
        for (auto && header: _tables_ptr->expense_items().getHeaders())
        {
          sheet->writeStr(1, i++, header.c_str());
        }
        i = 2;
        for (auto && row: _tables_ptr->expense_items().selectAll())
        {
          sheet->writeNum(i, 0, row.id);
          sheet->writeStr(i++, 1, row.name.c_str());
        }
      }
    }

    {
      Sheet * sheet = book->addSheet("Sales");
      if (sheet)
      {
        int i = 0;
        for (auto && header: _tables_ptr->sales().getHeaders())
        {
          sheet->writeStr(1, i++, header.c_str());
        }
        i = 2;
        for (auto && row: _tables_ptr->sales().selectAll())
        {
          sheet->writeNum(i, 0, row.id);
          sheet->writeNum(i, 1, row.amount);
          sheet->writeNum(i, 2, row.quantity);
          sheet->writeStr(i, 3, row.sale_date.c_str());
          sheet->writeNum(i++, 4, row.warehouse_id);
        }
      }
    }

    {
      Sheet * sheet = book->addSheet("Warehouses");
      if (sheet)
      {
        int i = 0;
        for (auto && header: _tables_ptr->warehouses().getHeaders())
        {
          sheet->writeStr(1, i++, header.c_str());
        }
        i = 2;
        for (auto && row: _tables_ptr->warehouses().selectAll())
        {
          sheet->writeNum(i, 0, row.id);
          sheet->writeStr(i, 1, row.name.c_str());
          sheet->writeNum(i, 2, row.quantity);
          sheet->writeNum(i++, 3, row.amount);
        }
      }
    }

    book->save("tables.xlsx");
    book->release();
  }
}
