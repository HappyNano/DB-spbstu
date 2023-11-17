#ifndef DB_CONNECTION_HPP
#define DB_CONNECTION_HPP

#include <pqxx/pqxx>
#include <memory>

namespace DB
{
  class Connection
  {
   public:
    using this_t = Connection;
    using shared = std::shared_ptr< Connection >;

    Connection(const std::string & arg);

    Connection(const this_t &) = delete;
    Connection(this_t &&) noexcept = delete;

    this_t & operator=(const this_t &) = delete;
    this_t & operator=(this_t &&) noexcept = delete;

    bool is_connected();

    std::shared_ptr< pqxx::connection > connection();
    std::shared_ptr< pqxx::work > worker();

   private:
    std::shared_ptr< pqxx::connection > _connection_ptr;
    std::shared_ptr< pqxx::work > _worker_ptr;

    bool _is_connected;
  };
}

#endif
