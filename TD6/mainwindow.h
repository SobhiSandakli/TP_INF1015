#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
#include <QCheckBox>
#include <QApplication>
#include <QLabel>
#include <QMessageBox>
#include "caisse.h"
#include <cmath>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void createMainWindow();
    void createPrix();
    void afficherListeArticle();

    Ui::MainWindow *ui;
    Caisse* caisse_;

public slots:
    void refreshView();

private slots:
    void on_ajouterBtn_clicked();
    void on_retirerBtn_clicked();
    void on_reinitialiserBtn_clicked();
};
#endif // MAINWINDOW_H
