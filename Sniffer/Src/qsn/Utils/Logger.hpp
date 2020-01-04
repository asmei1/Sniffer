#pragma once
#include "stdafx.h"
#include "Widgets/LogWidget.hpp"

class Logger : public QObject
{
   Q_OBJECT;
   Logger() = default;

public:
   static Logger& getInstance()
   {
      static Logger logger;
      return logger;
   }

   Logger(const Logger&) = delete;
   Logger& operator= (const Logger&) = delete;

 
signals:
   void log(const QString& msgText, LogWidget::LogLevel level = LogWidget::LogLevel::INFO);
};