#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tree.cpp"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Tree* get_expr();

private slots:
    void on_exprInput_returnPressed();
    void on_integrateButton_clicked();
    void on_diffButton_clicked();
    void on_simplifyButton_clicked();
};

#endif // MAINWINDOW_H
