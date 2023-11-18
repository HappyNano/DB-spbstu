#include "DB/tables/tables.hpp"
#include "DB/utility/log.hpp"

DB::Tables::Tables(const pq_worker_ptr & pq_worker):
  _charges{ pq_worker },
  _expense_items{ pq_worker },
  _sales{ pq_worker },
  _warehouses{ pq_worker },
  _users{ pq_worker }
{
  log::instance() << DateTime{} << Tag{ "Tables" } << "Created Tables Class\n";
}

DB::TableCharges & DB::Tables::charges()
{
  return _charges;
}
DB::TableExpenseItems & DB::Tables::expense_items()
{
  return _expense_items;
}
DB::TableSales & DB::Tables::sales()
{
  return _sales;
}
DB::TableWarehouses & DB::Tables::warehouses()
{
  return _warehouses;
}
DB::TableUsers & DB::Tables::users()
{
  return _users;
}