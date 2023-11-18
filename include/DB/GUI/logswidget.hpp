#ifndef DB_GUI_LOGSWIDGET_HPP
#define DB_GUI_LOGSWIDGET_HPP

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui
{
  class LogsWidget;
}
QT_END_NAMESPACE

class LogsWidget: public QWidget
{
  Q_OBJECT

 public:
  LogsWidget(QWidget * parent = nullptr);
  ~LogsWidget();

  void showLogs();

 private:
  Ui::LogsWidget * ui;
};

#endif
