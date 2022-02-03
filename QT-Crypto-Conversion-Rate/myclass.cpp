#include <QtGui>
#include "myclass.h"
#include <QRegExp>
#include <QTableView>
#include <QHBoxLayout>
#include <QString>
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;



MyClass::MyClass(QWidget *parent,string filestr) : QLabel(parent)
{
    this->coinsString = filestr;
    this->table = new QTableView;

    coinlist = new QNetworkAccessManager(this);
    connect(coinlist, SIGNAL(finished(QNetworkReply *)),this, SLOT(takeCoins(QNetworkReply *)));
    coinlist->get(QNetworkRequest(QUrl("https://api.coingecko.com/api/v3/coins/list")));


}

void MyClass::makeTable(int row){

    this->model = new QStandardItemModel(row,3,this);

    this->model->setHeaderData(0,Qt::Horizontal,tr("USD"));
    this->model->setHeaderData(1,Qt::Horizontal,tr("EUR"));
    this->model->setHeaderData(2,Qt::Horizontal,tr("GBP"));

    this->table->setModel(model);

    this->mainlayout = new QHBoxLayout;
    this->mainlayout->addWidget(this->table);
    setLayout(this->mainlayout);

}

void MyClass::takeCoins(QNetworkReply *reply){
    QString data = (QString) reply->readAll();

    QString qcoinString = QString::fromStdString(this->coinsString);

    QStringList coinNames = qcoinString.split("\n");

    QString html = "";

    for(int i = 0 ; i<coinNames.length() ; i++){


       if(coinNames[i].toStdString().empty()){
            continue;
        }

        QString qID = "";
        QString qfind = coinNames[i];

        QString qfindSymbol = "\\{\"id\":\"([\\w\\d\\s-]+)\",\"symbol\":\"" + qfind + "\",\"name\":\"[\\w\\d\\s-]+\"\\}" ;

        QString qfindName = "\\{\"id\":\"([\\w\\d\\s-]+)\",\"symbol\":\"[\\w\\d\\s-]+\",\"name\":\""+ qfind +"\"\\}" ;

        QRegExp searchSymbol(qfindSymbol);

        if(searchSymbol.indexIn(data,0) != -1){
            qID = searchSymbol.cap(1);
        }
        else {
            QRegExp searchName(qfindName);
            if(searchName.indexIn(data,0) != -1){
                qID = searchName.cap(1);
            }
            else {
                qID = qfind;
            }

        }
        if(i!=coinNames.length()-1){
            html += qID + ",";
        }else{
            html += qID;
        }

    }



    QString firstPart = "https://api.coingecko.com/api/v3/simple/price?ids=";
    QString secondPart = "&vs_currencies=usd,eur,gbp";
    QString qcoins = firstPart + html + secondPart;



    this->manager = new QNetworkAccessManager(this) ;
    connect(manager, SIGNAL(finished(QNetworkReply *)),this, SLOT(replyFinished(QNetworkReply *)));
    //const char* qcoins = coins.c_str();
    this->manager->get(QNetworkRequest(QUrl(qcoins)));
}

void MyClass::replyFinished(QNetworkReply *reply)  {

     QString qstrID ;
     QString qstrUSD;
     QString qstrEUR;
     QString qstrGBP;

     int pos = 0;

     // read the data fetched from the web site

     QString data = (QString) reply->readAll();

     // use pattern matching to extract the rate

     QRegExp currencyID("\"([\\w\\d\\s-]+)\":\\{(\"usd\":([\\d.e-]*),\"eur\":([\\d.e-]*),\"gbp\":([\\d.e-]*))?");
     QStringList qList = data.split("},");
     makeTable(qList.length());

     int i = 0;

     while (qList.length()>0) {

      currencyID.indexIn(qList[0],pos);

      qstrID = QString("")+currencyID.cap(1);
      qstrUSD = QString("")+currencyID.cap(3);
      qstrEUR = QString("")+currencyID.cap(4);
      qstrGBP = QString("")+currencyID.cap(5);

      string strID = qstrID.toStdString();

      const char* pID = strID.c_str();



      this->model->setHeaderData(i,Qt::Vertical,tr(pID));    // rate found
      this->model->setItem(i,0,new QStandardItem(qstrUSD));
      this->model->setItem(i,1,new QStandardItem(qstrEUR));
      this->model->setItem(i,2,new QStandardItem(qstrGBP));



      qList.removeFirst();



      i = i+1;


     }

     // set the text of the label
     //label->setText("") ;
}
