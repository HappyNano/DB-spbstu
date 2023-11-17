#ifndef DB_GUI_MAINWINDOW_HPP
#define DB_GUI_MAINWINDOW_HPP

#include <QMainWindow>
#include <QStandardItemModel>
#include "DB/GUI/tablewindow.hpp"
#include "DB/GUI/error_dialog.hpp"
#include "DB/GUI/login_dialog.hpp"
#include "DB/GUI/editorwindow.hpp"
#include "DB/connection.hpp"

QT_BEGIN_NAMESPACE
namespace Ui
{
  class MainWindow;
}
QT_END_NAMESPACE

class MainWindow: public QMainWindow
{
  Q_OBJECT

 public:
  MainWindow(const DB::Connection::shared & connection_ptr, QWidget * parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow * ui;
  QStandardItemModel * model;

  DB::Connection::shared _connection_ptr;
  std::shared_ptr< DB::Tables > _tables_ptr;

  TableWindow * _tablewindow;
  ErrorDialog * _errordialog;
  LoginDialog * _logindialog;
  EditorWindow * _editorwindow;
};

#endif
