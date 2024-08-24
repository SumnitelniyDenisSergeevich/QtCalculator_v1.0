#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "graphic.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_ButtonCos_clicked();
    void on_ButtonSin_clicked();
    void on_ButtonTan_clicked();
    void on_ButtonLeftBracket_clicked();
    void on_ButtonRightBracket_clicked();
    void on_ButtonASin_clicked();
    void on_ButtonATan_clicked();
    void on_ButtonACos_clicked();
    void on_ButtonMod_clicked();
    void on_ButtonDiv_clicked();
    void on_ButtonPow_clicked();
    void on_Button7_clicked();
    void on_Button8_clicked();
    void on_Button9_clicked();
    void on_ButtonMult_clicked();
    void on_ButtonSqrt_clicked();
    void on_Button4_clicked();
    void on_Button5_clicked();
    void on_Button6_clicked();
    void on_ButtonPlus_clicked();
    void on_ButtonLn_clicked();
    void on_Button1_clicked();
    void on_Button2_clicked();
    void on_Button3_clicked();
    void on_ButtonMinus_clicked();
    void on_ButtonLog_clicked();
    void on_ButtonX_clicked();
    void on_Button0_clicked();
    void on_ButtonDot_clicked();
    void on_ButtonEqual_clicked();
    void on_ButtonGraph_clicked();
    void on_ButtonCreditCalc_clicked();
    void on_ButtonDepositCalc_clicked();

    void on_ButtonCreateAddTable_clicked();

    void on_ButtonCreateSubTable_clicked();

private:
    void InitCredit();
    void InitDeposit();
    void InitCalculator();
    void resizeEvent(QResizeEvent *event);

    Ui::MainWindow *ui;
    Graphic *ui_graphic;
    QStandardItemModel *model;
    QStandardItemModel *model_add_table;
    QStandardItemModel *model_sub_table;
    bool set_table_size;
};
#endif // MAINWINDOW_H
