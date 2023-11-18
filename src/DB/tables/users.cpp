#include "DB/tables/users.hpp"
#include "DB/utility/md5.h"
#include <stdexcept>
#include "DB/utility/log.hpp"

DB::TableUsers::TableUsers(const pq_worker_ptr & pq_worker):
  _pq_worker{ pq_worker }
{}

void DB::TableUsers::registerUser(const std::string & username, const std::string & password)
{
  if (checkUser(username))
  {
    throw std::logic_error("This user has already registered");
  }
  std::string hash_password = md5(password);
  auto command =
   "INSERT INTO users(username, password) VALUES('" + _pq_worker->esc(username) + "', '" + _pq_worker->esc(hash_password) + "')";
  log::instance() << DateTime{} << Tag{ "Users Class" } << "Query: '" << command << "'\n";
  _pq_worker->exec(command);
}

bool DB::TableUsers::checkUserPassword(const std::string & username, const std::string & password)
{
  std::string hash_password = md5(password);
  auto command =
   "SELECT * FROM users WHERE username='" + _pq_worker->esc(username) + "' AND password='" + _pq_worker->esc(hash_password) + "'";
  log::instance() << DateTime{} << Tag{ "Users Class" } << "Query: '" << command << "'\n";
  auto result = _pq_worker->exec(command);
  return !result.empty();
}

bool DB::TableUsers::checkUser(const std::string & username)
{
  auto command = "SELECT * FROM users WHERE username='" + _pq_worker->esc(username) + "'";
  log::instance() << DateTime{} << Tag{ "Users Class" } << "Query: '" << command << "'\n";
  auto result = _pq_worker->exec(command);
  return !result.empty();
}
