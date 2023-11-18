#include "DB/utility/log.hpp"

namespace
{
  std::string getCurrentDateTime(std::string s)
  {
    std::time_t now = std::time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    if (s == "now")
    {
      strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
    }
    else if (s == "date")
    {
      strftime(buf, sizeof(buf), "%Y-%m-%d", &tstruct);
    }
    return std::string(buf);
  };
}

log::log(const std::string & filename):
  fout{ filename, std::ios::app }
{}

log::~log()
{
  fout.close();
}

// Static function
log & log::instance()
{
  static log instance("log");
  return instance;
}

std::ofstream & operator<<(std::ofstream & fout, const DateTime &)
{
  fout << getCurrentDateTime("now");
  return fout;
}

log & operator<<(log & log, const std::string & value)
{
  log.fout << value;
  return log;
}

log & operator<<(log & log, const Tag & tag)
{
  log.fout << ' ' << '[' << tag.tag << ']' << ' ';
  return log;
}

log & operator<<(log & log, const DateTime & dt)
{
  log.fout << ' ' << '[';
  log.fout << dt;
  log.fout << ']' << ' ';
  return log;
}