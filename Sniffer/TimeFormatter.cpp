#include "stdafx.h"
#include "TimeFormatter.h"

QString TimeFormatter::time2String(time_t local_tv_sec, const QString& timeFormatt)
{
   struct tm* ltime;
   char timestr[16];
   ltime = localtime(&local_tv_sec);
   strftime(timestr, sizeof timestr, "%H:%M:%S", ltime);

   return QString(timestr);
}
