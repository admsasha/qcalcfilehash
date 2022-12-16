#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QFileDialog>
#include <QDateTime>
#include <QDebug>
#include <QScreen>
#include <QTimer>

#include "ThreadCalcHash.h"
#include "version.h"


MainWindow::MainWindow(QWidget *parent, int gostSupport) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _gostSupport(gostSupport)
{
    ui->setupUi(this);
    this->setWindowTitle("QCalcFileHash v"+QString(VERSION)+" ("+QString(DATE_BUILD)+")");

    changeShowCompareForm();
    ui->label_6->setText("");
    ui->label_4->setText(tr("Copyright 2017-2022 DanSoft.")+tr("All rights reserved."));

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
    if (gostSupport){
        ui->comboBox->addItem("md_gost94",static_cast<int>(HASH_ALGORITHM::md_gost94));
        ui->comboBox->addItem("md_gost12_256",static_cast<int>(HASH_ALGORITHM::md_gost12_256));
        ui->comboBox->addItem("md_gost12_512",static_cast<int>(HASH_ALGORITHM::md_gost12_512));
    }
    ui->comboBox->setCurrentIndex(0);

    ui->label->setText("");
    ui->progressBar->setValue(0);
    ui->progressBar->setEnabled(false);

    QTimer::singleShot(100,[&](){
        // move to center
        this->move((qApp->primaryScreen()->size().width()-this->width())/2,(qApp->primaryScreen()->size().height()-this->height())/2);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setFilename(QString filename){
    ui->label->setText(filename);
    _filename=filename;
}

void MainWindow::setHash(QString hashName){
    for (int i=0;i<ui->comboBox->count();i++){
        if (ui->comboBox->itemText(i).toLower()==hashName.toLower()){
            ui->comboBox->setCurrentIndex(i);
            return;
        }
    }
}

void MainWindow::startCalc(){
    emit calcHash();
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
        ui->label_6->setVisible(true);
        ui->label_5->setVisible(true);
        ui->lineEdit->setVisible(true);
    }else{
        ui->label_6->setVisible(false);
        ui->label_5->setVisible(false);
        ui->lineEdit->setVisible(false);
    }
}


void MainWindow::calcHash(){
    if (_filename.isEmpty()) return;

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
        ui->label_6->setText("<font color=\"#005500\">"+tr("equally")+"</font>");
    }else{
        ui->label_6->setText("<font color=\"#ff0000\">"+tr("different")+"</font>");
    }
}
