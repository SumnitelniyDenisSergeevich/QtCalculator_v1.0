#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <QWidget>

#include <QtCharts/QLineSeries>
#include <QtCharts/QtCharts>
#include <QtCharts/QChartView>

namespace Ui {
class Graphic;
}

class Graphic : public QWidget
{
    Q_OBJECT

public:
    explicit Graphic(QWidget *parent = nullptr);
    ~Graphic();
    Ui::Graphic* GetUi();
    QLineSeries* GetSeries();
    QChart* GetChart();
private:
    void InitAxis();
    void InitChart();
    void InitSeries();

    Ui::Graphic *ui;
    QLineSeries *series;
    QChart *chart;
    QChartView *chartView;
    QValueAxis *axisX;
    QValueAxis *axisY;
};

#endif // GRAPHIC_H
