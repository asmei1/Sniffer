#pragma once

#include <QWidget>
#include "Structures/IPv4Interface.h"

namespace qsn {
   class FramesStash;
}

namespace Ui {
   class ResolverIPWidget;
}

class ResolverIPWidget : public QDialog
{
   Q_OBJECT;

public:
   explicit ResolverIPWidget(qsn::FramesStash* stash, QWidget* parent = nullptr);
   ~ResolverIPWidget();

private:
   std::map<qsn::IPv4Addr, std::pair<int, QString>> data;
   Ui::ResolverIPWidget* ui;
};

