#include "stdafx.h"
#include <type_traits>
#include "FramesTableView.h"
#include "Models/FramesModel.h"

FramesTableView::FramesTableView(QWidget* parent)
   : QTableView(parent)
{
   horizontalHeader()->setStretchLastSection(true);
   this->verticalHeader()->setDefaultSectionSize(10);
}

void FramesTableView::setModel(QAbstractItemModel* model)
{
   assert(dynamic_cast<FramesModel*>(model) != nullptr);
   QTableView::setModel(model);

   if(nullptr != model)
   {
      auto horH = horizontalHeader();
      for(int i = 0; i < model->columnCount(); i++)
      {
         horH->setSectionResizeMode(i, QHeaderView::ResizeToContents);
      }
      horH->setSectionResizeMode(model->columnCount() - 1, QHeaderView::Interactive);
   }
}
