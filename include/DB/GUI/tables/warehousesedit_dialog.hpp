#ifndef DB_GUI_WAREHOUSESEDIT_DIALOG_HPP
#define DB_GUI_WAREHOUSESEDIT_DIALOG_HPP

#include <QDialog>
#include <string>
#include "DB/tables/tables.hpp"

QT_BEGIN_NAMESPACE
namespace Ui
{
  class WarehousesEditDialog;
}
QT_END_NAMESPACE

class WarehousesEditDialog: public QDialog
{
  Q_OBJECT

 public:
  using tables_ptr = std::shared_ptr< DB::Tables >;

  WarehousesEditDialog(const tables_ptr & tables, QWidget * parent = nullptr);
  ~WarehousesEditDialog();

  void showWithData(int id, const std::string & name, int quantity, double amount);

 private:
  Ui::WarehousesEditDialog * ui;
  tables_ptr _tables_ptr;
  int _id;

  void _commit();
};

#endif
