#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QDebug>
#include <QListWidget>
#include <QDateTime>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    /**
    * @brief timer indica a frequência em que os
    * dados são fornecidos.
    */
   int timer;
   /**
    * @brief timers
    */
   std::vector <int>timers;
   /**
    * @brief endereco_ip
    */
   QString endereco_ip;

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
  

public slots:
  void tcpConnect();

  void timerEvent(QTimerEvent *event);

  void getData();

  void tcpDisconnect();

  void setIP(QString _ip);

  void updateIP(QListWidgetItem *item);

  void initTimer();

  void destroyTimer();

  void setTimer(int _t);
private:
  Ui::MainWindow *ui;
  QTcpSocket *socket;
};

#endif // MAINWINDOW_H
