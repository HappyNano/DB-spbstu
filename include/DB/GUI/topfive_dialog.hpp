#ifndef DB_GUI_TOPFIVE_DIALOG_HPP
#define DB_GUI_TOPFIVE_DIALOG_HPP

#include <QDialog>
#include <string>
#include "DB/connection.hpp"

QT_BEGIN_NAMESPACE
namespace Ui
{
  class TopFiveDialog;
}
QT_END_NAMESPACE

class TopFiveDialog: public QDialog
{
  Q_OBJECT

 public:
  TopFiveDialog(const DB::Connection::shared & connection_ptr, QWidget * parent = nullptr);
  ~TopFiveDialog();

 private:
  Ui::TopFiveDialog * ui;
  DB::Connection::shared _connection_ptr;

  void _get();
};

#endif
