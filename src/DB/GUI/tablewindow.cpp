#include "DB/GUI/tablewindow.hpp"
#include "./ui_tablewindow.h"
#include <iostream>

// #define button

TableWindow::TableWindow(const tables_ptr & tables, QWidget * parent):
  QWidget(parent),
  ui(new Ui::TableWindow),
  _tables_ptr{ tables }
{
  ui->setupUi(this);
  ui->tablesBox->addItem("Charges");
  ui->tablesBox->addItem("Expense Items");
  ui->tablesBox->addItem("Sales");
  ui->tablesBox->addItem("Warehouses");

  connect(ui->refreshButton, &QPushButton::clicked, this, &TableWindow::_refresh);
  connect(ui->tablesBox, &QComboBox::currentTextChanged, this, &TableWindow::_refresh);
}

TableWindow::~TableWindow()
{
  delete ui;
}

void TableWindow::_refresh()
{
  ui->table->setSortingEnabled(false);
  static auto setIntValue = [](auto & table, int row, int column, auto value)
  {
    auto item = new QTableWidgetItem();
    item->setData(Qt::EditRole, value);
    table->setItem(row, column, item);
  };
  // Clear Table
  ui->table->clear();
  ui->table->setRowCount(0);

  // Set
  auto index = ui->tablesBox->currentIndex();
  switch (index)
  {
  case 0: {
    QStringList headers;
    for (auto && header: _tables_ptr->charges().getHeaders())
    {
      headers << header.c_str();
    }
    ui->table->setColumnCount(headers.size());
    ui->table->setHorizontalHeaderLabels(headers);
    auto rows = _tables_ptr->charges().selectAll();
    ui->table->setRowCount(rows.size());
    for (int i = 0; i < rows.size(); ++i)
    {
      setIntValue(ui->table, i, 0, rows.at(i).id);
      setIntValue(ui->table, i, 1, rows.at(i).amount);
      ui->table->setItem(i, 2, new QTableWidgetItem(QString(rows.at(i).charge_data.c_str())));
      setIntValue(ui->table, i, 3, rows.at(i).expense_item_id);
    }
  }
  break;
  case 1: {
    QStringList headers;
    for (auto && header: _tables_ptr->expense_items().getHeaders())
    {
      headers << header.c_str();
    }
    ui->table->setColumnCount(headers.size());
    ui->table->setHorizontalHeaderLabels(headers);
    auto rows = _tables_ptr->expense_items().selectAll();
    ui->table->setRowCount(rows.size());
    for (int i = 0; i < rows.size(); ++i)
    {
      setIntValue(ui->table, i, 0, rows.at(i).id);
      ui->table->setItem(i, 1, new QTableWidgetItem(QString(rows.at(i).name.c_str())));
    }
  }
  break;
  case 2: {
    QStringList headers;
    for (auto && header: _tables_ptr->sales().getHeaders())
    {
      headers << header.c_str();
    }
    ui->table->setColumnCount(headers.size());
    ui->table->setHorizontalHeaderLabels(headers);
    auto rows = _tables_ptr->sales().selectAll();
    ui->table->setRowCount(rows.size());
    for (int i = 0; i < rows.size(); ++i)
    {
      setIntValue(ui->table, i, 0, rows.at(i).id);
      setIntValue(ui->table, i, 1, rows.at(i).amount);
      setIntValue(ui->table, i, 2, rows.at(i).quantity);
      ui->table->setItem(i, 3, new QTableWidgetItem(QString(rows.at(i).sale_date.c_str())));
      setIntValue(ui->table, i, 4, rows.at(i).warehouse_id);
    }
  }
  break;
  case 3: {
    QStringList headers;
    for (auto && header: _tables_ptr->warehouses().getHeaders())
    {
      headers << header.c_str();
    }
    ui->table->setColumnCount(headers.size());
    ui->table->setHorizontalHeaderLabels(headers);
    auto rows = _tables_ptr->warehouses().selectAll();
    ui->table->setRowCount(rows.size());
    for (int i = 0; i < rows.size(); ++i)
    {
      setIntValue(ui->table, i, 0, rows.at(i).id);
      ui->table->setItem(i, 1, new QTableWidgetItem(QString(rows.at(i).name.c_str())));
      setIntValue(ui->table, i, 2, rows.at(i).quantity);
      setIntValue(ui->table, i, 3, rows.at(i).amount);
    }
  }
  break;

  default:
    break;
  }
  ui->table->resizeColumnsToContents();
  ui->table->setSortingEnabled(true);
}
