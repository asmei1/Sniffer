#pragma once
#include "stdafx.h"
#include <QAbstractTableModel>

class PacketsModel : public QAbstractTableModel
{
   Q_OBJECT;
public:
   PacketsModel(QObject* parent = nullptr);
   ~PacketsModel() = default;

   QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

   QVariant data(const QModelIndex& index, int role) const override;

   int rowCount(const QModelIndex& parent) const override;
   int columnCount(const QModelIndex& parent) const override;

   bool insertRows(int row, int count, const QModelIndex& parent) override;
      
private:
   const QStringList headers =
   {
      "Lp.",
      "Time",
      "Source address",
      "Destination address",
      "Protocol",
      "Len",
      "Information",
   };

};

