#include "stdafx.h"
#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Logger.hpp"
#include "Widgets/DeviceListWidget.h"
#include "Models/PacketsModel.h"
#include <QDebug>
#include "Models/PacketsQStash.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
   this->ui->setupUi(this);
   this->ui->actionStart_listening->setEnabled(false);
   this->ui->actionStop_listening->setEnabled(false);


   connect(&Logger::getInstance(), &Logger::log, this->ui->logWidget, &LogWidget::logQStr);

   try
   {
      this->networkAdapter.loadAllDevices();
      emit Logger::getInstance().log(QString("Found %1 devices.").arg(this->networkAdapter.getAllAdapters().size()), LogWidget::LogLevel::INFO);
   }
   catch(const std::exception& e)
   {
      emit Logger::getInstance().log(e.what(), LogWidget::LogLevel::ERR);
   }

   //connect(&this->packetListener, &qsn::PacketListener::rawPacketSig, this->ui->plainTextEdit_tempInfoBox, &QPlainTextEdit::appendPlainText);

   auto test = new PacketsQStash();
   this->packetListener = new qsn::PacketListener(test);

   this->packetsModel = new PacketsModel(test, this);
   this->ui->tableView_packets->setModel(this->packetsModel);
   
   //on_actionShow_device_list_triggered();
}

MainWindow::~MainWindow()
{
   delete this->packetsModel;
   delete this->packetListener;

   delete this->ui;
}

void MainWindow::on_actionShow_device_list_triggered()
{
   DeviceListWidget dLWidg(this->networkAdapter.getAllAdapters());

   if(QDialog::DialogCode::Accepted == dLWidg.exec())
   {
      emit Logger::getInstance().log(QString("Selected device: %1").arg(dLWidg.getNameOfSelectedAdapter()), LogWidget::LogLevel::INFO);

      openSelectedAdapter(dLWidg.getNameOfSelectedAdapter().toStdString());
   }
}


void MainWindow::on_actionStart_listening_triggered()
{
   this->packetListener->initListener(this->networkAdapter.getOpenedAdapter());
   this->packetListener->startListening();
}


void MainWindow::on_actionStop_listening_triggered()
{
   this->packetListener->stopListening();
}

void MainWindow::openSelectedAdapter(const std::string& adapterName)
{
   try
   {
      //try to open selected adapter
      this->networkAdapter.openAdapter(adapterName);

      const auto* adapter = this->networkAdapter.getOpenedAdapter();

      //set label
      this->ui->label_openedAdapter->setToolTip(adapter->getFullDescription().c_str());
      this->ui->label_openedAdapter->setText(QString("Opened adapter: ") + adapter->getName().c_str());

      //enable actions
      this->ui->actionStart_listening->setEnabled(true);
      this->ui->actionStop_listening->setEnabled(true);

      emit Logger::getInstance().log(QString("Adapter %1 opened successfully.").arg(adapter->getName().c_str()), LogWidget::LogLevel::INFO);
   }
   catch (const std::exception& e)
   {
      emit Logger::getInstance().log(QString("Error during opening adapter: %1").arg(e.what()), LogWidget::LogLevel::ERR);
   }
}
