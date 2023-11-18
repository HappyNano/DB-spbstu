#ifndef DB_GUI_EXPENSEITEMSEDIT_DIALOG_HPP
#define DB_GUI_EXPENSEITEMSEDIT_DIALOG_HPP

#include <QDialog>
#include <string>
#include "DB/tables/tables.hpp"

QT_BEGIN_NAMESPACE
namespace Ui
{
  class ExpenseItemsEditDialog;
}
QT_END_NAMESPACE

class ExpenseItemsEditDialog: public QDialog
{
  Q_OBJECT

 public:
  using tables_ptr = std::shared_ptr< DB::Tables >;

  ExpenseItemsEditDialog(const tables_ptr & tables, QWidget * parent = nullptr);
  ~ExpenseItemsEditDialog();

  void showWithData(int id, const std::string & name);

 private:
  Ui::ExpenseItemsEditDialog * ui;
  tables_ptr _tables_ptr;
  int _id;

  void _commit();
};

#endif
