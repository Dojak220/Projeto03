#ifndef PLOTTER_H
#define PLOTTER_H

#include <QWidget>
#include <QDateTime>
#include <vector>
/**
 * @brief The Plotter class
 */
class Plotter : public QWidget
{
    Q_OBJECT
private:
    /**
     * @brief timeList
     */
    std::vector< double >timeList;
    /**
     * @brief valueList
     */
    std::vector< double >valueList;
    /**
     * @brief deltaX
     */
    double deltaX;
    /**
     * @brief x1
     */
    double x1;
    /**
     * @brief firstPrint
     */
    bool firstPrint;

public:
    /**
     * @brief Plotter Construtor da classe
     * @param parent
     */
    explicit Plotter(QWidget *parent = 0);
    /**
     * @brief paintEvent
     * @param event
     */
    void paintEvent(QPaintEvent *event);
    /**
     * @brief draw
     * @param _timeList
     * @param _valueList
     */
    void draw(std::vector<qint64> _timeList, std::vector<int> _valueList);
signals:

public slots:
};

#endif // PLOTTER_H
