#pragma once
#include <QMainWindow>

#include "AdapterManager.h"
#include "PacketListener.h"

class PacketsModel;

namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow
{
   Q_OBJECT;

public:
   MainWindow(QWidget* parent = Q_NULLPTR);
   ~MainWindow();


private slots:
   void on_actionShow_device_list_triggered();
   void on_actionStart_listening_triggered();
   void on_actionStop_listening_triggered();


private:
   void openSelectedAdapter(const std::string& adapterName);

   Ui::MainWindow* ui;

   PacketListener packetListener;
   AdapterManager networkAdapter;
   PacketsModel* packetsModel = nullptr;
};
