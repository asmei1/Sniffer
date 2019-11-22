#pragma once
#include <QDialog>
#include "Adapter.h"


namespace Ui { class DeviceListWidget; };
class DeviceListWidget : public QDialog
{
   Q_OBJECT

public:
   DeviceListWidget(const std::vector<Adapter>& devices, QWidget* parent = Q_NULLPTR);
   ~DeviceListWidget();

   QString getNameOfSelectedAdapter() const;

   enum
   {
      NAME_COL = 0,
      LOOPBACK_COL,
      DESC_COL
   };

private:
   QString selectedAdapterName;
   Ui::DeviceListWidget* ui;
};
