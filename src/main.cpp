#include <iostream>
#include <string>

#include <pqxx/pqxx>

#include "DB/GUI/mainwindow.hpp"
#include "DB/tables/tables.hpp"
#include "DB/connection.hpp"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char * argv[])
{
  auto connection_ptr = std::make_shared< DB::Connection >("config/db.ini");

  // // int employee_id = txn.query_value< int >(
  // //  "SELECT *"
  // //  "FROM warehouses ");

  // DB::TableWarehouses warehouses(worker_ptr);
  // auto result1 = warehouses.selectAll();

  // for (auto && header: warehouses.getHeaders())
  // {
  //   std::cout << header << ' ';
  // }
  // std::cout << '\n';
  // for (auto && row: result1)
  // {
  //   std::cout << row << '\n';
  // }
  // std::cout << '\n';
  // ///////////////////
  // DB::TableCharges charges(worker_ptr);
  // auto result2 = charges.selectAll();

  // for (auto && header: charges.getHeaders())
  // {
  //   std::cout << header << ' ';
  // }
  // std::cout << '\n';
  // for (auto && row: result2)
  // {
  //   std::cout << row << '\n';
  // }
  // std::cout << '\n';
  // ///////////////////
  // DB::TableExpenseItems expense_item(worker_ptr);
  // auto result3 = expense_item.selectAll();

  // for (auto && header: expense_item.getHeaders())
  // {
  //   std::cout << header << ' ';
  // }
  // std::cout << '\n';
  // for (auto && row: result3)
  // {
  //   std::cout << row << '\n';
  // }
  // std::cout << '\n';
  // ///////////////////
  // DB::TableSales sales(worker_ptr);
  // auto result4 = sales.selectAll();

  // for (auto && header: sales.getHeaders())
  // {
  //   std::cout << header << ' ';
  // }
  // std::cout << '\n';
  // for (auto && row: result4)
  // {
  //   std::cout << row << '\n';
  // }
  // std::cout << '\n';

  // c.disconnect();

  // txn.exec0("UPDATE EMPLOYEE "
  //           "SET salary = salary + 1 "
  //           "WHERE id = " +
  //           pqxx::to_string(employee_id));

  // Make our change definite.
  // return run();

  auto tables_ptr = std::make_shared< DB::Tables >(connection_ptr->worker());

  QApplication a(argc, argv);
  MainWindow w(connection_ptr);

  return a.exec();
}