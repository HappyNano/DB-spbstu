#ifndef DB_GUI_EDITORWINDOW_HPP
#define DB_GUI_EDITORWINDOW_HPP

#include <QWidget>
#include <memory>
#include "DB/tables/tables.hpp"

QT_BEGIN_NAMESPACE
namespace Ui
{
  class EditorWindow;
}
QT_END_NAMESPACE

class EditorWindow: public QWidget
{
  Q_OBJECT

 public:
  using tables_ptr = std::shared_ptr< DB::Tables >;

  EditorWindow(const tables_ptr & tables, QWidget * parent = nullptr);
  ~EditorWindow();

 private:
  Ui::EditorWindow * ui;
  tables_ptr _tables_ptr;

  bool _checkCharges();
  bool _checkExpenseItems();
  bool _checkSales();
  bool _checkWarehouses();

  void _insertCharges();
  void _insertExpenseItems();
  void _insertSales();
  void _insertWarehouses();

  void _update();
};

#endif
