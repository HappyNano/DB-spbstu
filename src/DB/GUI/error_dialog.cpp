#include "DB/GUI/error_dialog.hpp"
#include "./ui_error_dialog.h"
#include <iostream>

ErrorDialog::ErrorDialog(QWidget * parent):
  QDialog(parent),
  ui(new Ui::ErrorDialog)
{
  ui->setupUi(this);

  connect(ui->ok_button,
   &QPushButton::clicked,
   [&]()
   {
     this->close();
   });
}

ErrorDialog::~ErrorDialog()
{
  delete ui;
}

void ErrorDialog::updateMsg(const std::string & msg)
{
  ui->errorMsg->setText(msg.c_str());
}
