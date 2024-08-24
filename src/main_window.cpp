#include "main_window.h"
#include "./ui_mainwindow.h"
#include "./graphic.h"

#include <QDoubleValidator>
#include <QStandardItemModel>
#include <QStandardItem>


#include <numeric>

#ifdef __cplusplus
extern "C" {
#endif

#include "backend/s21_calculator.h"

#ifdef __cplusplus
}
#endif

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , ui_graphic(new Graphic)
{
    ui->setupUi(this);
    this->setWindowTitle("Jolteona Calculator");
    set_table_size = false;
    InitCredit();
    InitDeposit();
    InitCalculator();
}


MainWindow::~MainWindow()
{
    delete ui;
    delete ui_graphic;
    delete model;
    delete model_add_table;
    delete model_sub_table;
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    if(!set_table_size){
        ui->TableCredit->setColumnWidth(0,222);
        ui->TableCredit->setColumnWidth(1,222);
        ui->TableDepositIn->setColumnWidth(0,100);
        ui->TableDepositIn->setColumnWidth(1,100);
        ui->TableDepositOut->setColumnWidth(0,100);
        ui->TableDepositOut->setColumnWidth(1,100);
        set_table_size = true;
    }else{
        ui->TableCredit->setColumnWidth(0,ui->TableCredit->width()/2 - 11);
        ui->TableCredit->setColumnWidth(1,ui->TableCredit->width()/2 - 11);
        ui->TableDepositIn->setColumnWidth(0,ui->TableDepositIn->width()/2 - 11);
        ui->TableDepositIn->setColumnWidth(1,ui->TableDepositIn->width()/2 - 11);
        ui->TableDepositOut->setColumnWidth(0,ui->TableDepositOut->width()/2 - 11);
        ui->TableDepositOut->setColumnWidth(1,ui->TableDepositOut->width()/2 - 11);
    }
    QMainWindow::resizeEvent(event);
}

void MainWindow::on_ButtonEqual_clicked()
{
    ui->ErrText->setText("");
    double result;
    double x;
    bool conv_x = 0;
    QString str = ui->EditX->text();
    str.replace(',', '.');
    if(str.isEmpty()){
        x = std::numeric_limits<double>::quiet_NaN();
    }else{
        x = str.toDouble(&conv_x);
    }
    if(!conv_x){
        ui->ErrText->setText("X is not double!");
    }else{
        QByteArray formula_ba = ui->EditFormula->text().toLocal8Bit();
        const char *c_formula = formula_ba.data();
        int err = infix_notation(c_formula,x,&result);
        if(!err){
            QString num =QString::number(result,'f',7);
            while(num.back() =='0' && num.size() > 1){
                num.chop(1);
            }
            if(num.back() =='.'){
                num.chop(1);
            }
            ui->EditFormula->setText(num);
        }else if(err == 1){
            ui->ErrText->setText("Func/operator name error!");
        }else if(err == 2){
            ui->ErrText->setText("Logic error!");
        }
    }
}

void MainWindow::on_ButtonGraph_clicked()
{
    point_t result[POINTS_SIZE];
    double x_l = ui->DBoxX1->value();
    double x_r = ui->DBoxX2->value();
    double y_u = ui->DBoxY2->value();
    double y_d = ui->DBoxY1->value();
    if(ui->EditFormula->text().isEmpty()){
        ui->ErrText->setText("formula is empty!");
    }else if(x_l > x_r || y_d > y_u){
        ui->ErrText->setText("x1 > x2 or y1 > y2!");
    }else{
        QByteArray formula_ba = ui->EditFormula->text().toLocal8Bit();
        const char *c_formula = formula_ba.data();
        int err = graphic(c_formula,x_l,x_r,result);
        if(!err){
            ui_graphic->GetSeries()->clear();
            for(int i = 0; i < POINTS_SIZE;++i){
                ui_graphic->GetSeries()->append(result[i].x,result[i].y);
            }
            ui_graphic->GetChart()->axes(Qt::Horizontal,ui_graphic->GetSeries()).back()->setRange(x_l, x_r);
            ui_graphic->GetChart()->axes(Qt::Vertical,ui_graphic->GetSeries()).back()->setRange(y_d, y_u);
            ui_graphic->GetChart()->setTitle("Graphic: " + ui->EditFormula->text());
            ui_graphic->show();
        }else if(err == 1){
            ui->ErrText->setText("Func/operator name error!");
        }else if(err == 2){
            ui->ErrText->setText("Logic error!");
        }
    }
}

void MainWindow::on_ButtonCreditCalc_clicked()
{
    credit_calc_output_t result;
    credit_calc_input_t input;
    QString str = ui->BoxCreditSum->text();
    str.replace(',', '.');
    input.total_amount = str.toDouble();
    str = ui->BoxCreditRate->text();
    str.replace(',', '.');
    input.interest_rate = str.toDouble();
    input.term = ui->BoxCreditMonthCount->text().toInt();
    input.type = ui->BoxCreditType->currentIndex();
    credit_calculator(&input,&result);
    ui->labelCreditOverpaymentVal->setText(QString::number(result.overpayment,'f',2));
    ui->labelCreditTotalSumVal->setText(QString::number(result.total_paymen,'f',2));
    model->clear();
    QStringList horizontalHeader;
    horizontalHeader.append("№ месяца");
    horizontalHeader.append("Платеж");
    model->setHorizontalHeaderLabels(horizontalHeader);
    QStandardItem *item;
    if(input.type){
        for(int i =0 ; i < input.term; ++i){
            item = new QStandardItem(QString::number(result.monthly_payment[i]));
            model->setItem(i, 1, item);
            item = new QStandardItem(QString::number(i + 1));
            model->setItem(i, 0, item);
        }
    }else{
        for(int i =0 ; i < input.term; ++i){
            item = new QStandardItem(QString::number(*result.monthly_payment));
            model->setItem(i, 1, item);
            item = new QStandardItem(QString::number(i + 1));
            model->setItem(i, 0, item);
        }
    }
    ui->TableCredit->setModel(model);
    ui->TableCredit->setColumnWidth(0,ui->TableCredit->width()/2 - 11);
    ui->TableCredit->setColumnWidth(1,ui->TableCredit->width()/2 - 11);
}

void MainWindow::on_ButtonDepositCalc_clicked()
{
    ui->label_deposit_error->setText("");
    ui->labelDepositGetRateVal->setText("");
    ui->labelDepositTaxSumVal->setText("");
    ui->labelDepositSumTotalVal->setText("");
    deposit_calc_input_t input;
    if(ui->spinBox_add_count->value() != ui->TableDepositIn->model()->rowCount()
        || ui->spinBox_sub_count->value() != ui->TableDepositOut->model()->rowCount()
        ){
        ui->label_deposit_error->setText("Incorect in/out count and in/out rows");
    }else{
        input.par_list_size = ui->spinBox_sub_count->value();//снятия
        input.rep_list_size = ui->spinBox_add_count->value();
        bool double_conv = true;
        input.partial_withdrawals_list = (deposit_list_t*)malloc(sizeof(deposit_list_t) * input.par_list_size);
        input.replenishments_list = (deposit_list_t*)malloc(sizeof(deposit_list_t) * input.rep_list_size);
        for(int i = 0; i < input.par_list_size && double_conv; ++i){
            QModelIndex Index = model_sub_table->index(i,1);
            QString value_str = ui->TableDepositOut->model()->data(Index).toString();
            value_str.replace(',', '.');
            double value_double = value_str.toDouble(&double_conv);
            if(value_double < 0){
                double_conv = false;
            }else if(value_double > 1e-7){
                input.partial_withdrawals_list[i].sum = value_double;
            }
            Index = model_sub_table->index(i,0);
            value_str = ui->TableDepositOut->model()->data(Index).toString();
            int value_int = value_str.toInt(&double_conv);
            if(value_int <= 0){
                double_conv = false;
            }else{
                input.partial_withdrawals_list[i].period = value_int;
            }
        }
        for(int i = 0; i < input.rep_list_size && double_conv; ++i){
            QModelIndex Index = model_add_table->index(i,1);
            QString value_str = ui->TableDepositIn->model()->data(Index).toString();
            value_str.replace(',', '.');
            double value = value_str.toDouble(&double_conv);
            if(value < 0){
                double_conv = false;
            }else if(value > 1e-7){
                input.replenishments_list[i].sum = value;
                input.replenishments_list[i].period = i + 1;
            }
            Index = model_add_table->index(i,0);
            value_str = ui->TableDepositIn->model()->data(Index).toString();
            int value_int = value_str.toInt(&double_conv);
            if(value_int <= 0){
                double_conv = false;
            }else{
                input.replenishments_list[i].period = value_int;
            }
        }
        if(double_conv){
            QString str = ui->BoxDepositSum->text();
            str.replace(',','.');
            input.deposit_amount = str.toDouble();
            if (ui->CheckKap->isChecked()){
                input.capitalization_of_interest = 1;
            }else{
                input.capitalization_of_interest = 0;
            }
            str = ui->BoxDepositRate->text();
            str.replace(',','.');
            input.interest_rate = str.toDouble();
            str = ui->BoxDepositTax->text();
            str.replace(',','.');
            input.tax_rate = str.toDouble();
            input.term = ui->BoxDepositTerm->value();
            input.periodicity_of_payments= ui->BoxTermPayType->currentIndex();// 0 день 1 - месяц 2 - год;

            deposit_calc_output_t result = deposit_calculator(&input);

            ui->labelDepositGetRateVal->setText(QString::number(result.accrued_interest,'f',2));
            ui->labelDepositTaxSumVal->setText(QString::number(result.tax_amount,'f',2));
            ui->labelDepositSumTotalVal->setText(QString::number(result.deposit_amount_end,'f',2));
        }else{
            ui->label_deposit_error->setText("Incorect add/sub table values");
        }
        free(input.partial_withdrawals_list);
        free(input.replenishments_list);
    }
}

void MainWindow::on_ButtonCreateAddTable_clicked()
{
    model_add_table->clear();
    QStringList horizontalHeader_add;
    horizontalHeader_add.append("№ месяца");
    horizontalHeader_add.append("Пополнение");

    model_add_table->setHorizontalHeaderLabels(horizontalHeader_add);
    QStandardItem *item;
    for(int i =0 ; i < ui->spinBox_add_count->value(); ++i){
        item = new QStandardItem(QString::number(0));
        model_add_table->setItem(i, 1, item);
        item = new QStandardItem(QString::number(i + 1));
        model_add_table->setItem(i, 0, item);
    }
    ui->TableDepositIn->setModel(model_add_table);
    ui->TableDepositIn->setColumnWidth(0,ui->TableDepositIn->width()/2 - 11);
    ui->TableDepositIn->setColumnWidth(1,ui->TableDepositIn->width()/2 - 11);
}

void MainWindow::on_ButtonCreateSubTable_clicked()
{
    model_sub_table->clear();
    QStringList horizontalHeader_sub;
    horizontalHeader_sub.append("№ месяца");
    horizontalHeader_sub.append("Снятие");
    model_sub_table->setHorizontalHeaderLabels(horizontalHeader_sub);
    QStandardItem *item;
    for(int i =0 ; i < ui->spinBox_sub_count->value(); ++i){
        item = new QStandardItem(QString::number(0));
        model_sub_table->setItem(i, 1, item);
        item = new QStandardItem(QString::number(i + 1));
        model_sub_table->setItem(i, 0, item);
    }
    ui->TableDepositOut->setModel(model_sub_table);
    ui->TableDepositOut->setColumnWidth(0,ui->TableDepositOut->width()/2 - 11);
    ui->TableDepositOut->setColumnWidth(1,ui->TableDepositOut->width()/2 - 11);
}

void MainWindow::InitCredit(){
    ui->BoxCreditType->addItem("Аннуитетный");
    ui->BoxCreditType->addItem("Дифференцированный");
    ui->BoxCreditSum->setMinimum(0);
    ui->BoxCreditSum->setMaximum(1e+308);
    ui->BoxCreditSum->setDecimals(2);
    ui->BoxCreditRate->setMinimum(0);
    ui->BoxCreditRate->setDecimals(2);
    ui->BoxCreditMonthCount->setMinimum(0);
    ui->BoxCreditMonthCount->setMaximum(10000);
    ui->TableCredit->verticalHeader()->setVisible(false);

    model = new QStandardItemModel;
    //Заголовки столбцов
    QStringList horizontalHeader;
    horizontalHeader.append("№ месяца");
    horizontalHeader.append("Платеж");
    model->setHorizontalHeaderLabels(horizontalHeader);
    //Закидываем данные
    ui->TableCredit->setModel(model);
}

void MainWindow::InitDeposit(){
    ui->BoxDepositSum->setMinimum(0);
    ui->BoxDepositSum->setMaximum(1e+308);
    ui->BoxDepositSum->setDecimals(2);
    ui->BoxTermPayType->addItem("Ежедневно");
    ui->BoxTermPayType->addItem("Ежемесячно");
    ui->BoxTermPayType->addItem("Ежегодно");
    ui->BoxDepositRate->setMinimum(0);
    ui->BoxDepositRate->setDecimals(2);
    ui->BoxDepositTax->setMinimum(0);
    ui->BoxDepositTax->setDecimals(2);
    ui->BoxDepositTerm->setMinimum(0);
    ui->BoxDepositTerm->setMaximum(10000);

    ui->TableDepositIn->verticalHeader()->setVisible(false);
    ui->TableDepositOut->verticalHeader()->setVisible(false);

    model_add_table = new QStandardItemModel;
    model_sub_table = new QStandardItemModel;
    //Заголовки столбцов
    QStringList horizontalHeader_add;
    horizontalHeader_add.append("№ месяца");
    horizontalHeader_add.append("Пополнение");
    QStringList horizontalHeader_sub;
    horizontalHeader_sub.append("№ месяца");
    horizontalHeader_sub.append("Снятие");
    model_add_table->setHorizontalHeaderLabels(horizontalHeader_add);
    model_sub_table->setHorizontalHeaderLabels(horizontalHeader_sub);
    //Закидываем данные
    ui->TableCredit->setModel(model);
    ui->TableDepositIn->setModel(model_add_table);
    ui->TableDepositOut->setModel(model_sub_table);
}

void MainWindow::InitCalculator(){
    ui->EditX->setValidator(new QDoubleValidator(this));
    ui->DBoxX1->setMinimum(-1e+6);
    ui->DBoxX1->setMaximum(1e+6);
    ui->DBoxX1->setDecimals(6);
    ui->DBoxX2->setMinimum(-1e+6);
    ui->DBoxX2->setMaximum(1e+6);
    ui->DBoxX2->setDecimals(6);
    ui->DBoxY1->setMinimum(-1e+6);
    ui->DBoxY1->setMaximum(1e+6);
    ui->DBoxY1->setDecimals(6);
    ui->DBoxY2->setMinimum(-1e+6);
    ui->DBoxY2->setMaximum(1e+6);
    ui->DBoxY2->setDecimals(6);
}

void MainWindow::on_ButtonCos_clicked()
{
    ui->EditFormula->setText(ui->EditFormula->text() + QString("cos("));
}

void MainWindow::on_ButtonSin_clicked()
{
    ui->EditFormula->setText(ui->EditFormula->text() + QString("sin("));
}

void MainWindow::on_ButtonTan_clicked()
{
    ui->EditFormula->setText(ui->EditFormula->text() + QString("tan("));
}

void MainWindow::on_ButtonLeftBracket_clicked()
{
    ui->EditFormula->setText(ui->EditFormula->text() + QString("("));
}

void MainWindow::on_ButtonRightBracket_clicked()
{
    ui->EditFormula->setText(ui->EditFormula->text() + QString(")"));
}

void MainWindow::on_ButtonASin_clicked()
{
    ui->EditFormula->setText(ui->EditFormula->text() + QString("asin("));
}

void MainWindow::on_ButtonACos_clicked()
{
    ui->EditFormula->setText(ui->EditFormula->text() + QString("acos("));
}

void MainWindow::on_ButtonATan_clicked()
{
    ui->EditFormula->setText(ui->EditFormula->text() + QString("atan("));
}

void MainWindow::on_ButtonMod_clicked()
{
    ui->EditFormula->setText(ui->EditFormula->text() + QString("mod"));
}

void MainWindow::on_ButtonDiv_clicked()
{
    ui->EditFormula->setText(ui->EditFormula->text() + QString("/"));
}

void MainWindow::on_ButtonPow_clicked()
{
    ui->EditFormula->setText(ui->EditFormula->text() + QString("^"));
}

void MainWindow::on_Button7_clicked()
{
    ui->EditFormula->setText(ui->EditFormula->text() + QString("7"));
}

void MainWindow::on_Button8_clicked()
{
    ui->EditFormula->setText(ui->EditFormula->text() + QString("8"));
}

void MainWindow::on_Button9_clicked()
{
    ui->EditFormula->setText(ui->EditFormula->text() + QString("9"));
}

void MainWindow::on_ButtonMult_clicked()
{
    ui->EditFormula->setText(ui->EditFormula->text() + QString("*"));
}

void MainWindow::on_ButtonSqrt_clicked()
{
    ui->EditFormula->setText(ui->EditFormula->text() + QString("sqrt("));
}

void MainWindow::on_Button4_clicked()
{
    ui->EditFormula->setText(ui->EditFormula->text() + QString("4"));
}

void MainWindow::on_Button5_clicked()
{
    ui->EditFormula->setText(ui->EditFormula->text() + QString("5"));
}

void MainWindow::on_Button6_clicked()
{
    ui->EditFormula->setText(ui->EditFormula->text() + QString("6"));
}

void MainWindow::on_ButtonPlus_clicked()
{
    ui->EditFormula->setText(ui->EditFormula->text() + QString("+"));
}

void MainWindow::on_ButtonLn_clicked()
{
    ui->EditFormula->setText(ui->EditFormula->text() + QString("ln("));
}

void MainWindow::on_Button1_clicked()
{
    ui->EditFormula->setText(ui->EditFormula->text() + QString("1"));
}

void MainWindow::on_Button2_clicked()
{
    ui->EditFormula->setText(ui->EditFormula->text() + QString("2"));
}

void MainWindow::on_Button3_clicked()
{
    ui->EditFormula->setText(ui->EditFormula->text() + QString("3"));
}

void MainWindow::on_ButtonMinus_clicked()
{
    ui->EditFormula->setText(ui->EditFormula->text() + QString("-"));
}

void MainWindow::on_ButtonLog_clicked()
{
    ui->EditFormula->setText(ui->EditFormula->text() + QString("log("));
}

void MainWindow::on_ButtonX_clicked()
{
    ui->EditFormula->setText(ui->EditFormula->text() + QString("x"));
}

void MainWindow::on_Button0_clicked()
{
    ui->EditFormula->setText(ui->EditFormula->text() + QString("0"));
}

void MainWindow::on_ButtonDot_clicked()
{
    ui->EditFormula->setText(ui->EditFormula->text() + QString("."));
}



