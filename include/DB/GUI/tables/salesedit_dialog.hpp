#ifndef DB_GUI_SALESEDIT_DIALOG_HPP
#define DB_GUI_SALESEDIT_DIALOG_HPP

#include <QDialog>
#include <string>
#include "DB/tables/tables.hpp"
#include "DB/GUI/error_dialog.hpp"

QT_BEGIN_NAMESPACE
namespace Ui
{
  class SalesEditDialog;
}
QT_END_NAMESPACE

class SalesEditDialog: public QDialog
{
  Q_OBJECT

 public:
  using tables_ptr = std::shared_ptr< DB::Tables >;

  SalesEditDialog(const tables_ptr & tables, QWidget * parent = nullptr);
  ~SalesEditDialog();

  void showWithData(int id, int quantity, double amount, const QDateTime & sale_date, const std::string & product_name);

 private:
  Ui::SalesEditDialog * ui;
  tables_ptr _tables_ptr;
  int _id;

  ErrorDialog * _errordialog;

  void _commit();
};

#endif
