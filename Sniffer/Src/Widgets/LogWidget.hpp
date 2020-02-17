#pragma once
#include <QPlainTextEdit>
#include <QScrollBar>


class LogWidget : public QPlainTextEdit
{
   Q_OBJECT;
public:
   explicit LogWidget(QObject* parent = nullptr);
   ~LogWidget();

   enum class LogLevel
   {
      CRITICAL_ERROR = 0,
      ERR,
      INFO,
      DEBUG_LOG,
   };


public slots:
   void log(const QString& text);
   void logCStr(const char* text, LogLevel level);
   void logQStr(const QString& text, LogLevel level);
};
