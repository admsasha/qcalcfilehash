#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QFileDialog>
#include <QDateTime>
#include <QDebug>
#include <QScreen>
#include <QTimer>
#include <QMimeData>

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
        ui->comboBox->addItem(tr("GOST R 34.11-94"),static_cast<int>(HASH_ALGORITHM::md_gost94));
        ui->comboBox->addItem(tr("GOST R 34.11-2012 (256 bit)"),static_cast<int>(HASH_ALGORITHM::md_gost12_256));
        ui->comboBox->addItem(tr("GOST R 34.11-2012 (512 bit)"),static_cast<int>(HASH_ALGORITHM::md_gost12_512));
    }
    ui->comboBox->setCurrentIndex(0);

    ui->label->setText("");
    ui->progressBar->setValue(0);
    ui->progressBar->setEnabled(false);

    setAcceptDrops(true);

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

    ui->textEdit->setText("");
    resultCompare();
}

void MainWindow::setHash(QString hashName){
    for (int i=0;i<ui->comboBox->count();i++){
        if ((hashName=="md_gost94" and ui->comboBox->itemData(i).toInt()==static_cast<int>(HASH_ALGORITHM::md_gost94)) or
            (hashName=="md_gost12_256" and ui->comboBox->itemData(i).toInt()==static_cast<int>(HASH_ALGORITHM::md_gost12_256)) or
            (hashName=="md_gost12_512" and ui->comboBox->itemData(i).toInt()==static_cast<int>(HASH_ALGORITHM::md_gost12_512))
        ){
            ui->comboBox->setCurrentIndex(i);
            return;
        }
        if (ui->comboBox->itemText(i).toLower()==hashName.toLower()){
            ui->comboBox->setCurrentIndex(i);
            return;
        }
    }
}

void MainWindow::startCalc(){
    emit calcHash();
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event){
    if (event->mimeData()->hasUrls()) {
        event->accept();
    }
}

void MainWindow::dropEvent(QDropEvent *event){
    const QMimeData* mimeData = event->mimeData();

    if (mimeData->hasUrls() and mimeData->urls().size()>0){
        setFilename(mimeData->urls().at(0).toLocalFile());
    }
}

void MainWindow::openfile(){
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open file"), "", tr("All Files (*)"));
    if (fileName.size() <= 0) return;

    setFilename(fileName);
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
	QString ourhash = ui->textEdit->toPlainText();
	QString userhash = ui->lineEdit->text();
	// if there is nothing to compare
	if ( QString::compare(ourhash, "", Qt::CaseInsensitive) == 0 ||
	     QString::compare(userhash, "", Qt::CaseInsensitive) == 0 ) {
	    ui->label_6->setText("");
	    return;
	}
    if (QString::compare(ourhash, userhash, Qt::CaseInsensitive) == 0) {
        ui->label_6->setText("<font color=\"#005500\">"+tr("equally")+"</font>");
    }else{
        ui->label_6->setText("<font color=\"#ff0000\">"+tr("different")+"</font>");
    }
}
