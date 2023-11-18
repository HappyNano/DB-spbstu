#include "DB/GUI/logswidget.hpp"
#include "./ui_logs.h"
#include <fstream>

LogsWidget::LogsWidget(QWidget * parent):
  QWidget(parent),
  ui(new Ui::LogsWidget)
{
  ui->setupUi(this);
}

LogsWidget::~LogsWidget()
{
  delete ui;
}

void LogsWidget::showLogs()
{
  std::ifstream fin("log");
  ui->logsText->clear();
  std::string str((std::istreambuf_iterator< char >(fin)), std::istreambuf_iterator< char >());
  ui->logsText->setText(str.c_str());
  this->show();
}
