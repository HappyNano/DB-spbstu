#ifndef DB_UTILITY_LOG_HPP
#define DB_UTILITY_LOG_HPP

#include <fstream>
#include <string>
#include <ctime>

struct Tag
{
  std::string tag;
};

struct DateTime
{};

std::ofstream & operator<<(std::ofstream & fout, const DateTime &);

class log
{
 public:
  static log & instance();

  friend log & operator<<(log & fout, const std::string & value);
  friend log & operator<<(log & log, const Tag & tag);
  friend log & operator<<(log & log, const DateTime & dt);

 private:
  std::ofstream fout;

  log(const std::string & filename);
  ~log();
  log(const log &) = default;
  log & operator=(log &) = default;
};

log & operator<<(log & log, const std::string & value);
log & operator<<(log & log, const Tag & tag);
log & operator<<(log & log, const DateTime & dt);

#endif
