#include "graphic.h"
#include "ui_graphic.h"

Graphic::Graphic(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Graphic)
{
    ui->setupUi(this);
    series = new QLineSeries();
    chart = new QChart();
    this->setWindowTitle("Jolteona Calculator Graphics");
    InitSeries();
    InitChart();
    InitAxis();
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    chart->addSeries(series);

    series->attachAxis(axisX);
    series->attachAxis(axisY);
    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    ui->ChartFrame->addWidget(chartView);
}

Graphic::~Graphic()
{
    delete ui;
    delete series;
    delete chart;
    delete chartView;
    delete axisX;
    delete axisY;
}

void Graphic::InitAxis(){
    axisX = new QValueAxis();
    axisY = new QValueAxis();
    // Customize axis label font
    QFont labelsFont;
    labelsFont.setPixelSize(15);
    axisX->setLabelsFont(labelsFont);
    axisY->setLabelsFont(labelsFont);

    // Customize axis colors
    QPen axisPen(QRgb(0x37fff8));
    axisPen.setWidth(2);
    axisX->setLinePen(axisPen);
    axisY->setLinePen(axisPen);

    // Customize axis label colors
    QBrush axisBrush(QRgb(0x37fff8));
    axisX->setLabelsBrush(axisBrush);
    axisY->setLabelsBrush(axisBrush);

    // Customize grid lines and shades
    axisX->setGridLineColor(QRgb(0x37fff8));
    axisY->setGridLineColor(QRgb(0x37fff8));

    axisX->setTitleText("x");
    axisY->setTitleText("y");
    axisX->setTitleBrush(axisBrush);
    axisY->setTitleBrush(axisBrush);
    QFont axisFont;
    axisFont.setPixelSize(18);
    axisX->setTitleFont(axisFont);
    axisY->setTitleFont(axisFont);
}

void Graphic::InitChart(){
    QFont ChartFont;
    ChartFont.setPixelSize(18);
    chart->setTitleFont(ChartFont);
    chart->setTitleBrush(QBrush(QRgb(0xff7b0f)));
    chart->legend()->hide();
    QBrush backgroundBrush(QRgb(0x000000));
    chart->setBackgroundBrush(backgroundBrush);
}

void Graphic::InitSeries(){
    QPen SeriesPen(QRgb(0xff7b0f));
    SeriesPen.setWidth(4);
    series->setPen(SeriesPen);
}

Ui::Graphic* Graphic::GetUi(){
    return ui;
}

QLineSeries* Graphic::GetSeries(){
    return series;
}

QChart* Graphic::GetChart(){
    return chart;
}
