#include "DB/GUI/tablewindow.hpp"
#include "./ui_tablewindow.h"
#include <iostream>
#include <QDateTime>

// #define button

TableWindow::TableWindow(const tables_ptr & tables, QWidget * parent):
  QWidget(parent),
  ui(new Ui::TableWindow),
  _tables_ptr{ tables }
{
  ui->setupUi(this);
  ui->tablesBox->addItem("Charges");
  ui->tablesBox->addItem("Expense Items");
  ui->tablesBox->addItem("Sales");
  ui->tablesBox->addItem("Warehouses");

  connect(ui->refreshButton, &QPushButton::clicked, this, &TableWindow::_refresh);
  connect(ui->tablesBox, &QComboBox::currentTextChanged, this, &TableWindow::_refresh);

  // Clear Table
  ui->table->clear();
  ui->table->setRowCount(0);
  ui->table->setColumnCount(0);

  _chargesEdit_dialog = new ChargesEditDialog(_tables_ptr);
  _expenseItemsEdit_dialog = new ExpenseItemsEditDialog(_tables_ptr);
  _salesEdit_dialog = new SalesEditDialog(_tables_ptr);
  _warehousesEdit_dialog = new WarehousesEditDialog(_tables_ptr);
}

TableWindow::~TableWindow()
{
  delete ui;
}

void TableWindow::_refresh()
{
  ui->table->setSortingEnabled(false);
  static auto setIntValue = [](auto & table, int row, int column, auto value)
  {
    auto item = new QTableWidgetItem();
    item->setData(Qt::EditRole, value);
    table->setItem(row, column, item);
  };
  // Clear Table
  ui->table->clear();
  ui->table->setRowCount(0);

  // Set
  auto index = ui->tablesBox->currentIndex();
  switch (index)
  {
  case 0: {
    QStringList headers;
    for (auto && header: _tables_ptr->charges().getHeaders())
    {
      headers << header.c_str();
    }
    headers << "Remove"
            << "Edit";
    ui->table->setColumnCount(headers.size());
    ui->table->setHorizontalHeaderLabels(headers);
    auto rows = _tables_ptr->charges().selectAll();
    ui->table->setRowCount(rows.size());
    for (int i = 0; i < rows.size(); ++i)
    {
      setIntValue(ui->table, i, 0, rows.at(i).id);
      setIntValue(ui->table, i, 1, rows.at(i).amount);
      ui->table->setItem(i, 2, new QTableWidgetItem(QString(rows.at(i).charge_data.c_str())));
      setIntValue(ui->table, i, 3, rows.at(i).expense_item_id);

      {
        QWidget * pWidget = new QWidget();
        QPushButton * btn_remove = new QPushButton();
        connect(btn_remove,
         &QPushButton::clicked,
         [this, id = rows.at(i).id]()
         {
           _tables_ptr->charges().remove(id);
           _refresh();
         });
        btn_remove->setText("x");
        QHBoxLayout * pLayout = new QHBoxLayout(pWidget);
        pLayout->addWidget(btn_remove);
        pLayout->setAlignment(Qt::AlignCenter);
        pLayout->setContentsMargins(3, 3, 3, 3);
        pWidget->setLayout(pLayout);
        ui->table->setCellWidget(i, 4, pWidget);
      }

      {
        QWidget * pWidget = new QWidget();
        QPushButton * btn_edit = new QPushButton();
        connect(btn_edit,
         &QPushButton::clicked,
         [this,
          id = rows.at(i).id,
          amount = rows.at(i).amount,
          date = rows.at(i).charge_data,
          expense_item_id = rows.at(i).expense_item_id]()
         {
           std::string expense_item_str = "";
           for (auto && item: this->_tables_ptr->expense_items().getExpenseItems())
           {
             if (item.first == expense_item_id)
             {
               expense_item_str = item.second;
             }
           }
           QDateTime datetime = QDateTime::fromString(date.c_str(), "yyyy-MM-dd HH:mm:ss");
           if (datetime.toString().isEmpty())
           {
             datetime = QDateTime::fromString(date.c_str(), "yyyy-MM-dd HH:mm:ss.zzz");
           }

           _chargesEdit_dialog->showWithData(id, amount, datetime, expense_item_str);
         });
        btn_edit->setText("Edit");
        QHBoxLayout * pLayout = new QHBoxLayout(pWidget);
        pLayout->addWidget(btn_edit);
        pLayout->setAlignment(Qt::AlignCenter);
        pLayout->setContentsMargins(3, 3, 3, 3);
        pWidget->setLayout(pLayout);
        ui->table->setCellWidget(i, 5, pWidget);
      }
    }
  }
  break;
  case 1: {
    QStringList headers;
    for (auto && header: _tables_ptr->expense_items().getHeaders())
    {
      headers << header.c_str();
    }
    headers << "Remove"
            << "Edit";
    ui->table->setColumnCount(headers.size());
    ui->table->setHorizontalHeaderLabels(headers);
    auto rows = _tables_ptr->expense_items().selectAll();
    ui->table->setRowCount(rows.size());
    for (int i = 0; i < rows.size(); ++i)
    {
      setIntValue(ui->table, i, 0, rows.at(i).id);
      ui->table->setItem(i, 1, new QTableWidgetItem(QString(rows.at(i).name.c_str())));

      {
        QWidget * pWidget = new QWidget();
        QPushButton * btn_remove = new QPushButton();
        connect(btn_remove,
         &QPushButton::clicked,
         [this, id = rows.at(i).id]()
         {
           _tables_ptr->expense_items().remove(id);
           _refresh();
         });
        btn_remove->setText("x");
        QHBoxLayout * pLayout = new QHBoxLayout(pWidget);
        pLayout->addWidget(btn_remove);
        pLayout->setAlignment(Qt::AlignCenter);
        pLayout->setContentsMargins(3, 3, 3, 3);
        pWidget->setLayout(pLayout);
        ui->table->setCellWidget(i, 2, pWidget);
      }

      {
        QWidget * pWidget = new QWidget();
        QPushButton * btn_edit = new QPushButton();
        connect(btn_edit,
         &QPushButton::clicked,
         [this, id = rows.at(i).id, name = rows.at(i).name]()
         {
           _expenseItemsEdit_dialog->showWithData(id, name);
         });
        btn_edit->setText("Edit");
        QHBoxLayout * pLayout = new QHBoxLayout(pWidget);
        pLayout->addWidget(btn_edit);
        pLayout->setAlignment(Qt::AlignCenter);
        pLayout->setContentsMargins(3, 3, 3, 3);
        pWidget->setLayout(pLayout);
        ui->table->setCellWidget(i, 3, pWidget);
      }
    }
  }
  break;
  case 2: {
    QStringList headers;
    for (auto && header: _tables_ptr->sales().getHeaders())
    {
      headers << header.c_str();
    }
    headers << "Remove"
            << "Edit";
    ui->table->setColumnCount(headers.size());
    ui->table->setHorizontalHeaderLabels(headers);
    auto rows = _tables_ptr->sales().selectAll();
    ui->table->setRowCount(rows.size());
    for (int i = 0; i < rows.size(); ++i)
    {
      setIntValue(ui->table, i, 0, rows.at(i).id);
      setIntValue(ui->table, i, 1, rows.at(i).amount);
      setIntValue(ui->table, i, 2, rows.at(i).quantity);
      ui->table->setItem(i, 3, new QTableWidgetItem(QString(rows.at(i).sale_date.c_str())));
      setIntValue(ui->table, i, 4, rows.at(i).warehouse_id);

      {
        QWidget * pWidget = new QWidget();
        QPushButton * btn_remove = new QPushButton();
        connect(btn_remove,
         &QPushButton::clicked,
         [this, id = rows.at(i).id]()
         {
           _tables_ptr->sales().remove(id);
           _refresh();
         });
        btn_remove->setText("x");
        QHBoxLayout * pLayout = new QHBoxLayout(pWidget);
        pLayout->addWidget(btn_remove);
        pLayout->setAlignment(Qt::AlignCenter);
        pLayout->setContentsMargins(3, 3, 3, 3);
        pWidget->setLayout(pLayout);
        ui->table->setCellWidget(i, 5, pWidget);
      }

      {
        QWidget * pWidget = new QWidget();
        QPushButton * btn_edit = new QPushButton();
        connect(btn_edit,
         &QPushButton::clicked,
         [this,
          id = rows.at(i).id,
          quantity = rows.at(i).quantity,
          amount = rows.at(i).amount,
          date = rows.at(i).sale_date,
          product_name_id = rows.at(i).warehouse_id]()
         {
           std::string product_name_str = "";
           for (auto && item: this->_tables_ptr->warehouses().getProducts())
           {
             if (item.first == product_name_id)
             {
               product_name_str = item.second;
             }
           }
           QDateTime datetime = QDateTime::fromString(date.c_str(), "yyyy-MM-dd HH:mm:ss");
           if (datetime.toString().isEmpty())
           {
             datetime = QDateTime::fromString(date.c_str(), "yyyy-MM-dd HH:mm:ss.zzz");
           }

           _salesEdit_dialog->showWithData(id, quantity, amount, datetime, product_name_str);
         });
        btn_edit->setText("Edit");
        QHBoxLayout * pLayout = new QHBoxLayout(pWidget);
        pLayout->addWidget(btn_edit);
        pLayout->setAlignment(Qt::AlignCenter);
        pLayout->setContentsMargins(3, 3, 3, 3);
        pWidget->setLayout(pLayout);
        ui->table->setCellWidget(i, 6, pWidget);
      }
    }
  }
  break;
  case 3: {
    QStringList headers;
    for (auto && header: _tables_ptr->warehouses().getHeaders())
    {
      headers << header.c_str();
    }
    headers << "Remove"
            << "Edit";
    ui->table->setColumnCount(headers.size());
    ui->table->setHorizontalHeaderLabels(headers);
    auto rows = _tables_ptr->warehouses().selectAll();
    ui->table->setRowCount(rows.size());
    for (int i = 0; i < rows.size(); ++i)
    {
      setIntValue(ui->table, i, 0, rows.at(i).id);
      ui->table->setItem(i, 1, new QTableWidgetItem(QString(rows.at(i).name.c_str())));
      setIntValue(ui->table, i, 2, rows.at(i).quantity);
      setIntValue(ui->table, i, 3, rows.at(i).amount);

      {
        QWidget * pWidget = new QWidget();
        QPushButton * btn_remove = new QPushButton();
        connect(btn_remove,
         &QPushButton::clicked,
         [this, id = rows.at(i).id]()
         {
           _tables_ptr->warehouses().remove(id);
           _refresh();
         });
        btn_remove->setText("x");
        QHBoxLayout * pLayout = new QHBoxLayout(pWidget);
        pLayout->addWidget(btn_remove);
        pLayout->setAlignment(Qt::AlignCenter);
        pLayout->setContentsMargins(3, 3, 3, 3);
        pWidget->setLayout(pLayout);
        ui->table->setCellWidget(i, 4, pWidget);
      }

      {
        QWidget * pWidget = new QWidget();
        QPushButton * btn_edit = new QPushButton();
        connect(btn_edit,
         &QPushButton::clicked,
         [this, id = rows.at(i).id, name = rows.at(i).name, quantity = rows.at(i).quantity, amount = rows.at(i).amount]()
         {
           _warehousesEdit_dialog->showWithData(id, name, quantity, amount);
         });
        btn_edit->setText("Edit");
        QHBoxLayout * pLayout = new QHBoxLayout(pWidget);
        pLayout->addWidget(btn_edit);
        pLayout->setAlignment(Qt::AlignCenter);
        pLayout->setContentsMargins(3, 3, 3, 3);
        pWidget->setLayout(pLayout);
        ui->table->setCellWidget(i, 5, pWidget);
      }
    }
  }
  break;

  default:
    break;
  }
  ui->table->resizeColumnsToContents();
  ui->table->setSortingEnabled(true);
}
