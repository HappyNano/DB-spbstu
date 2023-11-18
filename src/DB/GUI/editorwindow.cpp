#include "DB/GUI/editorwindow.hpp"
#include "./ui_editorwindow.h"
#include <iostream>

EditorWindow::EditorWindow(const tables_ptr & tables, QWidget * parent):
  QWidget(parent),
  ui(new Ui::EditorWindow),
  _tables_ptr{ tables }
{
  ui->setupUi(this);
  connect(ui->chargesInsert, &QPushButton::clicked, this, &EditorWindow::_insertCharges);
  connect(ui->expenseItemInsert, &QPushButton::clicked, this, &EditorWindow::_insertExpenseItems);
  connect(ui->salesInsert, &QPushButton::clicked, this, &EditorWindow::_insertSales);
  connect(ui->productInsert, &QPushButton::clicked, this, &EditorWindow::_insertWarehouses);
  _update();
}

EditorWindow::~EditorWindow()
{
  delete ui;
}

bool EditorWindow::_checkCharges()
{
  return true;
}
bool EditorWindow::_checkExpenseItems()
{
  return true;
}
bool EditorWindow::_checkSales()
{
  return true;
}
bool EditorWindow::_checkWarehouses()
{
  return true;
}

void EditorWindow::_insertCharges()
{
  if (!_checkCharges())
  {}
  double amount = ui->chargesAmount->value();
  auto date = ui->chatgesDate->date();
  auto time = ui->chatgesDate->time();
  auto expense_item_str = ui->chargesExpenseItem->currentText().toStdString();
  int expense_item_id = -1;

  for (auto & item: _tables_ptr->expense_items().getExpenseItems())
  {
    if (item.second == expense_item_str)
    {
      expense_item_id = item.first;
      break;
    }
  }
  if (expense_item_id == -1)
  {
    std::cerr << "error charges\n";
  }
  std::string date_str = std::to_string(date.year()) + "-" + std::to_string(date.month()) + "-" + std::to_string(date.day()) + " " +
                         std::to_string(time.hour()) + ":" + std::to_string(time.minute()) + ":" + std::to_string(time.second());

  _tables_ptr->charges().insert(amount, date_str, expense_item_id);
  _update();
}
void EditorWindow::_insertExpenseItems()
{
  if (!_checkExpenseItems())
  {}

  auto name = ui->expenseItemName->text().toStdString();

  _tables_ptr->expense_items().insert(name);
  _update();
}
void EditorWindow::_insertSales()
{
  if (!_checkSales())
  {}
  auto quantity = ui->salesQuantity->value();
  auto amount = ui->salesAmount->value();
  auto date = ui->salesDatetime->date();
  auto time = ui->salesDatetime->time();
  auto product_str = ui->salesProduct->currentText().toStdString();
  auto product_id = -1;

  for (auto & item: _tables_ptr->warehouses().getProducts())
  {
    if (item.second == product_str)
    {
      product_id = item.first;
      break;
    }
  }
  if (product_id == -1)
  {
    std::cerr << "error sales\n";
  }
  std::string date_str = std::to_string(date.year()) + "-" + std::to_string(date.month()) + "-" + std::to_string(date.day()) + " " +
                         std::to_string(time.hour()) + ":" + std::to_string(time.minute()) + ":" + std::to_string(time.second());

  _tables_ptr->sales().insert(amount, quantity, date_str, product_id);

  _update();
}
void EditorWindow::_insertWarehouses()
{
  if (!_checkWarehouses())
  {}

  auto name = ui->productName->text().toStdString();
  auto quantity = ui->productQuantity->value();
  auto amount = ui->productAmount->value();

  _tables_ptr->warehouses().insert(name, quantity, amount);

  _update();
}

void EditorWindow::_update()
{
  ui->chargesExpenseItem->clear();
  ui->salesProduct->clear();

  for (auto & item: _tables_ptr->expense_items().getExpenseItems())
  {
    ui->chargesExpenseItem->addItem(item.second.c_str());
  }

  for (auto & item: _tables_ptr->warehouses().getProducts())
  {
    ui->salesProduct->addItem(item.second.c_str());
  }
  ui->chatgesDate->setDateTime(QDateTime::currentDateTime());
  ui->salesDatetime->setDateTime(QDateTime::currentDateTime());
}
