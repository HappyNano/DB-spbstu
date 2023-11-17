#include "DB/GUI/login_dialog.hpp"
#include "./ui_login.h"
#include <iostream>
#include <QtWidgets>

LoginDialog::LoginDialog(const tables_ptr & tables, QWidget * parent):
  QDialog(parent),
  ui(new Ui::LoginDialog),
  _tables_ptr(tables),
  _is_logged(false),
  _username{},
  _password{}
{
  ui->setupUi(this);
  connect(ui->loginbutton, &QPushButton::clicked, this, &LoginDialog::_login);
  connect(ui->registerbutton, &QPushButton::clicked, this, &LoginDialog::_register);
}

LoginDialog::~LoginDialog()
{
  delete ui;
}

bool LoginDialog::isLogged() const
{
  return _is_logged;
}

std::pair< std::string, std::string > LoginDialog::getUser() const
{
  return { _username, _password };
}

void LoginDialog::_login()
{
  if (!_check())
  {
    return;
  }
  std::string username = ui->username->text().toStdString();
  std::string password = ui->password->text().toStdString();
  _is_logged = _tables_ptr->users().checkUserPassword(username, password);
  if (_is_logged)
  {
    _username = username;
    _password = password;
    this->close();
  }
  else
  {
    ui->username->setStyleSheet(ui->username->styleSheet() + "#username {border: 2px solid red;}");
    ui->password->setStyleSheet(ui->password->styleSheet() + "#password {border: 2px solid red;}");
  }
}

void LoginDialog::_register()
{
  if (!_check())
  {
    return;
  }
  std::string username = ui->username->text().toStdString();
  std::string password = ui->password->text().toStdString();
  _tables_ptr->users().registerUser(username, password);
  _is_logged = true;
  _username = username;
  _password = password;
  this->close();
}

bool LoginDialog::_check()
{
  bool has_username = !ui->username->text().isEmpty();
  bool has_password = !ui->password->text().isEmpty();

  if (!has_username)
  {
    ui->username->setStyleSheet(ui->username->styleSheet() + "#username {border: 2px solid red;}");
  }

  if (!has_password)
  {
    ui->password->setStyleSheet(ui->password->styleSheet() + "#password {border: 2px solid red;}");
  }

  return has_username && has_password;
}
