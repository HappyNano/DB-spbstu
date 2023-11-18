#include "DB/GUI/tables/chargesedit_dialog.hpp"
#include "./ui_chargesedit_dialog.h"
#include <iostream>

ChargesEditDialog::ChargesEditDialog(const tables_ptr & tables, QWidget * parent):
  QDialog(parent),
  ui(new Ui::ChargesEditDialog),
  _tables_ptr(tables)
{
  ui->setupUi(this);

  connect(ui->commitButton, &QPushButton::clicked, this, &ChargesEditDialog::_commit);

  _errordialog = new ErrorDialog();
}

ChargesEditDialog::~ChargesEditDialog()
{
  delete ui;
}

void ChargesEditDialog::showWithData(int id, double amount, const QDateTime & datetime, const std::string & expenseItem_str)
{
  this->show();

  _id = id;
  ui->amountValue->setValue(amount);
  ui->chargeDate->setDateTime(datetime);

  // Clear and add again
  int expenseItem_id = -1;
  int i = 0;
  ui->expenseItem->clear();
  for (auto && item: _tables_ptr->expense_items().getExpenseItems())
  {
    ui->expenseItem->addItem(item.second.c_str());
    if (expenseItem_str == item.second)
    {
      expenseItem_id = i;
    }
    ++i;
  }
  ui->expenseItem->setCurrentIndex(expenseItem_id);
}

void ChargesEditDialog::_commit()
{
  double amount = ui->amountValue->value();
  auto date = ui->chargeDate->date();
  auto time = ui->chargeDate->time();
  auto expense_item_str = ui->expenseItem->currentText().toStdString();
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
    std::cerr << "error charges commit\n";
  }

  std::string date_str = std::to_string(date.year()) + "-" + std::to_string(date.month()) + "-" + std::to_string(date.day()) + " " +
                         std::to_string(time.hour()) + ":" + std::to_string(time.minute()) + ":" + std::to_string(time.second());

  try
  {
    _tables_ptr->charges().update(_id, amount, date_str, expense_item_id);
  }
  catch (const std::exception & e)
  {
    _errordialog->updateMsg(e.what());
    _errordialog->show();
  }

  this->close();
}
