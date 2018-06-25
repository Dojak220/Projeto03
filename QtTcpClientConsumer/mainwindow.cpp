#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  socket = new QTcpSocket(this);
  tcpConnect();

  connect(ui->setIP,
          SIGNAL(textChanged(QString)),
          this,
          SLOT(setIP(QString)));
  connect(ui->pushButtonConnect,
          SIGNAL(clicked(bool)),
          this,
          SLOT(tcpConnect()));
  connect(ui->pushButtonDisconnect,
          SIGNAL(clicked(bool)),
          this,
          SLOT(tcpDisconnect()));
  connect(ui->pushButtonUpdate,
          SIGNAL(clicked(bool)),
          this,
          SLOT(updateIP()));
  connect(ui->pushButtonStart,
          SIGNAL(clicked(bool)),
          this,
          SLOT(initTimer()));
  connect(ui->pushButtonStop,
          SIGNAL(clicked(bool)),
          this,
          SLOT(destroyTimer()));
  connect(ui->horizontalSliderTiming,
          SIGNAL(valueChanged(int)),
          this,
          SLOT(setTimer(int)));
  connect(ui->listViewIP,
          SIGNAL(itemDoubleClicked(QListWidgetItem*)),
          this,
          SLOT(updateIP(QListWidgetItem*)));

  endereco_ip = "127.0.0.1";
  timer = 1;
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

//evento para ficar recebendo os dados do servidor
void MainWindow::timerEvent(QTimerEvent *event){
    getData();
}

void MainWindow::getData(){
  QString str;
  QByteArray array;
  QStringList list;
  qint64 thetime;
  qDebug() << "to get data...";
  if(socket->state() == QAbstractSocket::ConnectedState){
    if(socket->isOpen()){
      qDebug() << "reading...";
      socket->write("get 127.0.0.1 5\r\n");
      socket->waitForBytesWritten();
      socket->waitForReadyRead();
      qDebug() << socket->bytesAvailable();
      while(socket->bytesAvailable()){
        str = socket->readLine().replace("\n","").replace("\r","");
        list = str.split(" ");
        if(list.size() == 2){
          bool ok;
          str = list.at(0);
          thetime = str.toLongLong(&ok);
          str = list.at(1);
          qDebug() << thetime << ": " << str;
        }
      }
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
void MainWindow::setIP(QString _ip){
    endereco_ip = QString (_ip);
}

void MainWindow::updateIP(QListWidgetItem* item){
    ui->setIP->setText(item->text());
}

//inicia o contador dos numeros aleatorios
void MainWindow::initTimer(){
    if(timers.size()==0){
        timers.push_back(startTimer(1000*timer));
    }
    else{
        killTimer(timers[0]);
        timers[0] = startTimer(1000*timer);
    }
}

//destroi o timer
void MainWindow::destroyTimer(){
    killTimer(timers[0]);
    timers.clear();
}

void MainWindow::setTimer(int _t){
    timer = _t;
    if(timers.size()){
        initTimer();
    }
}

MainWindow::~MainWindow(){
  delete socket;
  delete ui;
}
