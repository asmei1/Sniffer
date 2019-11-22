#include "stdafx.h"
#include "DeviceListWidget.h"
#include "ui_DeviceListWidget.h"


DeviceListWidget::DeviceListWidget(const std::vector<Adapter>& devices, QWidget* parent)
   : QDialog(parent), ui(new Ui::DeviceListWidget())
{
   this->ui->setupUi(this);
   this->setWindowFlag(Qt::WindowContextHelpButtonHint, false);

   this->ui->buttonBox->button(QDialogButtonBox::Ok)->setDisabled(true);
   this->ui->tableWidget_devices->setColumnWidth(NAME_COL, 280);
   this->ui->tableWidget_devices->setColumnWidth(LOOPBACK_COL, 70);

   for(const auto& d : devices)
   {
      int row = this->ui->tableWidget_devices->rowCount();
      this->ui->tableWidget_devices->insertRow(row);
      //name
      auto name = new QTableWidgetItem(d.getName().c_str());
      name->setFlags(name->flags() & ~(Qt::ItemIsEditable));
      this->ui->tableWidget_devices->setItem(row, NAME_COL, name);

      //is loopback
      auto loopBackAlignWidg = new QWidget;
      QHBoxLayout* activeSheetLayout = new QHBoxLayout(loopBackAlignWidg);
      activeSheetLayout->QLayoutItem::setAlignment(Qt::AlignCenter);
      activeSheetLayout->setContentsMargins(0, 0, 0, 0);
      auto loopBack = new QCheckBox;
      loopBack->setDisabled(true);
      loopBack->setCheckState(d.isLoopBack() ? Qt::Checked : Qt::Unchecked);
      activeSheetLayout->addWidget(loopBack);
      this->ui->tableWidget_devices->setCellWidget(row, LOOPBACK_COL, loopBackAlignWidg);

      //desc
      auto desc = new QTableWidgetItem(d.getDescription().c_str());
      desc->setFlags(desc->flags() & ~(Qt::ItemIsEditable));
      this->ui->tableWidget_devices->setItem(row, DESC_COL, desc);


      connect(this->ui->tableWidget_devices->selectionModel(), &QItemSelectionModel::currentRowChanged, [this, devices](const QModelIndex& selected, const QModelIndex&)
         {
            this->ui->plainTextEdit_fullDesc->setVisible(true);
            this->ui->plainTextEdit_fullDesc->setPlainText(devices[selected.row()].getFullDescription().c_str());

            this->ui->buttonBox->button(QDialogButtonBox::Ok)->setDisabled(false);
         });

      connect(this->ui->buttonBox, &QDialogButtonBox::accepted, [this, devices]()
      {
         int row = this->ui->tableWidget_devices->selectedItems()[0]->row();
         this->selectedAdapterName = this->ui->tableWidget_devices->item(row, NAME_COL)->text();

         QDialog::accept();
      });
      connect(this->ui->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
   }
}



DeviceListWidget::~DeviceListWidget()
{
   delete ui;
}

QString DeviceListWidget::getNameOfSelectedAdapter() const
{
   return this->selectedAdapterName;
}
