#ifndef DB_GUI_ERRORDIALOG_HPP
#define DB_GUI_ERRORDIALOG_HPP

#include <QDialog>
#include <string>

QT_BEGIN_NAMESPACE
namespace Ui
{
  class ErrorDialog;
}
QT_END_NAMESPACE

class ErrorDialog: public QDialog
{
  Q_OBJECT

 public:
  ErrorDialog(QWidget * parent = nullptr);
  ~ErrorDialog();

  void updateMsg(const std::string & msg);

 private:
  Ui::ErrorDialog * ui;
};

#endif
