#ifndef PLOTTER_H
#define PLOTTER_H

#include <QWidget>
#include <QDateTime>
#include <vector>
class Plotter : public QWidget
{
    Q_OBJECT
private:
    std::vector< double >timeList;
    std::vector< double >valueList;
    double deltaX;
    double x1;
    bool firstPrint;

public:
    //!Construtor da classe
    explicit Plotter(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    void draw(  std::vector<qint64 > _timeList, std::vector<int>_valueList);
signals:

public slots:
};

#endif // PLOTTER_H
