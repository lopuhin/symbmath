#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "parser.cpp"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

Tree* MainWindow::get_expr() {
    QString s = ui->exprInput->text();
    return parse(s.toAscii().data());
}

void MainWindow::on_simplifyButton_clicked()
{
    get_expr()->print();
}

void MainWindow::on_diffButton_clicked()
{

}

void MainWindow::on_integrateButton_clicked()
{

}

void MainWindow::on_exprInput_returnPressed()
{
    get_expr()->print();
}
