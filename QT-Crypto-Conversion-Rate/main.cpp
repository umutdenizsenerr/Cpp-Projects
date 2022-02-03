#include <QtCore>
#include <QApplication>
#include "myclass.h"
#include <fstream>
#include <iostream>
#include <stdio.h>

using namespace std;
int main(int argc,char *argv[])
{

   QApplication app(argc, argv);

   //string filename = argv[1];
   ifstream file;


   char* envr = getenv("MYCRYPTOCONVERT");

   file.open(envr);


   string coindata = "";

   string line;

   while (getline (file, line)) {

     line.append("\n");
     coindata.append(line);

   }


   MyClass myTable(0,coindata);

   myTable.resize(640,480);
   myTable.show();


   file.close();
   return app.exec();
}
