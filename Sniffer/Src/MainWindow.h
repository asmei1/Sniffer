#pragma once
#include <QMainWindow>

#include "NetworkAdapter.h"

namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow
{
   Q_OBJECT;

public:
    MainWindow(QWidget *parent = Q_NULLPTR);


private slots:
   void on_actionShow_device_list_triggered();


private:
   NetworkAdapter networkAdapter;
   Ui::MainWindow* ui;
};
