#include "stdafx.h"
#include <type_traits>
#include "PacketsTableView.h"
#include "Models/PacketsModel.h"

PacketsTableView::PacketsTableView(QWidget* parent)
   : QTableView(parent)
{
   horizontalHeader()->setStretchLastSection(true);
}

void PacketsTableView::setModel(QAbstractItemModel* model)
{
   assert(dynamic_cast<PacketsModel*>(model) != nullptr);
   QTableView::setModel(model);

   if(nullptr != model)
   {
      auto horH = horizontalHeader();
      for(int i = 0; i < model->columnCount(); i++)
      {
         horH->setSectionResizeMode(i, QHeaderView::ResizeToContents);
      }
      horH->setSectionResizeMode(model->columnCount() - 1, QHeaderView::Stretch);
   }
}
