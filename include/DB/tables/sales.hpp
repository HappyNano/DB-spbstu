#ifndef DB_TABLE_SALES_HPP
#define DB_TABLE_SALES_HPP

#include <string>
#include <vector>
#include <iosfwd>

#include <pqxx/pqxx>

namespace DB
{
  struct SalesRow
  {
    int id;
    double amount;
    int quantity;
    std::string sale_date;
    int warehouse_id;

    SalesRow(pqxx::const_result_iterator::reference & res);
  };

  std::ostream & operator<<(std::ostream & out, const SalesRow & row);

  class TableSales
  {
   public:
    using this_t = TableSales;
    using headers_t = std::vector< std::string >;
    using row_t = SalesRow;

    using pq_worker_ptr = std::shared_ptr< pqxx::nontransaction >;

    TableSales(const pq_worker_ptr & pq_worker);

    TableSales(const this_t &) = delete;
    TableSales(this_t &&) noexcept = delete;

    this_t & operator=(const this_t &) = delete;
    this_t & operator=(this_t &&) noexcept = delete;

    const headers_t & getHeaders() const;

    std::vector< row_t > selectAll();

    void insert(double amount, int quantity, const std::string & sale_date, int warehouse_id);
    void remove(int id);
    void update(int id, double amount, int quantity, const std::string & sale_date, int warehouse_id);

   private:
    pq_worker_ptr _pq_worker;
    headers_t _headers;
  };
}

#endif
