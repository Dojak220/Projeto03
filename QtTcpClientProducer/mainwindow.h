#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QDebug>
#include <QTimerEvent>
#include <vector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT
  int min, max, timer;
  std::vector <int>timers;
  QString endereco_ip;
public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
  void timerEvent(QTimerEvent *event);
  
public slots:
  void tcpConnect();
  void putData();
  void tcpDisconnect();
  void mudarIP(QString _ip);
  void setMin(int _min);
  void setMax(int _max);

  void initTimer();
  void destroyTimer();
  void setTimer(int _t);

private:
  Ui::MainWindow *ui;
  QTcpSocket *socket;
};

#endif // MAINWINDOW_H
