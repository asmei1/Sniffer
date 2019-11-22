#include "stdafx.h"
#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Logger.hpp"
#include "DeviceListWidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
   this->ui->setupUi(this);
   connect(&Logger::getInstance(), &Logger::log, this->ui->logWidget, &LogWidget::logQStr);


   if(false == this->networkAdapter.loadAllDevices())
   {
      emit Logger::getInstance().log(this->networkAdapter.getLastErrorInfo().c_str(), LogWidget::LogLevel::ERR);
   }
   else
   {
      emit Logger::getInstance().log(QString("Found %1 devices.").arg(this->networkAdapter.getAllAdapters().size()), LogWidget::LogLevel::INFO);
   }
}


void MainWindow::on_actionShow_device_list_triggered()
{
   DeviceListWidget dLWidg(this->networkAdapter.getAllAdapters());
   if(QDialog::DialogCode::Accepted == dLWidg.exec())
   {
      emit Logger::getInstance().log(QString("Selected device: %1").arg(dLWidg.getNameOfSelectedAdapter()), LogWidget::LogLevel::INFO);
   }
}
