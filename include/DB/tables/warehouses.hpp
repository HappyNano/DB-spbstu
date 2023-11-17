#ifndef DB_TABLE_WAREHOUSES_HPP
#define DB_TABLE_WAREHOUSES_HPP

#include <string>
#include <vector>
#include <set>
#include <iosfwd>

#include <pqxx/pqxx>

namespace DB
{
  struct WarehousesRow
  {
    int id;
    std::string name;
    int quantity;
    double amount;

    WarehousesRow(pqxx::const_result_iterator::reference & res);
  };

  std::ostream & operator<<(std::ostream & out, const WarehousesRow & row);

  class TableWarehouses
  {
   public:
    using this_t = TableWarehouses;
    using headers_t = std::vector< std::string >;
    using row_t = WarehousesRow;

    using pq_worker_ptr = std::shared_ptr< pqxx::work >;

    TableWarehouses(const pq_worker_ptr & pq_worker);

    TableWarehouses(const this_t &) = delete;
    TableWarehouses(this_t &&) noexcept = delete;

    this_t & operator=(const this_t &) = delete;
    this_t & operator=(this_t &&) noexcept = delete;

    const headers_t & getHeaders() const;

    std::vector< row_t > selectAll();
    std::set< std::pair< int, std::string > > getProducts();

    void insert(const std::string & name, int quantity, double amount);
    void remove(int id);

   private:
    pq_worker_ptr _pq_worker;
    headers_t _headers;
  };
}

#endif
