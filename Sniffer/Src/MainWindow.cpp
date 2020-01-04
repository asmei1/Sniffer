#include "stdafx.h"
#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Utils/Logger.hpp"
#include "Widgets/DeviceListWidget.h"
#include "Models/FramesModel.h"
#include <QDebug>


MainWindow::MainWindow(QWidget* parent)
   : QMainWindow(parent), ui(new Ui::MainWindow)
{
   this->ui->setupUi(this);
   this->ui->actionStart_listening->setEnabled(false);
   this->ui->actionStop_listening->setEnabled(false);
   this->ui->dockWidget_logger->hide();

   prepareStatusBarWidgets();


#ifdef _DEBUG
   this->ui->dockWidget_logger->show();
#endif

   this->ui->actionLog_window->setChecked(this->ui->dockWidget_logger->isVisible());

   connect(&Logger::getInstance(), &Logger::log, this->ui->logWidget, &LogWidget::logQStr);

   try
   {
      this->networkAdapter.loadAllDevices();
      emit Logger::getInstance().log(QString("Found %1 devices.").arg(this->networkAdapter.getAllAdapters().size()), LogWidget::LogLevel::INFO);
   }
   catch(const std::exception & e)
   {
      emit Logger::getInstance().log(e.what(), LogWidget::LogLevel::ERR);
   }

   //connect(&this->packetListener, &qsn::FrameListener::rawPacketSig, this->ui->plainTextEdit_tempInfoBox, &QPlainTextEdit::appendPlainText);

   this->packetsModel = new FramesModel(this);
   this->packetListener = new qsn::FrameListener(this->packetsModel);

   this->ui->tableView_packets->setModel(this->packetsModel);

   //on_actionShow_device_list_triggered();

}

MainWindow::~MainWindow()
{
   delete this->packetListener;
   delete this->packetsModel;
   delete this->statusListenerLabel;
   delete this->openedAdapterLabel;
   delete this->statusBarPermanentWidget;

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

void MainWindow::prepareStatusBarWidgets()
{
   this->statusBarPermanentWidget = new QWidget;
   this->statusBarPermanentWidget->setFixedHeight(20);
   this->openedAdapterLabel = new QLabel("None");
   this->statusListenerLabel = new QLabel;
   this->statusListenerLabel->setPixmap(QPixmap(":/gray_circle"));
   this->statusListenerLabel->setToolTip("Not selected adapter to listening");
   auto pernamentWidgetLayout = new QHBoxLayout;
   pernamentWidgetLayout->setMargin(0);
   pernamentWidgetLayout->setContentsMargins(0, 0, 0, 0);
   pernamentWidgetLayout->addWidget(this->openedAdapterLabel);
   pernamentWidgetLayout->addWidget(this->statusListenerLabel);
   this->statusBarPermanentWidget->setLayout(pernamentWidgetLayout);
   this->statusBar()->addPermanentWidget(this->statusBarPermanentWidget);
}

void MainWindow::on_actionStart_listening_triggered()
{
   this->packetListener->initListener(this->networkAdapter.getOpenedAdapter());
   on_actionClear_all_packets_triggered();
   this->packetListener->startListening();
   this->statusListenerLabel->setPixmap(QPixmap(":/green_circle"));
   this->statusListenerLabel->setToolTip("Listening");
}


void MainWindow::on_actionStop_listening_triggered()
{
   this->packetListener->stopListening();
   this->statusListenerLabel->setPixmap(QPixmap(":/red_circle"));
   this->statusListenerLabel->setToolTip("Stopped");
}

void MainWindow::openSelectedAdapter(const std::string& adapterName)
{
   try
   {
      //try to open selected adapter
      this->networkAdapter.openAdapter(adapterName);

      const auto* adapter = this->networkAdapter.getOpenedAdapter();

      //set label
      this->openedAdapterLabel->setToolTip(adapter->getFullDescription().c_str());
      this->openedAdapterLabel->setText(adapter->getName().c_str());

      //enable actions
      this->ui->actionStart_listening->setEnabled(true);
      this->ui->actionStop_listening->setEnabled(true);

      emit Logger::getInstance().log(QString("Adapter %1 opened successfully.").arg(adapter->getName().c_str()), LogWidget::LogLevel::INFO);
   }
   catch(const std::exception & e)
   {
      emit Logger::getInstance().log(QString("Error during opening adapter: %1").arg(e.what()), LogWidget::LogLevel::ERR);
   }
}

void MainWindow::on_actionQuit_triggered()
{
   QApplication::quit();
}

void MainWindow::on_actionLog_window_triggered()
{
   if(true == this->ui->actionLog_window->isChecked())
   {
      this->ui->dockWidget_logger->show();
   }
   else
   {
      this->ui->dockWidget_logger->hide();
   }
}

void MainWindow::on_tableView_packets_clicked(const QModelIndex &index)
{
   if(true == index.isValid())
   {
      this->ui->plainTextEdit_hexContent->setPlainText(this->packetsModel->data(index, FramesModel::PacketsInfo::HEX_CONTENT).toString());
      this->ui->plainTextEdit_asciiContent->setPlainText(this->packetsModel->data(index, FramesModel::PacketsInfo::ASCII_CONTENT).toString());
   }
   else
   {
      QApplication::beep();
   }
}

void MainWindow::on_actionClear_all_packets_triggered()
{
   if(nullptr != this->packetsModel)
   {
      this->packetsModel->clear();
   }

   this->ui->plainTextEdit_asciiContent->clear();
   this->ui->plainTextEdit_hexContent->clear();
}
