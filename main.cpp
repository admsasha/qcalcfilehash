#include <QApplication>
#include <QTranslator>
#include <QLibraryInfo>
#include <QCommandLineParser>
#include <QDebug>

#include "mainwindow.h"
#include "ObjectConsole.h"
#include "version.h"

#include <iostream>


int main(int argc, char *argv[]){
#ifdef Q_OS_LINUX
    bool useGUI = getenv("DISPLAY") != NULL;
#else
    bool useGUI = true;
#endif



    QTranslator translator;
    QTranslator qtTranslator;
    QString locale = QLocale::system().name();

    qtTranslator.load("qt_"+locale,QLibraryInfo::location(QLibraryInfo::TranslationsPath));

    if (translator.load(QString("qcalcfilehash_") + locale)==false){
        translator.load(QString("/usr/share/qcalcfilehash/langs/qcalcfilehash_") + locale);
    }


    bool showProgress=false;
    bool showlistOption=false;
    QStringList listPositionalArguments;
    QString compareHash="";

    {
        QCoreApplication app(argc, argv);
        QCoreApplication::setApplicationName("QCalcFileHash");
        QCoreApplication::setApplicationVersion(VERSION);
        QCoreApplication::setOrganizationDomain("dansoft.krasnokamensk.ru");

        app.installTranslator(&qtTranslator);
        app.installTranslator(&translator);


        QCommandLineParser parser;
        parser.setApplicationDescription("Calculator hash (SHA1, SHA-224, SHA-256, SHA-384, SHA-512, MD5, CRC32, CRC8)");
        parser.addHelpOption();
        parser.addVersionOption();
        parser.addPositionalArgument("filename", QCoreApplication::tr("Source file to hash"));
        parser.addPositionalArgument("hash", QCoreApplication::tr("Hash algorithm"));

        QCommandLineOption CompareHash(QStringList() << "compare",
                QCoreApplication::tr("hash comparison"),
                QCoreApplication::tr("hash"));
        parser.addOption(CompareHash);


        QCommandLineOption showProgressOption("p", QCoreApplication::tr("Show progress"));
        parser.addOption(showProgressOption);

        QCommandLineOption listOption(QStringList() << "l" << "list", QCoreApplication::tr("Show list all hash algorithm"));
        parser.addOption(listOption);

        parser.process(app);

        listPositionalArguments = parser.positionalArguments();
        showProgress = parser.isSet(showProgressOption);
        showlistOption = parser.isSet(listOption);
        compareHash = parser.value(CompareHash);

    }

    if (listPositionalArguments.size()!=0 or showlistOption!=false){
        useGUI=false;
    }

    if (useGUI){
        QApplication app(argc, argv);

        app.installTranslator(&qtTranslator);
        app.installTranslator(&translator);

        MainWindow form;
        form.show();

        return app.exec();
    }else{
        QCoreApplication app(argc, argv);

        app.installTranslator(&qtTranslator);
        app.installTranslator(&translator);

        ObjectConsole form;
        form.calcHash(listPositionalArguments,showProgress,showlistOption,compareHash);

        return app.exec();
    }
}
