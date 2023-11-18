#ifndef DB_GUI_CHARGESEDIT_DIALOG_HPP
#define DB_GUI_CHARGESEDIT_DIALOG_HPP

#include <QDialog>
#include <string>
#include "DB/tables/tables.hpp"
#include "DB/GUI/error_dialog.hpp"

QT_BEGIN_NAMESPACE
namespace Ui
{
  class ChargesEditDialog;
}
QT_END_NAMESPACE

class ChargesEditDialog: public QDialog
{
  Q_OBJECT

 public:
  using tables_ptr = std::shared_ptr< DB::Tables >;

  ChargesEditDialog(const tables_ptr & tables, QWidget * parent = nullptr);
  ~ChargesEditDialog();

  void showWithData(int id, double amount, const QDateTime & datetime, const std::string & expenseItem_str);

 private:
  Ui::ChargesEditDialog * ui;
  tables_ptr _tables_ptr;
  int _id;

  ErrorDialog * _errordialog;

  void _commit();
};

#endif
