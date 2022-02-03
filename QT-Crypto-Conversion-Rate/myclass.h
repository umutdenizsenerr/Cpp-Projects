#ifndef MYCLASS_H
#define MYCLASS_H


#include <QtGui>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QLabel>
#include <QBoxLayout>
#include <QTableView>
#include <fstream>

using namespace std;
class MyClass : public QLabel
{
    Q_OBJECT

    public:
      MyClass(QWidget *parent = 0,string a = "");
      void makeTable(int row);
      QBoxLayout *mainlayout;
      QStandardItemModel *model;
      QTableView *table;
      string coinsString;

    public slots:
      void takeCoins(QNetworkReply *reply);
      void replyFinished(QNetworkReply * reply) ;

    private:
      QNetworkAccessManager *manager ;
      QNetworkAccessManager *coinlist ;
} ;
#endif
