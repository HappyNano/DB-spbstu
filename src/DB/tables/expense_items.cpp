#include "DB/tables/expense_items.hpp"
#include "DB/utility/log.hpp"

std::ostream & DB::operator<<(std::ostream & out, const ExpenseItemsRow & row)
{
  out << row.id << ' ';
  out << row.name;
  return out;
}

DB::ExpenseItemsRow::ExpenseItemsRow(pqxx::const_result_iterator::reference & res):
  id{ res[0].as< int >() },
  name{ res[1].as< std::string >() }
{}

DB::TableExpenseItems::TableExpenseItems(const pq_worker_ptr & pq_worker):
  _pq_worker{ pq_worker },
  _headers{ std::initializer_list< std::string >{ "id", "name" } }
{}

const typename DB::TableExpenseItems::headers_t & DB::TableExpenseItems::getHeaders() const
{
  return _headers;
}

std::vector< typename DB::TableExpenseItems::row_t > DB::TableExpenseItems::selectAll()
{
  log::instance() << DateTime{} << Tag{ "ExpenseItems Class" } << "Query: "
                  << "'SELECT * FROM expense_items'\n";
  auto result = _pq_worker->exec("SELECT * FROM expense_items");

  std::vector< row_t > rows;
  for (auto && res: result)
  {
    rows.emplace_back(res);
  }

  return rows;
}

std::set< std::pair< int, std::string > > DB::TableExpenseItems::getExpenseItems()
{
  std::set< std::pair< int, std::string > > expense_items;
  auto all = selectAll();
  for (auto && row: all)
  {
    expense_items.insert({ row.id, row.name });
  }
  return expense_items;
}

void DB::TableExpenseItems::insert(const std::string & name)
{
  auto command = "INSERT INTO expense_items(name) VALUES('" + _pq_worker->esc(name) + "')";
  log::instance() << DateTime{} << Tag{ "ExpenseItems Class" } << "Query: '" << command << "'\n";
  _pq_worker->exec(command);
}

void DB::TableExpenseItems::remove(int id)
{
  auto command = "DELETE FROM expense_items WHERE id = " + std::to_string(id);
  log::instance() << DateTime{} << Tag{ "ExpenseItems Class" } << "Query: '" << command << "'\n";
  _pq_worker->exec(command);
}

void DB::TableExpenseItems::update(int id, const std::string & name)
{
  auto command = "UPDATE expense_items SET name='" + _pq_worker->esc(name) + "' WHERE id=" + std::to_string(id);
  log::instance() << DateTime{} << Tag{ "ExpenseItems Class" } << "Query: '" << command << "'\n";
  _pq_worker->exec(command);
}
