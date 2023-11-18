#include "DB/connection.hpp"
#include "DB/utility/ini.h"
#include <iostream>

DB::Connection::Connection(const std::string & filename):
  _connection_ptr{},
  _worker_ptr{},
  _is_connected{ false }
{
  mINI::INIFile file(filename);
  mINI::INIStructure ini;
  file.read(ini);
  std::string dbname = ini["database"]["db"];
  std::string user = ini["database"]["user"];
  std::string password = ini["database"]["password"];
  std::string host = ini["database"]["host"];
  std::string port = ini["database"]["port"];

  std::string arg =
   std::string("dbname = ") + dbname + " user = " + user + " password = " + password + " hostaddr = " + host + " port = " + port;
  try
  {
    _connection_ptr = std::make_unique< pqxx::connection >(arg);
    _worker_ptr = std::make_unique< pqxx::nontransaction >(*_connection_ptr);
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

std::shared_ptr< pqxx::nontransaction > DB::Connection::worker()
{
  return _worker_ptr;
}
