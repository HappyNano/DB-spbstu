#include "DB/tables/sales.hpp"

std::ostream & DB::operator<<(std::ostream & out, const SalesRow & row)
{
  out << row.id << ' ';
  out << row.amount << ' ';
  out << row.quantity << ' ';
  out << row.sale_date << ' ';
  out << row.warehouse_id;
  return out;
}

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

void DB::TableSales::insert(double amount, int quantity, const std::string & sale_date, int warehouse_id)
{
  _pq_worker->exec("INSERT INTO sales(amount, quantity, sale_date, warehouse_id) VALUES(" + std::to_string(amount) + ", " +
                   std::to_string(quantity) + ", '" + _pq_worker->esc(sale_date) + "', " + std::to_string(warehouse_id) + ")");
}

void DB::TableSales::remove(int id)
{
  _pq_worker->exec("DELETE FROM sales WHERE id=" + std::to_string(id));
}

void DB::TableSales::update(int id, double amount, int quantity, const std::string & sale_date, int warehouse_id)
{
  _pq_worker->exec("UPDATE sales SET amount=" + std::to_string(amount) + ", quantity=" + std::to_string(quantity) + ", sale_date='" +
                   _pq_worker->esc(sale_date) + "', warehouse_id=" + std::to_string(warehouse_id) + " WHERE id=" + std::to_string(id));
}
