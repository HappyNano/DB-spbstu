#include "DB/tables/users.hpp"
#include "DB/utility/md5.h"
#include <stdexcept>

DB::TableUsers::TableUsers(const pq_worker_ptr & pq_worker):
  _pq_worker{ pq_worker }
{}

void DB::TableUsers::registerUser(const std::string & username, const std::string & password)
{
  if (checkUser(username))
  {
    throw std::logic_error("This user has already registered");
  }

  _pq_worker->exec(
   "INSERT INTO users(username, password) VALUES('" + _pq_worker->esc(username) + "', '" + _pq_worker->esc(password) + "')");
}

bool DB::TableUsers::checkUserPassword(const std::string & username, const std::string & password)
{
  std::string hash_password = md5(password);
  auto result = _pq_worker->exec(
   "SELECT * FROM users WHERE username='" + _pq_worker->esc(username) + "' AND password='" + _pq_worker->esc(password) + "'");
  return !result.empty();
}

bool DB::TableUsers::checkUser(const std::string & username)
{
  auto result = _pq_worker->exec("SELECT * FROM users WHERE username='" + _pq_worker->esc(username) + "'");
  return !result.empty();
}
