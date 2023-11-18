#ifndef DB_GUI_TABLEWINDOW_HPP
#define DB_GUI_TABLEWINDOW_HPP

#include <QWidget>
#include <memory>
#include "DB/tables/tables.hpp"

#include "DB/GUI/tables/chargesedit_dialog.hpp"
#include "DB/GUI/tables/expenseitemsedit_dialog.hpp"
#include "DB/GUI/tables/salesedit_dialog.hpp"
#include "DB/GUI/tables/warehousesedit_dialog.hpp"

#include "DB/GUI/error_dialog.hpp"

QT_BEGIN_NAMESPACE
namespace Ui
{
  class TableWindow;
}
QT_END_NAMESPACE

class TableWindow: public QWidget
{
  Q_OBJECT

 public:
  using tables_ptr = std::shared_ptr< DB::Tables >;

  TableWindow(const tables_ptr & tables, QWidget * parent = nullptr);
  ~TableWindow();

 private:
  Ui::TableWindow * ui;
  tables_ptr _tables_ptr;

  ChargesEditDialog * _chargesEdit_dialog;
  ExpenseItemsEditDialog * _expenseItemsEdit_dialog;
  SalesEditDialog * _salesEdit_dialog;
  WarehousesEditDialog * _warehousesEdit_dialog;

  ErrorDialog * _error_dialog;

  void _refresh();
};

#endif
