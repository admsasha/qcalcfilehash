#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QFileDialog>
#include <QDateTime>

#include "ThreadCalcHash.h"
#include "version.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("QCalcFileHash v"+QString(VERSION)+" ("+QString(DATE_BUILD)+")");
    //this->setFixedSize(this->width(),this->height());

    changeShowCompareForm();
    ui->label_6->setText("");

    connect(ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(close()));
    connect(ui->pushButton_2,SIGNAL(clicked(bool)),this,SLOT(openfile()));
    connect(ui->pushButton_3,SIGNAL(clicked(bool)),this,SLOT(calcHash()));
    connect(ui->pushButton_4,SIGNAL(clicked(bool)),this,SLOT(changeShowCompareForm()));
    connect(ui->lineEdit,SIGNAL(textChanged(QString)),this,SLOT(resultCompare()));

    ui->comboBox->addItem("CRC-8",static_cast<int>(HASH_ALGORITHM::Crc8));
    ui->comboBox->addItem("CRC-32",static_cast<int>(HASH_ALGORITHM::Crc32));
    ui->comboBox->addItem("MD4",static_cast<int>(HASH_ALGORITHM::Md4));
    ui->comboBox->addItem("MD5",static_cast<int>(HASH_ALGORITHM::Md5));
    ui->comboBox->addItem("SHA-1",static_cast<int>(HASH_ALGORITHM::Sha1));
    ui->comboBox->addItem("SHA-224",static_cast<int>(HASH_ALGORITHM::Sha224));
    ui->comboBox->addItem("SHA-256",static_cast<int>(HASH_ALGORITHM::Sha256));
    ui->comboBox->addItem("SHA-384",static_cast<int>(HASH_ALGORITHM::Sha384));
    ui->comboBox->addItem("SHA-512",static_cast<int>(HASH_ALGORITHM::Sha512));
    ui->comboBox->setCurrentIndex(0);

    ui->label->setText("");
    ui->progressBar->setValue(0);
    ui->progressBar->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openfile(){
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open file"), "", tr("All Files (*)"));
    if (fileName.size() <= 0) return;

    ui->label->setText(fileName);
    _filename=fileName;
}

void MainWindow::calcHashChangeValue(int value) {
    ui->progressBar->setValue(value);
}

void MainWindow::calcHashResult(QString hash) {
    ui->textEdit->setText(hash);

    ui->progressBar->setValue(0);
    ui->progressBar->setEnabled(false);
    ui->pushButton_3->setEnabled(true);

    resultCompare();
}

void MainWindow::changeShowCompareForm(){
    if (ui->pushButton_4->isChecked()){
        //this->setFixedHeight(292);
        ui->label_6->setVisible(true);
        ui->label_5->setVisible(true);
        ui->lineEdit->setVisible(true);

        ui->pushButton->move(ui->pushButton->x(),260);
        ui->pushButton_4->move(ui->pushButton_4->x(),260);
        ui->label_4->move(ui->label_4->x(),270);
    }else{
        //this->setFixedHeight(222);
        ui->label_6->setVisible(false);
        ui->label_5->setVisible(false);
        ui->lineEdit->setVisible(false);

        ui->pushButton->move(ui->pushButton->x(),190);
        ui->pushButton_4->move(ui->pushButton_4->x(),190);
        ui->label_4->move(ui->label_4->x(),200);
    }
}


void MainWindow::calcHash(){
    ui->progressBar->setValue(0);
    ui->progressBar->setEnabled(true);
    ui->textEdit->setText("");
    ui->pushButton_3->setEnabled(false);


    ThreadCalcHash *thCaclHash = new ThreadCalcHash();
    thCaclHash->setFilename(_filename);
    thCaclHash->setHashAlgorithm(HASH_ALGORITHM(ui->comboBox->currentData().toInt()));

    connect(thCaclHash,SIGNAL(changeValue(int)),this,SLOT(calcHashChangeValue(int)));
    connect(thCaclHash,SIGNAL(result(QString)),this,SLOT(calcHashResult(QString)));

    thCaclHash->start();
}


void MainWindow::resultCompare(){
    if (ui->textEdit->toPlainText().toUpper()==ui->lineEdit->text().toUpper()){
        ui->label_6->setText(tr("equally"));
    }else{
        ui->label_6->setText(tr("different"));
    }
}
