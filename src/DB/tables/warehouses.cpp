#include "DB/tables/warehouses.hpp"

DB::WarehousesRow::WarehousesRow(pqxx::const_result_iterator::reference & res):
  id{ res[0].as< int >() },
  name{ res[1].as< std::string >() },
  quantity{ res[2].as< int >() },
  amount{ res[3].as< double >() }
{}

DB::TableWarehouses::TableWarehouses(const pq_worker_ptr & pq_worker):
  _pq_worker{ pq_worker },
  _headers{ { "id", "name", "quantity", "amount" } }
{}

const typename DB::TableWarehouses::headers_t & DB::TableWarehouses::getHeaders() const
{
  return _headers;
}

std::vector< typename DB::TableWarehouses::row_t > DB::TableWarehouses::selectAll()
{
  auto result = _pq_worker->exec("SELECT * FROM warehouses");

  std::vector< row_t > rows;
  for (auto && res: result)
  {
    rows.emplace_back(res);
  }

  return rows;
}
