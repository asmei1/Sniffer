#include "stdafx.h"
#include "FramesModel.h"
#include <QDebug>
#include <QByteArray>
#include "Structures/EthernetHeader.h"
#include "Printer.h"
#include "Utils/Logger.hpp"
#include "Utils/Helper.h"
#include "TimeFormatter.h"

FramesModel::FramesModel(QObject* parent)
{

}

QVariant FramesModel::headerData(int section, Qt::Orientation orientation, int role) const
{
   if(Qt::DisplayRole != role || Qt::Orientation::Horizontal != orientation)
   {
      return QVariant();
   }

   return this->headers.at(static_cast<HeaderIdx>(section));
}

QVariant FramesModel::data(const QModelIndex& index, int role) const
{
   if(false == index.isValid())
   {
      return QVariant();
   }


   if(Qt::DisplayRole == role)
   {
      qsn::RawFrame* rP = getPacket(index.row());
      qsn::IPv4Header* ipv4 = (qsn::IPv4Header*)(&rP->data[0] + 4);

      switch(static_cast<HeaderIdx>(index.column()))
      {
      case HeaderIdx::LP:
      {
         return index.row();
      }
      case HeaderIdx::TIME:
      {
         return TimeFormatter::time2String(rP->time.tv_sec);
      }
      case HeaderIdx::SRC_ADDR:
      {
         return qsn::ipv42String(ipv4->saddr).c_str();
      }
      case HeaderIdx::DST_ADDR:
      {
         return qsn::ipv42String(ipv4->daddr).c_str();
      }
      case HeaderIdx::PROTOCOL:
      {
         return qsn::protToCStr(ipv4->proto);
      }
      case HeaderIdx::LENGHT:
      {
         return QString::number(rP->caplen);
      }
      case HeaderIdx::INF:
      {
         struct tm* ltime;
         time_t local_tv_sec;
         char timestr[16];
         local_tv_sec = rP->time.tv_sec;
         ltime = localtime(&local_tv_sec);
         strftime(timestr, sizeof timestr, "%H:%M:%S", ltime);

         auto eth = (qsn::EthernetHeader*)(&rP->data[0]);
         
         return qsn::mac2HexString(eth->dest).c_str();
      }
      default:;
      }
      
   }
   else if(Qt::TextAlignmentRole == role)
   {
      if(qsn::ec2Int(HeaderIdx::INF) != index.column())
      {
         return Qt::AlignRight;
      }
      else
      {
         return Qt::AlignLeft;
      }
   }
   else if(Qt::UserRole <= role)
   {
      qsn::RawFrame* rP = getPacket(index.row());
      if(role == PacketsInfo::HEX_CONTENT)
      {
         return qsn::rawData2Hex(&rP->data[0], rP->caplen).c_str();
      }
      else if(role == PacketsInfo::ASCII_CONTENT)
      {
         return qsn::rawData2String(&rP->data[0], rP->caplen).c_str();
      }
   }
   return QVariant();
}

int FramesModel::rowCount(const QModelIndex& parent) const
{
   return this->getPacketsCount();
}

int FramesModel::columnCount(const QModelIndex& parent) const
{
   return this->headers.size();
}


void FramesModel::appendPacket(qsn::RawFrame* packet)
{
   qsn::FramesStash::appendPacket(packet);
   int row = this->getPacketsCount();
   beginInsertRows(QModelIndex(), row, row);

   endInsertRows();
}

void FramesModel::clear()
{
   if(this->getPacketsCount() > 0)
   {
      beginRemoveRows(QModelIndex(), 0, this->getPacketsCount() - 1);
      qsn::FramesStash::clear();

      endRemoveRows();
   }
}
