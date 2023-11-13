#include "DB/tables/expense_items.hpp"

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
  auto result = _pq_worker->exec("SELECT * FROM expense_items");

  std::vector< row_t > rows;
  for (auto && res: result)
  {
    rows.emplace_back(res);
  }

  return rows;
}
