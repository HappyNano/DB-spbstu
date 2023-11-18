#include "DB/GUI/profit_dialog.hpp"
#include "./ui_profit_dialog.h"
#include <iostream>
#include "DB/utility/log.hpp"

ProfitDialog::ProfitDialog(const DB::Connection::shared & connection_ptr, QWidget * parent):
  QDialog(parent),
  ui(new Ui::ProfitDialog),
  _connection_ptr(connection_ptr)
{
  ui->setupUi(this);

  connect(ui->calcButton, &QPushButton::clicked, this, &ProfitDialog::_calc);
  auto fromDate = QDate::currentDate().addMonths(-1);
  auto toDate = QDate::currentDate();
  ui->fromDate->setDate(fromDate);
  ui->toDate->setDate(toDate);
}

ProfitDialog::~ProfitDialog()
{
  delete ui;
}

void ProfitDialog::_calc()
{
  auto dateFrom = ui->fromDate->date();
  auto dateTo = ui->toDate->date();
  std::string dateFrom_str =
   std::to_string(dateFrom.year()) + "-" + std::to_string(dateFrom.month()) + "-" + std::to_string(dateFrom.day());
  std::string dateTo_str = std::to_string(dateTo.year()) + "-" + std::to_string(dateTo.month()) + "-" + std::to_string(dateTo.day());

  std::string command = "SELECT * FROM get_income_and_charge_func('" + dateFrom_str + "'::TIMESTAMP, '" + dateTo_str + "'::TIMESTAMP);";
  log::instance() << DateTime{} << Tag{ "ProfitCalc Class" } << "Query: '" << command << "'\n";
  pqxx::result result = _connection_ptr->worker()->exec(command);

  double income = 0;
  double charge = 0;
  double profit = 0;

  for (const auto & row: result)
  {
    if (!row["total_income"].is_null())
    {
      income = row["total_income"].as< double >();
    }
    if (!row["total_charge"].is_null())
    {
      charge = row["total_charge"].as< double >();
    }
    profit = income - charge;
  }

  ui->incomeLabel->setText("Income: " + QString::number(income));
  ui->chargeLabel->setText("Charge: " + QString::number(charge));
  ui->profitLabel->setText("Profit: " + QString::number(profit));
}
