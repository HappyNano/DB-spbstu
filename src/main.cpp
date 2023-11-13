#include <iostream>
#include <string>

#include <pqxx/pqxx>

#include "DB/GUI/mainwindow.hpp"
#include "DB/tables/warehouses.hpp"
#include "DB/tables/charges.hpp"
#include "DB/tables/expense_items.hpp"
#include "DB/tables/sales.hpp"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char * argv[])
{

  pqxx::connection c{ "dbname = lab user = admin password = admin hostaddr = 127.0.0.1 port = 5432" };
  auto worker_ptr = std::make_shared< pqxx::work >(c);

  // int employee_id = txn.query_value< int >(
  //  "SELECT *"
  //  "FROM warehouses ");

  DB::TableWarehouses warehouses(worker_ptr);
  auto result1 = warehouses.selectAll();

  for (auto && header: warehouses.getHeaders())
  {
    std::cout << header << ' ';
  }
  std::cout << '\n';
  for (auto && row: result1)
  {
    std::cout << row << '\n';
  }
  std::cout << '\n';
  ///////////////////
  DB::TableCharges charges(worker_ptr);
  auto result2 = charges.selectAll();

  for (auto && header: charges.getHeaders())
  {
    std::cout << header << ' ';
  }
  std::cout << '\n';
  for (auto && row: result2)
  {
    std::cout << row << '\n';
  }
  std::cout << '\n';
  ///////////////////
  DB::TableExpenseItems expense_item(worker_ptr);
  auto result3 = expense_item.selectAll();

  for (auto && header: expense_item.getHeaders())
  {
    std::cout << header << ' ';
  }
  std::cout << '\n';
  for (auto && row: result3)
  {
    std::cout << row << '\n';
  }
  std::cout << '\n';
  ///////////////////
  DB::TableSales sales(worker_ptr);
  auto result4 = sales.selectAll();

  for (auto && header: sales.getHeaders())
  {
    std::cout << header << ' ';
  }
  std::cout << '\n';
  for (auto && row: result4)
  {
    std::cout << row << '\n';
  }
  std::cout << '\n';

  // c.disconnect();

  // txn.exec0("UPDATE EMPLOYEE "
  //           "SET salary = salary + 1 "
  //           "WHERE id = " +
  //           pqxx::to_string(employee_id));

  // Make our change definite.
  // return run();
  // QApplication a(argc, argv);

  // QTranslator translator;
  // const QStringList uiLanguages = QLocale::system().uiLanguages();
  // for (const QString & locale: uiLanguages)
  // {
  //   const QString baseName = "aps_" + QLocale(locale).name();
  //   if (translator.load(":/i18n/" + baseName))
  //   {
  //     a.installTranslator(&translator);
  //     break;
  //   }
  // }
  // MainWindow w;

  // w.show();
  // return a.exec();
}