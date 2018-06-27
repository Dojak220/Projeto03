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
/**
 * @brief The MainWindow class
 */
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
  /**
   * @brief MainWindow
   * @param parent
   */
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
  

public slots:
  /**
   * @brief tcpConnect
   */
  void tcpConnect();
  /**
   * @brief timerEvent
   * @param event
   */
  void timerEvent(QTimerEvent *event);
  /**
   * @brief getData
   */
  void getData();
  /**
   * @brief tcpDisconnect
   */
  void tcpDisconnect();
  /**
   * @brief setIP
   * @param _ip
   */
  void setIP(QString _ip);
  /**
   * @brief updateIP
   * @param item
   */
  void updateIP(QListWidgetItem *item);
  /**
   * @brief initTimer
   */
  void initTimer();
  /**
   * @brief destroyTimer
   */
  void destroyTimer();
  /**
   * @brief setTimer
   * @param _t
   */
  void setTimer(int _t);
private:
  /**
   * @brief ui
   */
  Ui::MainWindow *ui;
  /**
   * @brief socket
   */
  QTcpSocket *socket;
};

#endif // MAINWINDOW_H
