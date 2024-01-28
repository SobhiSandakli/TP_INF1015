#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "exception.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    caisse_ = new Caisse();
    createMainWindow();
    createPrix();
    QObject::connect(caisse_, &Caisse::refresh, this, &MainWindow::refreshView);
}

MainWindow::~MainWindow()
{
    delete caisse_;
    delete ui;
}

void MainWindow::createMainWindow()
{
    setWindowTitle("Caisse Enregristreuse");
    afficherListeArticle();
}

void MainWindow::createPrix()
{
    double avantTaxes = caisse_->getTotalPreTaxes();
    double taxes = caisse_->getTotalTaxes();

    ui->totalAvantTaxes->setText(QString::number(avantTaxes, 'f',2));
    ui->totalTaxes->setText(QString::number(taxes, 'f',2));
    ui->total->setText(QString::number(taxes + avantTaxes, 'f',2));
}

void MainWindow::afficherListeArticle()
{
    ui->listArticles->clear();
    vector<Article*> articles = caisse_->getListeArticle();

    for (auto elem: articles) {
        std::string affichage = elem->description + "\t" + QString::number(elem->prix, 'f',2).toStdString();
        if (elem->taxable == true) {affichage += "\t taxable";}

        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(affichage),ui->listArticles);
        item->setData(Qt::UserRole, QVariant::fromValue<Article*>(elem));
    }

    ui->retirerBtn->setDisabled(articles.empty());
}

void MainWindow::refreshView()
{
    afficherListeArticle();
    createPrix();
}

void MainWindow::on_ajouterBtn_clicked()
{
    try {
        Article* article = new Article;
        article->description = ui->editDescription->text().toStdString();
        article->prix = ui->editPrix->text().replace(',', '.').toDouble();
        article->taxable = ui->checkBoxTax->isChecked();
        caisse_->ajouterArticle(article);

    } catch (ExceptionEntreeValeur& e) {
        QMessageBox messageBox;
        messageBox.critical(0, "Erreur d'entrée de valeur", e.what());
    }
}

void MainWindow::on_retirerBtn_clicked()
{
    std::vector<Article*> aEnlever;

    for (QListWidgetItem *item : ui->listArticles->selectedItems()) {
        aEnlever.push_back(item->data(Qt::UserRole).value<Article*>());
    }

    for(Article* a: aEnlever){
        caisse_->retirerArticle(a);
    }
}

void MainWindow::on_reinitialiserBtn_clicked()
{
    for (Article* a : caisse_->getListeArticle()){
        caisse_->retirerArticle(a);
    }

    ui->listArticles->clear();
    ui->editDescription->clear();
    ui->editPrix->clear();
    ui->checkBoxTax->setChecked(false);
    ui->totalAvantTaxes->setText(QString::number(0, 'f',2));
    ui->totalTaxes->setText(QString::number(0, 'f',2));
    ui->total->setText(QString::number(0, 'f',2));
}
