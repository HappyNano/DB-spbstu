#include "DB/connection.hpp"
#include <iostream>

DB::Connection::Connection(const std::string & arg):
  _connection_ptr{},
  _worker_ptr{},
  _is_connected{ false }
{
  try
  {
    _connection_ptr = std::make_unique< pqxx::connection >(arg);
    _worker_ptr = std::make_unique< pqxx::work >(*_connection_ptr);
    _is_connected = true;
  }
  catch (const std::exception & e)
  {
    std::cerr << e.what() << '\n';
    _is_connected = false;
  }
}

bool DB::Connection::is_connected()
{
  return _is_connected;
}

std::shared_ptr< pqxx::connection > DB::Connection::connection()
{
  return _connection_ptr;
}

std::shared_ptr< pqxx::work > DB::Connection::worker()
{
  return _worker_ptr;
}
