#include "DB/tables/sales.hpp"

DB::SalesRow::SalesRow(pqxx::const_result_iterator::reference & res):
  id{ res[0].as< int >() },
  amount{ res[1].as< double >() },
  quantity{ res[2].as< int >() },
  sale_date{ res[3].as< std::string >() },
  warehouse_id{ res[4].as< int >() }
{}

DB::TableSales::TableSales(const pq_worker_ptr & pq_worker):
  _pq_worker{ pq_worker },
  _headers{ { "id", "amount", "quantity", "sale_date", "warehouse_id" } }
{}

const typename DB::TableSales::headers_t & DB::TableSales::getHeaders() const
{
  return _headers;
}

std::vector< typename DB::TableSales::row_t > DB::TableSales::selectAll()
{
  auto result = _pq_worker->exec("SELECT * FROM sales");

  std::vector< row_t > rows;
  for (auto && res: result)
  {
    rows.emplace_back(res);
  }

  return rows;
}
