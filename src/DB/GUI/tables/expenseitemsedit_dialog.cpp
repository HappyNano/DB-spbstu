#include "DB/GUI/tables/expenseitemsedit_dialog.hpp"
#include "./ui_expenseitemsedit_dialog.h"
#include <iostream>

ExpenseItemsEditDialog::ExpenseItemsEditDialog(const tables_ptr & tables, QWidget * parent):
  QDialog(parent),
  ui(new Ui::ExpenseItemsEditDialog),
  _tables_ptr(tables)
{
  ui->setupUi(this);

  connect(ui->commitButton, &QPushButton::clicked, this, &ExpenseItemsEditDialog::_commit);
}

ExpenseItemsEditDialog::~ExpenseItemsEditDialog()
{
  delete ui;
}

void ExpenseItemsEditDialog::showWithData(int id, const std::string & name)
{
  this->show();

  _id = id;
  ui->name->setText(name.c_str());
}

void ExpenseItemsEditDialog::_commit()
{
  auto name = ui->name->text().toStdString();

  _tables_ptr->expense_items().update(_id, name);
  this->close();
}
