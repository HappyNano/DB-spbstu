#ifndef DB_TABLE_CHARGES_HPP
#define DB_TABLE_CHARGES_HPP

#include <string>
#include <vector>
#include <iosfwd>

#include <pqxx/pqxx>

namespace DB
{
  struct ChargesRow
  {
    int id;
    double amount;
    std::string charge_data;
    int expense_item_id;

    ChargesRow(pqxx::const_result_iterator::reference & res);
  };

  std::ostream & operator<<(std::ostream & out, const ChargesRow & row);

  class TableCharges
  {
   public:
    using this_t = TableCharges;
    using headers_t = std::vector< std::string >;
    using row_t = ChargesRow;

    using pq_worker_ptr = std::shared_ptr< pqxx::nontransaction >;

    TableCharges(const pq_worker_ptr & pq_worker);

    TableCharges(const this_t &) = delete;
    TableCharges(this_t &&) noexcept = delete;

    this_t & operator=(const this_t &) = delete;
    this_t & operator=(this_t &&) noexcept = delete;

    const headers_t & getHeaders() const;

    std::vector< row_t > selectAll();

    void insert(double amount, const std::string & charge_data, int expense_item_id);
    void remove(int id);
    void update(int id, double amount, const std::string & charge_data, int expense_item_id);

   private:
    pq_worker_ptr _pq_worker;
    headers_t _headers;
  };
}

#endif
