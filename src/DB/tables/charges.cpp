#include "DB/tables/charges.hpp"

std::ostream & DB::operator<<(std::ostream & out, const ChargesRow & row)
{
  out << row.id << ' ';
  out << row.amount << ' ';
  out << row.charge_data << ' ';
  out << row.expense_item_id;
  return out;
}

DB::ChargesRow::ChargesRow(pqxx::const_result_iterator::reference & res):
  id{ res[0].as< int >() },
  amount{ res[1].as< double >() },
  charge_data{ res[2].as< std::string >() },
  expense_item_id{ res[3].as< int >() }
{}

DB::TableCharges::TableCharges(const pq_worker_ptr & pq_worker):
  _pq_worker{ pq_worker },
  _headers{ { "id", "amount", "charge_date", "expense_item_id" } }
{}

const typename DB::TableCharges::headers_t & DB::TableCharges::getHeaders() const
{
  return _headers;
}

std::vector< typename DB::TableCharges::row_t > DB::TableCharges::selectAll()
{
  auto result = _pq_worker->exec("SELECT * FROM charges");

  std::vector< row_t > rows;
  for (auto && res: result)
  {
    rows.emplace_back(res);
  }

  return rows;
}

void DB::TableCharges::insert(double amount, const std::string & charge_data, int expense_item_id)
{
  _pq_worker->exec("INSERT INTO charges(amount, charge_data, expense_item_id) VALUES(" + std::to_string(amount) + ", '" +
                   _pq_worker->esc(charge_data) + "', " + std::to_string(expense_item_id) + ")");
}

void DB::TableCharges::remove(int id)
{
  _pq_worker->exec("DELETE FROM charges WHERE id = " + std::to_string(id));
}

void DB::TableCharges::update(int id, double amount, const std::string & charge_data, int expense_item_id)
{
  _pq_worker->exec("UPDATE charges SET amount=" + std::to_string(amount) + ", charge_data='" + _pq_worker->esc(charge_data) +
                   "', expense_item_id=" + std::to_string(expense_item_id) + " WHERE id=" + std::to_string(id));
}
