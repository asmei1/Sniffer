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


protected:
   void paintEvent(QPaintEvent* event) override 
   {
      QPlainTextEdit::paintEvent(event);
      static bool displayWarnings = true;
      if(displayWarnings == true)
      {
         displayWarnings = false;
         //const QString filePath = QString::fromStdString(m_pSstProject->getConfigFilePath() );

         //// TODO  :  usun niepotrzbne  parametry   z messegy
         //for (int i = 0; i < p_ATS_MainWindow->logsList.size(); i++)
         //{
         //   ATSLog->log(p_ATS_MainWindow->logsList[ i ].first, ATSLogger::LOG_LEVEL_CRIT_WARN | ATSLogger::LOG_WIDGET | ATSLogger::LOG_MESSAGE_BOX, p_ATS_MainWindow->logsList[ i ].second, { filePath });
         //}
         //p_ATS_MainWindow->logsList.clear();
      } 
   }
};
