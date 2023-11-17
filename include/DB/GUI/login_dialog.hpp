#ifndef DB_GUI_LOGINDIALOG_HPP
#define DB_GUI_LOGINDIALOG_HPP

#include <QDialog>
#include <string>
#include "DB/tables/tables.hpp"

QT_BEGIN_NAMESPACE
namespace Ui
{
  class LoginDialog;
}
QT_END_NAMESPACE

class LoginDialog: public QDialog
{
  Q_OBJECT

 public:
  using tables_ptr = std::shared_ptr< DB::Tables >;

  LoginDialog(const tables_ptr & tables, QWidget * parent = nullptr);
  ~LoginDialog();

  bool isLogged() const;

  std::pair< std::string, std::string > getUser() const;

 private:
  Ui::LoginDialog * ui;

  tables_ptr _tables_ptr;
  bool _is_logged;
  std::string _username;
  std::string _password;

  void _login();
  void _register();
  bool _check();
};

#endif
