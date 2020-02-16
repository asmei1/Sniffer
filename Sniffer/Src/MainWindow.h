#pragma once
#include <QMainWindow>

#include "AdapterManager.h"
#include "FrameListener.h"

class FramesModel;

namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow
{
   Q_OBJECT;
 
public:
   void prepareStatusBarWidgets();
   MainWindow(QWidget* parent = Q_NULLPTR);
   ~MainWindow();


private slots:
   void on_actionShow_device_list_triggered();
   void on_actionStart_listening_triggered();
   void on_actionStop_listening_triggered();


   void on_actionQuit_triggered();

   void on_actionLog_window_triggered();

   void tableViewSelectionChanged(const QModelIndex &index);

   void on_actionClear_all_packets_triggered();

private:
   enum class AppStatus
   {
      Init,
      Listening,
      Stopped,
   };

   void setAppStatus(const AppStatus& appStatus)
   void openSelectedAdapter(const std::string& adapterName);

   Ui::MainWindow* ui;
   
   QWidget* statusBarPermanentWidget = nullptr;
   QLabel* statusListenerLabel = nullptr;
   QLabel* openedAdapterLabel = nullptr;


   QString selectedAdapterName;
   qsn::FrameListener* packetListener = nullptr;
   qsn::AdapterManager networkAdapter;
   FramesModel* packetsModel = nullptr;
};
