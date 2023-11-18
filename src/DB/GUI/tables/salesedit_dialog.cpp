#include "DB/GUI/tables/salesedit_dialog.hpp"
#include "./ui_salesedit_dialog.h"
#include <iostream>

SalesEditDialog::SalesEditDialog(const tables_ptr & tables, QWidget * parent):
  QDialog(parent),
  ui(new Ui::SalesEditDialog),
  _tables_ptr(tables)
{
  ui->setupUi(this);

  _errordialog = new ErrorDialog();

  connect(ui->commitButton, &QPushButton::clicked, this, &SalesEditDialog::_commit);
}

SalesEditDialog::~SalesEditDialog()
{
  delete ui;
}

void SalesEditDialog::showWithData(int id, int quantity, double amount, const QDateTime & sale_date, const std::string & product_name)
{
  _id = id;
  ui->quantityValue->setValue(quantity);
  ui->amountValue->setValue(amount);
  ui->saleDate->setDateTime(sale_date);

  // Clear and add again
  int productName_id = -1;
  int i = 0;
  ui->product->clear();
  for (auto && item: _tables_ptr->warehouses().getProducts())
  {
    ui->product->addItem(item.second.c_str());
    if (product_name == item.second)
    {
      productName_id = i;
    }
    ++i;
  }
  ui->product->setCurrentIndex(productName_id);

  this->show();
}

void SalesEditDialog::_commit()
{
  auto quantity = ui->quantityValue->value();
  auto amount = ui->amountValue->value();
  auto date = ui->saleDate->date();
  auto time = ui->saleDate->time();
  auto product_str = ui->product->currentText().toStdString();
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
    std::cerr << "error sales commit\n";
  }
  std::string date_str = std::to_string(date.year()) + "-" + std::to_string(date.month()) + "-" + std::to_string(date.day()) + " " +
                         std::to_string(time.hour()) + ":" + std::to_string(time.minute()) + ":" + std::to_string(time.second());

  try
  {
    _tables_ptr->sales().update(_id, amount, quantity, date_str, product_id);
  }
  catch (const std::exception & e)
  {
    _errordialog->updateMsg(e.what());
    _errordialog->show();
  }

  this->close();
}
