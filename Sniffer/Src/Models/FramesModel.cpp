#include "stdafx.h"
#include "FramesModel.h"
#include <QDebug>
#include <QByteArray>
#include "Structures/EthernetHeader.h"
#include "Printer.h"
#include "Utils/Logger.hpp"
#include "Utils/Helper.h"
#include "TimeFormatter.h"
#include "FrameParser.h"

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
      auto frame = qsn::FrameParser::getInstance().parse(rP);

      switch(static_cast<HeaderIdx>(index.column()))
      {
         case HeaderIdx::LP:
         {
            //+ 1 to skip 0 
            return index.row() + 1;
         }
         case HeaderIdx::TIME:
         {
            return TimeFormatter::time2String(frame->getRawTime().tv_sec);
         }
         case HeaderIdx::SRC_ADDR:
         {
            const auto& packet = frame->getPacket();
            if(true == frame->isValid() && true == packet.has_value())
            {
               auto srcAddr = packet->getSrcAddr();
               if(true == srcAddr.has_value())
               {
                  return qsn::ipv42String(*srcAddr).c_str();
               }
            }
            break;
         }
         case HeaderIdx::DST_ADDR:
         {
            const auto& packet = frame->getPacket();
            if(true == frame->isValid() && true == packet.has_value())
            {
               const auto& dstAddr = packet->getDstAddr();
               if(true == dstAddr.has_value())
               {
                  return qsn::ipv42String(*dstAddr).c_str();
               }
            }
            break;
         }
         case HeaderIdx::PROTOCOL:
         {
            return qsn::protToCStr(frame->getPacket()->getProtocalNumber());
         }
         case HeaderIdx::LENGHT:
         {
            return QString::number(rP->caplen);
         }
         case HeaderIdx::SRC_MAC:
         {
            auto srcMac = frame->getMacSrcAddr();
            return qsn::mac2HexString(*srcMac).c_str();
         }
         case HeaderIdx::DST_MAC:
         {
            auto dstMac = frame->getMacDstAddr();
            return qsn::mac2HexString(*dstMac).c_str();
         }
         case HeaderIdx::INF:
         {
            auto dstMac = frame->getMacDstAddr();
            auto srcMac = frame->getMacSrcAddr();
            if(dstMac && srcMac)
            {
               return "";
            }
            else
            {
               return "Loopback";
            }
         }
         default:;
      }

   }
   else if(Qt::TextAlignmentRole == role)
   {
      if(qsn::ec2Int(HeaderIdx::INF) != index.column())
      {
         return int(Qt::AlignRight | Qt::AlignVCenter);
      }
      else
      {
         return int(Qt::AlignLeft | Qt::AlignVCenter);;
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
      else if(role == PacketsInfo::RAW_PTR)
      {
         return QVariant::fromValue((void*)rP);
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
