#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent), ui(new Ui::MainWindow){
  ui->setupUi(this);
  socket = new QTcpSocket(this);

  //seta os signals e slots
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
          SIGNAL(valueChanged(int)),
          this,
          SLOT(setMin(int)));
  connect(ui->horizontalSliderMax,
          SIGNAL(valueChanged(int)),
          this,
          SLOT(setMax(int)));
  connect(ui->horizontalSliderTimings,
          SIGNAL(valueChanged(int)),
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

//connecta com o servidor
void MainWindow::tcpConnect(){
  socket->connectToHost(endereco_ip,1234);
  if(socket->waitForConnected(3000)){
    qDebug() << "Connected";
  }
  else{
    qDebug() << "Disconnected";
  }
}

//evento para ficar enviando os dados ao servidor
void MainWindow::timerEvent(QTimerEvent *event)
{
    putData();
}

void MainWindow::putData(){
  QDateTime datetime;
  QString str;
  qint64 msecdate;

  if(socket->state()== QAbstractSocket::ConnectedState){

    msecdate = QDateTime::currentDateTime().toMSecsSinceEpoch();
    str = "set "+ QString::number(msecdate) + " " + QString::number(qrand()%35)+"\r\n";
    QStringList list(str);
    ui->listWidget->addItems(list);
    ui->listWidget->scrollToBottom();
      qDebug() << str;
      qDebug() << socket->write(str.toStdString().c_str()) << " bytes written";
      if(socket->waitForBytesWritten(3000)){
        qDebug() << "wrote";
      }
  }
}

//disconnecta do servidor
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

//muda o endereço de ip, por padrão é o localhost 127.0.0.1
void MainWindow::mudarIP(QString _ip)
{
    endereco_ip = QString (_ip);
}

//seta a faixa minima
void MainWindow::setMin(int _min)
{
    if(max <= _min){
        ui->horizontalSliderMax->setValue(_min);
    }
    min = _min;
}

//maximo
void MainWindow::setMax(int _max)
{
    if(min >= _max){
        ui->horizontalSliderMin->setValue(_max);
    }
    max = _max;
}

//inicia o contador dos numeros aleatorios
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

//destroi o timer
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
