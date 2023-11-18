#include "DB/tables/warehouses.hpp"
#include "DB/utility/log.hpp"

std::ostream & DB::operator<<(std::ostream & out, const WarehousesRow & row)
{
  out << row.id << ' ';
  out << row.name << ' ';
  out << row.quantity << ' ';
  out << row.amount;
  return out;
}

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
  auto command = "SELECT * FROM warehouses";
  log::instance() << DateTime{} << Tag{ "Warehouses Class" } << "Query: '" << command << "'\n";
  auto result = _pq_worker->exec(command);

  std::vector< row_t > rows;
  for (auto && res: result)
  {
    rows.emplace_back(res);
  }

  return rows;
}

std::set< std::pair< int, std::string > > DB::TableWarehouses::getProducts()
{
  std::set< std::pair< int, std::string > > products;
  auto all = selectAll();
  for (auto && row: all)
  {
    products.insert({ row.id, row.name });
  }
  return products;
}

void DB::TableWarehouses::insert(const std::string & name, int quantity, double amount)
{
  auto command = "INSERT INTO warehouses(name, quantity, amount) VALUES('" + _pq_worker->esc(name) + "', " + std::to_string(quantity) +
                 ", " + std::to_string(amount) + ")";
  log::instance() << DateTime{} << Tag{ "Warehouses Class" } << "Query: '" << command << "'\n";
  _pq_worker->exec(command);
}

void DB::TableWarehouses::remove(int id)
{
  auto command = "DELETE FROM warehouses WHERE id=" + std::to_string(id);
  log::instance() << DateTime{} << Tag{ "Warehouses Class" } << "Query: '" << command << "'\n";
  _pq_worker->exec(command);
}

void DB::TableWarehouses::update(int id, const std::string & name, int quantity, double amount)
{
  auto command = "UPDATE warehouses SET name='" + _pq_worker->esc(name) + "', quantity=" + std::to_string(quantity) +
                 ", amount=" + std::to_string(amount) + " WHERE id=" + std::to_string(id);
  log::instance() << DateTime{} << Tag{ "Warehouses Class" } << "Query: '" << command << "'\n";
  _pq_worker->exec(command);
}
