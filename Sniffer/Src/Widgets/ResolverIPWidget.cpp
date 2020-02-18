#include "stdafx.h"
#include "ResolverIPWidget.h"
#include "ui_ResolverIPWidget.h"
#include "FrameParser.h"
#include "FramesStash.h"
#include <QHostInfo>
#include "Printer.h"

ResolverIPWidget::ResolverIPWidget(qsn::FramesStash* stash, QWidget* parent) :
   QDialog(parent),
   ui(new Ui::ResolverIPWidget)
{
   ui->setupUi(this);
   auto horH = this->ui->tableWidget->horizontalHeader();
   for(int i = 0; i < this->ui->tableWidget->model()->columnCount(); i++)
   {
      horH->setSectionResizeMode(i, QHeaderView::ResizeToContents);
   }
   horH->setSectionResizeMode(this->ui->tableWidget->model()->columnCount() - 1, QHeaderView::Interactive);


   for(const auto& f : stash->getPackets())
   {
      const auto& frame = qsn::FrameParser::getInstance().parse(f);
      const auto& packet = frame->getPacket();

      if(true == frame->isValid() && true == packet.has_value())
      {
         auto srcAddr = packet->getSrcAddr();
         if(true == srcAddr.has_value())
         {
            if(this->data.count(*srcAddr) > 0)
            {
               this->data[*srcAddr].first++;
            }
            else
            {
               this->data[*srcAddr].first = 1;
               this->data[*srcAddr].second = QHostInfo::fromName(qsn::ipv42String(*srcAddr).c_str()).hostName();
            }
       //     return qsn::ipv42String(*srcAddr).c_str();
         }
      }
   }


   int row = 0;
   for(const auto& p : this->data)
   {
      this->ui->tableWidget->insertRow(row);

      this->ui->tableWidget->setItem(row, 0, new QTableWidgetItem(qsn::ipv42String(p.first).c_str()));
      this->ui->tableWidget->setItem(row, 1, new QTableWidgetItem(QString::number(p.second.first)));
      this->ui->tableWidget->setItem(row, 2, new QTableWidgetItem(p.second.second));

      row++;
   }
}

ResolverIPWidget::~ResolverIPWidget()
{
   delete ui;
}
