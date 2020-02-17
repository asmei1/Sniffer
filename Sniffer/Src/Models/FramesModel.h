#pragma once
#include "stdafx.h"
#include <QAbstractTableModel>
#include "FramesStash.h"

namespace qsn {
   struct RawFrame;
}

class FramesModel : public QAbstractTableModel, public qsn::FramesStash
{
   Q_OBJECT;
public:
   FramesModel(QObject* parent = nullptr);
   ~FramesModel() = default;

   QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

   QVariant data(const QModelIndex& index, int role) const override;

   int rowCount(const QModelIndex& parent) const override;
   int columnCount(const QModelIndex& parent) const override;

   //bool insertRows(int row, int count, const QModelIndex& parent) override;

   void appendPacket(qsn::RawFrame* packet) override;
   void clear() override;


   enum PacketsInfo
   {
      HEX_CONTENT = Qt::UserRole,
      ASCII_CONTENT
   };

private:
   enum class HeaderIdx
   {
      LP = 0,
      TIME,
      SRC_ADDR,
      DST_ADDR,
      PROTOCOL,
      LENGHT,
      SRC_MAC,
      DST_MAC,
      INF,
   };
   const std::map<HeaderIdx, QString> headers =
   {
      {HeaderIdx::LP ,"Lp."},
      {HeaderIdx::TIME ,"Time"},
      {HeaderIdx::SRC_ADDR ,"Source address"},
      {HeaderIdx::DST_ADDR ,"Destination address"},
      {HeaderIdx::PROTOCOL ,"Protocol"},
      {HeaderIdx::LENGHT ,"Len"},
      {HeaderIdx::SRC_MAC ,"Src mac"},
      {HeaderIdx::DST_MAC ,"Dst mac"},
      {HeaderIdx::INF ,"Information"}
   };
};

