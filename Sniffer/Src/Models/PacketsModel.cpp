#include "stdafx.h"
#include "PacketsModel.h"
#include "PacketsQStash.h"

PacketsModel::PacketsModel(PacketsQStash* packets, QObject* parent)
{
   this->packets = packets;

   connect(this->packets, &PacketsQStash::appendPacketSig, [&]()
      {
         this->insertRow(this->packets->getPacketsCount());
      });

}

QVariant PacketsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
   if(Qt::DisplayRole != role || Qt::Orientation::Horizontal != orientation)
   {
      return QVariant();
   }

   return this->headers[section];
}

QVariant PacketsModel::data(const QModelIndex& index, int role) const
{
   if(Qt::DisplayRole == role)
   {
      if(0 == index.column())
      {
         return index.row();
      }
      return "Cos";
   }
   return QVariant();
}

int PacketsModel::rowCount(const QModelIndex& parent) const
{
   return this->packets->getPacketsCount();
}

int PacketsModel::columnCount(const QModelIndex& parent) const
{
   return this->headers.size();
}

bool PacketsModel::insertRows(int row, int count, const QModelIndex& parent)
{
   beginInsertRows(QModelIndex(), row, row + count - 1);

   // change the data structure.

   endInsertRows();
   return true;
}
