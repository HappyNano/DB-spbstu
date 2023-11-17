#ifndef DB_GUI_TABLEWINDOW_HPP
#define DB_GUI_TABLEWINDOW_HPP

#include <QWidget>
#include <memory>
#include "DB/tables/tables.hpp"

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

  void _refresh();
};

#endif
