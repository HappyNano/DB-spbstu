#ifndef DB_TABLE_USERS_HPP
#define DB_TABLE_USERS_HPP

#include <string>
#include <vector>
#include <iosfwd>

#include <pqxx/pqxx>

namespace DB
{
  class TableUsers
  {
   public:
    using this_t = TableUsers;
    using headers_t = std::vector< std::string >;

    using pq_worker_ptr = std::shared_ptr< pqxx::work >;

    TableUsers(const pq_worker_ptr & pq_worker);

    TableUsers(const this_t &) = delete;
    TableUsers(this_t &&) noexcept = delete;

    this_t & operator=(const this_t &) = delete;
    this_t & operator=(this_t &&) noexcept = delete;

    void registerUser(const std::string & username, const std::string & password);
    bool checkUserPassword(const std::string & username, const std::string & password);
    bool checkUser(const std::string & username);

   private:
    pq_worker_ptr _pq_worker;
  };
}

#endif
