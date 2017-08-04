#include <QApplication>
#include <QTranslator>
#include <QLibraryInfo>

#include "mainwindow.h"

int main(int argc, char *argv[]){
    QApplication app(argc, argv);

    QTranslator translator;
    QTranslator qtTranslator;
    QString locale = QLocale::system().name();

    qtTranslator.load("qt_"+locale,QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    app.installTranslator(&qtTranslator);

    if (translator.load(QString("qcalcfilehash_") + locale)==false){
        translator.load(QString("/usr/share/qcalcfilehash/qcalcfilehash_") + locale);
    }
    app.installTranslator(&translator);

    MainWindow form;
    form.show();

    return app.exec();
}
