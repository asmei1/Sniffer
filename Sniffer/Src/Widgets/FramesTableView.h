#pragma once
#include <QTableView>
class FramesTableView : public QTableView
{
   Q_OBJECT;
public:
   FramesTableView(QWidget* parent = nullptr);
   ~FramesTableView() = default;


   void setModel(QAbstractItemModel* model) override;
};

