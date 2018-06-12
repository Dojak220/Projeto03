#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent), ui(new Ui::MainWindow){
  ui->setupUi(this);
  socket = new QTcpSocket(this);

  connect(ui->pushButtonConnect,
          SIGNAL(clicked(bool)),
          this,
          SLOT(tcpConnect()));
  connect(ui->pushButtonDisconnect,
          SIGNAL(clicked(bool)),
          this,
          SLOT(tcpDisconnect()));
  connect(ui->pushButtonStart,
          SIGNAL(clicked(bool)),
          this,
          SLOT(initTimer()));
  connect(ui->pushButtonStop,
          SIGNAL(clicked(bool)),
          this,
          SLOT(destroyTimer()));
  connect(ui->horizontalSliderMin,
          SIGNAL(clicked(bool)),
          this,
          SLOT(setMin(int)));
  connect(ui->horizontalSliderMax,
          SIGNAL(clicked(bool)),
          this,
          SLOT(setMax(int)));
  connect(ui->horizontalSliderTimings,
          SIGNAL(clicked(bool)),
          this,
          SLOT(setTimer(int)));
  connect(ui->setIP,
          SIGNAL(textChanged(QString)),
          this,
          SLOT(mudarIP(QString)));


  endereco_ip = "127.0.0.1";
  timer = 1;
  min = 1;
  max = 10;
}

void MainWindow::tcpConnect(){
  socket->connectToHost(endereco_ip,1234);
  if(socket->waitForConnected(3000)){
    qDebug() << "Connected";
  }
  else{
    qDebug() << "Disconnected";
  }
}

void MainWindow::putData(){
  QDateTime datetime;
  QString str;
  qint64 msecdate;

  if(socket->state()== QAbstractSocket::ConnectedState){

    msecdate = QDateTime::currentDateTime().toMSecsSinceEpoch();
    str = "set "+ QString::number(msecdate) + " " + QString::number(qrand()%35)+"\r\n";

      qDebug() << str;
      qDebug() << socket->write(str.toStdString().c_str()) << " bytes written";
      if(socket->waitForBytesWritten(3000)){
        qDebug() << "wrote";
      }
  }
}

void MainWindow::tcpDisconnect()
{
    socket->disconnectFromHost();
    if(socket->waitForConnected(3000)){
      qDebug() << "Connected";
    }
    else{
      qDebug() << "Disconnected";
    }
}

void MainWindow::mudarIP(QString _ip)
{
    endereco_ip = QString (_ip);
}

void MainWindow::setMin(int _min)
{
    if(max <= _min){
        ui->horizontalSliderMax->setValue(_min);
    }
    min = _min;
}

void MainWindow::setMax(int _max)
{
    if(min >= _max){
        ui->horizontalSliderMin->setValue(_max);
    }
    max = _max;
}

void MainWindow::initTimer()
{
    if(timers.size()==0){
        timers.push_back(startTimer(1000*timer));
    }
    else{
        killTimer(timers[0]);
        timers[0] = startTimer(1000*timer);
    }
}

void MainWindow::destroyTimer()
{
    killTimer(timers[0]);
    timers.clear();
}

void MainWindow::setTimer(int _t)
{
    timer = _t;
    if(timers.size()){
        initTimer();
    }
}

MainWindow::~MainWindow(){
  delete socket;
  delete ui;
}
