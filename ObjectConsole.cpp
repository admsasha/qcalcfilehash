#include "ObjectConsole.h"

#include "ThreadCalcHash.h"
#include <QCoreApplication>

#include <QDebug>


#include <iostream>

ObjectConsole::ObjectConsole(QObject *parent) : QObject(parent){
    current_progress=0;
}

void ObjectConsole::calcHash(QStringList listPositionalArguments,bool showProgress,bool showlistOption){
    if (showlistOption){
        std::cout << "CRC-8, CRC-32, MD4, MD5, SHA-1, SHA-224, SHA-256, SHA-384, SHA-512" << std::endl;
        exit(0);
    }

    if (listPositionalArguments.size()!=2){
        qDebug() << tr("Invalid positional arguments");
        exit(0);
    }

    QString filename = listPositionalArguments.at(0);
    QString hashAlgorithm = listPositionalArguments.at(1);
    HASH_ALGORITHM hash = HASH_ALGORITHM::Crc8;

    _showProgress=showProgress;


    if (hashAlgorithm=="CRC-8"){
        hash=HASH_ALGORITHM::Crc8;
    }else if (hashAlgorithm=="CRC-32"){
        hash=HASH_ALGORITHM::Crc32;
    }else if (hashAlgorithm=="MD4"){
        hash=HASH_ALGORITHM::Md4;
    }else if (hashAlgorithm=="MD5"){
        hash=HASH_ALGORITHM::Md5;
    }else if (hashAlgorithm=="SHA-1"){
        hash=HASH_ALGORITHM::Sha1;
    }else if (hashAlgorithm=="SHA-224"){
        hash=HASH_ALGORITHM::Sha224;
    }else if (hashAlgorithm=="SHA-256"){
        hash=HASH_ALGORITHM::Sha256;
    }else if (hashAlgorithm=="SHA-384"){
        hash=HASH_ALGORITHM::Sha384;
    }else if (hashAlgorithm=="SHA-512"){
        hash=HASH_ALGORITHM::Sha512;
    }else{
        qDebug() << tr("Invalid hash argument");
        exit(0);
    }

    std::cout << tr("Filename: ").toStdString() << filename.toStdString() << std::endl;

    ThreadCalcHash *thCaclHash = new ThreadCalcHash();
    thCaclHash->setFilename(filename);
    thCaclHash->setHashAlgorithm(hash);

    if (showProgress){
        connect(thCaclHash,SIGNAL(changeValue(int)),this,SLOT(calcHashChangeValue(int)));
    }
    connect(thCaclHash,SIGNAL(result(QString)),this,SLOT(calcHashResult(QString)));

    thCaclHash->start();
}

void ObjectConsole::calcHashChangeValue(int value){
    int proc = value/10;

    std::cout << "\033[0G";

    std::cout << "calc: [";
    for (int i=0;i<proc;i++) std::cout << "#" ;
    for (int i=0;i<10-proc;i++) std::cout << " " ;
    std::cout << "] " << value << "% " << std::flush;


}

void ObjectConsole::calcHashResult(QString hash){
    if (_showProgress) std::cout << std::endl;

    qDebug() << "result: " << hash;
    exit(0);
}
