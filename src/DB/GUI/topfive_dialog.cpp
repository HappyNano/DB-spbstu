#include "DB/GUI/topfive_dialog.hpp"
#include "./ui_topfive_dialog.h"
#include <iostream>

TopFiveDialog::TopFiveDialog(const DB::Connection::shared & connection_ptr, QWidget * parent):
  QDialog(parent),
  ui(new Ui::TopFiveDialog),
  _connection_ptr(connection_ptr)
{
  ui->setupUi(this);

  connect(ui->getButton, &QPushButton::clicked, this, &TopFiveDialog::_get);
  auto fromDate = QDate::currentDate().addMonths(-1);
  auto toDate = QDate::currentDate();
  ui->fromDate->setDate(fromDate);
  ui->toDate->setDate(toDate);
}

TopFiveDialog::~TopFiveDialog()
{
  delete ui;
}

void TopFiveDialog::_get()
{
  auto dateFrom = ui->fromDate->date();
  auto dateTo = ui->toDate->date();
  std::string dateFrom_str =
   std::to_string(dateFrom.year()) + "-" + std::to_string(dateFrom.month()) + "-" + std::to_string(dateFrom.day());
  std::string dateTo_str = std::to_string(dateTo.year()) + "-" + std::to_string(dateTo.month()) + "-" + std::to_string(dateTo.day());

  std::string command =
   std::string("SELECT warehouses.name AS name, SUM(sales.amount * sales.quantity) AS profit FROM sales ") +
   "INNER JOIN warehouses ON sales.warehouse_id = warehouses.id " + "WHERE sales.sale_date >= '" + dateFrom_str +
   "' AND sales.sale_date <= '" + dateTo_str + "'" + " GROUP BY name ORDER BY profit DESC LIMIT 5";
  pqxx::result result = _connection_ptr->worker()->exec(command);

  auto topFive_labels = { ui->firstLabel, ui->secondLabel, ui->thirdLabel, ui->fourthLabel, ui->fifthLabel };
  auto topFive_labels_iter = topFive_labels.begin();
  int i = 1;
  for (auto && row: result)
  {
    (*topFive_labels_iter)->setText(QString::number(i++) + ": " + row.at(0).as< std::string >().c_str());
    ++topFive_labels_iter;
  }
}
