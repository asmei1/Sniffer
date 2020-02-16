#pragma once
class TimeFormatter
{
public:
   static QString time2String(time_t local_tv_sec, const QString& timeFormatt = "%H:%M:%S");
};

