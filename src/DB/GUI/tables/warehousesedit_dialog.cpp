#include "DB/GUI/tables/warehousesedit_dialog.hpp"
#include "./ui_warehousesedit_dialog.h"
#include <iostream>

WarehousesEditDialog::WarehousesEditDialog(const tables_ptr & tables, QWidget * parent):
  QDialog(parent),
  ui(new Ui::WarehousesEditDialog),
  _tables_ptr(tables)
{
  ui->setupUi(this);

  connect(ui->commitButton, &QPushButton::clicked, this, &WarehousesEditDialog::_commit);
}

WarehousesEditDialog::~WarehousesEditDialog()
{
  delete ui;
}

void WarehousesEditDialog::showWithData(int id, const std::string & name, int quantity, double amount)
{
  _id = id;
  ui->name->setText(name.c_str());
  ui->quantityValue->setValue(quantity);
  ui->amountValue->setValue(amount);

  this->show();
}

void WarehousesEditDialog::_commit()
{
  auto name = ui->name->text().toStdString();
  auto quantity = ui->quantityValue->value();
  auto amount = ui->amountValue->value();

  _tables_ptr->warehouses().update(_id, name, quantity, amount);

  this->close();
}
