#include "stdafx.h"

#include "MainWindow.h"
#include <QtWidgets/QApplication>

#ifndef WIN32
#include <sys/socket.h>
#include <netinet/in.h>
#else
#include <winsock.h>
#include <tchar.h>
bool LoadNpcapDlls()
{
   TCHAR npcap_dir[512];
   UINT len;
   len = GetSystemDirectory(npcap_dir, 480);
   if(!len) {
      fprintf(stderr, "Error in GetSystemDirectory: %x", GetLastError());
      return false;
   }
   _tcscat_s(npcap_dir, 512, TEXT("\\Npcap"));
   if(SetDllDirectory(npcap_dir) == 0) {
      fprintf(stderr, "Error in SetDllDirectory: %x", GetLastError());
      return false;
   }
   return true;
}
#endif

int main(int argc, char** argv)
{
   LoadNpcapDlls();
   QApplication a(argc, argv);
   MainWindow w;
   w.show();
   return a.exec();
}
