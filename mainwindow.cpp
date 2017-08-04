#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QFileDialog>
#include <QDateTime>

#include "ThreadCalcHash.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("QCalcFileHash v1.0.0 (04.08.2017)");
    this->setFixedSize(this->width(),this->height());

    connect(ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(close()));
    connect(ui->pushButton_2,SIGNAL(clicked(bool)),this,SLOT(openfile()));
    connect(ui->pushButton_3,SIGNAL(clicked(bool)),this,SLOT(calcHash()));

    ui->comboBox->addItem("CRC-8",(int)HASH_ALGORITHM::Crc8);
    ui->comboBox->addItem("CRC-32",(int)HASH_ALGORITHM::Crc32);
    ui->comboBox->addItem("MD4",(int)HASH_ALGORITHM::Md4);
    ui->comboBox->addItem("MD5",(int)HASH_ALGORITHM::Md5);
    ui->comboBox->addItem("SHA-1",(int)HASH_ALGORITHM::Sha1);
    ui->comboBox->addItem("SHA-224",(int)HASH_ALGORITHM::Sha224);
    ui->comboBox->addItem("SHA-256",(int)HASH_ALGORITHM::Sha256);
    ui->comboBox->addItem("SHA-384",(int)HASH_ALGORITHM::Sha384);
    ui->comboBox->addItem("SHA-512",(int)HASH_ALGORITHM::Sha512);
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
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open file"), "", tr("All Files (*.*)"));
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
