#include "stdafx.h"
#include "PacketsModel.h"

PacketsModel::PacketsModel(QObject* parent)
{
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
   return QVariant();
}

int PacketsModel::rowCount(const QModelIndex& parent) const
{
   return 0;
}

int PacketsModel::columnCount(const QModelIndex& parent) const
{
   return this->headers.size();
}

bool PacketsModel::insertRows(int row, int count, const QModelIndex& parent)
{
   return false;
}
