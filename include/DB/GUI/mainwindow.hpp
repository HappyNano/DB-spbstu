#ifndef DB_GUI_MAINWINDOW_HPP
#define DB_GUI_MAINWINDOW_HPP

#include <QMainWindow>
#include <QStandardItemModel>

QT_BEGIN_NAMESPACE
namespace Ui
{
  class MainWindow;
}
QT_END_NAMESPACE

class MainWindow: public QMainWindow
{
  Q_OBJECT

 public:
  MainWindow(QWidget * parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow * ui;
  QStandardItemModel * model;

};

#endif
