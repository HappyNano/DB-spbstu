#ifndef DB_GUI_PROFIT_DIALOG_HPP
#define DB_GUI_PROFIT_DIALOG_HPP

#include <QDialog>
#include <string>
#include "DB/connection.hpp"

QT_BEGIN_NAMESPACE
namespace Ui
{
  class ProfitDialog;
}
QT_END_NAMESPACE

class ProfitDialog: public QDialog
{
  Q_OBJECT

 public:
  ProfitDialog(const DB::Connection::shared & connection_ptr, QWidget * parent = nullptr);
  ~ProfitDialog();

 private:
  Ui::ProfitDialog * ui;
  DB::Connection::shared _connection_ptr;

  void _calc();
};

#endif
