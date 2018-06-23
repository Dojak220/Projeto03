#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QDebug>
#include <QTimerEvent>
#include <vector>
/**
 * @brief The MainWindow class tem a função de
 * desenhar a interface.
 */
namespace Ui {
class MainWindow;
}
/**
 * @brief The MainWindow class tem a função de
 * comandar as ações de como a interface será
 * trabalhada/operada.
 */
class MainWindow : public QMainWindow
{
  Q_OBJECT
   /**
   * @brief min é o valor mínimo a ser gerado no
   * produtor.
   * @brief max min é o valor máximo a ser
   * gerado no produtor.
   * @brief timer indica a frequência em que os
   * dados são fornecidos.
   */
  int min, max, timer;
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
  /**
   * @brief timerEvent faz com que os dados sejam enviados ao
   * servidor
   * @param event
   */
  void timerEvent(QTimerEvent *event);
  
public slots:
  /**
   * @brief tcpConnect faz a conexão com o servidor.
   */
  void tcpConnect();
  /**
   * @brief putData simula a produção de dados e imprime na tela o
   * dado e o tempo em que ele foi gerado.
   */
  void putData();
  /**
   * @brief tcpDisconnect faz o corte da conexão entre o servidor
   * e o produtor.
   */
  void tcpDisconnect();
  /**
   * @brief mudarIP serve para mudar o ip que, por padrão, é o
   * localhost 127.0.0.1.
   * @param _ip é um Qstring que guarda o novo ip a ser colocado.
   */
  void mudarIP(QString _ip);
  /**
   * @brief setMin configura o valor mínimo na faixa de valores a
   * serem gerados a partir do slider. O setMin também impede que
   * o valor máximo seja menor que o mínimo.
   * @param _min é o valor recebido pelo slider.
   */
  void setMin(int _min);
  /**
   * @brief setMax configura o valor máximo na faixa de valores a
   * serem gerados a partir do slider. O setMax também impede que
   * o valor mínimo seja maior que o máximo.
   * @param _max é o valor recebido pelo slider.
   */
  void setMax(int _max);
  /**
   * @brief initTimer inicia ou para o contador dos números
   * gerados aleatoriamente.
   */
  void initTimer();
  /**
   * @brief destroyTimer reseta o timer
   */
  void destroyTimer();
  /**
   * @brief setTimer configura o timer.
   * @param _t valor recebido do slider.
   */
  void setTimer(int _t);

private:
  /**
   * @brief ui permite o acesso a todos os objetos da Ui(interface
   * visual),  ou seja, os botões, slider, caixa de texto etc...
   */
  Ui::MainWindow *ui;
  /**
   * @brief socket
   */
  QTcpSocket *socket;
};

#endif // MAINWINDOW_H
