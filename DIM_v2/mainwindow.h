#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "emulator.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    Emulator* emu;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Btn_Random_clicked();

    void on_Btn_AppNode_clicked();

    void on_Btn2_AppName_clicked();

    void on_Btn_Start_clicked();

    void on_Btn_Stop_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
