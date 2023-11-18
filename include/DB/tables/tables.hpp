#ifndef DB_TABLES_TABLES_HPP
#define DB_TABLES_TABLES_HPP

#include "DB/tables/charges.hpp"
#include "DB/tables/expense_items.hpp"
#include "DB/tables/sales.hpp"
#include "DB/tables/warehouses.hpp"
#include "DB/tables/users.hpp"

namespace DB
{
  class Tables
  {
   public:
    using this_t = Tables;
    using pq_worker_ptr = std::shared_ptr< pqxx::nontransaction >;

    Tables(const pq_worker_ptr & pq_worker);

    Tables(const this_t &) = delete;
    Tables(this_t &&) noexcept = delete;

    this_t & operator=(const this_t &) = delete;
    this_t & operator=(this_t &&) noexcept = delete;

    TableCharges & charges();
    TableExpenseItems & expense_items();
    TableSales & sales();
    TableWarehouses & warehouses();
    TableUsers & users();

   private:
    TableCharges _charges;
    TableExpenseItems _expense_items;
    TableSales _sales;
    TableWarehouses _warehouses;
    TableUsers _users;
  };
}

#endif
