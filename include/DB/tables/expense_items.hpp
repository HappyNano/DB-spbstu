#ifndef DB_TABLE_EXPENSE_ITEMS_HPP
#define DB_TABLE_EXPENSE_ITEMS_HPP

#include <string>
#include <vector>
#include <set>
#include <iosfwd>

#include <pqxx/pqxx>

namespace DB
{
  struct ExpenseItemsRow
  {
    int id;
    std::string name;

    ExpenseItemsRow(pqxx::const_result_iterator::reference & res);
  };

  std::ostream & operator<<(std::ostream & out, const ExpenseItemsRow & row);

  class TableExpenseItems
  {
   public:
    using this_t = TableExpenseItems;
    using headers_t = std::vector< std::string >;
    using row_t = ExpenseItemsRow;

    using pq_worker_ptr = std::shared_ptr< pqxx::work >;

    TableExpenseItems(const pq_worker_ptr & pq_worker);

    TableExpenseItems(const this_t &) = delete;
    TableExpenseItems(this_t &&) noexcept = delete;

    this_t & operator=(const this_t &) = delete;
    this_t & operator=(this_t &&) noexcept = delete;

    const headers_t & getHeaders() const;

    std::vector< row_t > selectAll();

    std::set< std::pair< int, std::string > > getExpenseItems();

    void insert(const std::string & name);
    void remove(int id);
    void update(int id, const std::string & name);

   private:
    pq_worker_ptr _pq_worker;
    headers_t _headers;
  };
}

#endif
