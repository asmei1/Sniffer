#include "stdafx.h"
#include "LogWidget.hpp"

LogWidget::LogWidget(QObject* parent)
{

}


LogWidget::~LogWidget()
{
}

void LogWidget::logCStr(const char* text, LogLevel level)
{
   QString log = text;
   log.replace("\r", "");
   log.replace("\n", "<br/>");
   QString html;
   switch (level)
   {
   case LogLevel::ERR:
      html = "<font color=\"Red\">";
      break;
   case LogLevel::DEBUG_LOG:
      html = "<font color=\"Green\">";
      break;
   case LogLevel::INFO:
      html = "<font color=\"#228be3\">";
      break;
   }
   log = html + "<pre>" + log + "</pre></font>";
   emit this->appendHtml(log);
   emit this->verticalScrollBar()->setValue(this->verticalScrollBar()->maximum()); // Scrolls to the bottom
}

void LogWidget::log(const QString & text)
{
   this->appendPlainText(text); // Adds the message to the widget
   this->verticalScrollBar()->setValue(this->verticalScrollBar()->maximum()); // Scrolls to the bottom
}

void LogWidget::logQStr(const QString & text, LogLevel level)
{
   this->logCStr(text.toStdString().c_str(), level);
}
