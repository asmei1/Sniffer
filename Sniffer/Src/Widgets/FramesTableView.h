#pragma once
#include <QTableView>
class PacketsTableView : public QTableView
{
   Q_OBJECT;
public:
   PacketsTableView(QWidget* parent = nullptr);
   ~PacketsTableView() = default;


   void setModel(QAbstractItemModel* model) override;
};

