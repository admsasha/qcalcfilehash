#include <QApplication>
#include <QTranslator>
#include <QLibraryInfo>
#include <QCommandLineParser>

#include <openssl/engine.h>

#include "mainwindow.h"
#include "ObjectConsole.h"
#include "version.h"


// Engine gost initialization
int init_gost(){
    static ENGINE *e = NULL;

    ENGINE_load_builtin_engines();
    ENGINE_register_all_complete();

    e = ENGINE_by_id("gost");
    if (!e){
        // Can't find engine
        return 0;
    }
    if (!ENGINE_init(e)){
        // Engine initialization failed!
        ENGINE_free(e);
        return 0;
    }
    ENGINE_free(e);

    if (!ENGINE_set_default(e, ENGINE_METHOD_ALL)) {
        // Initialized but not usable
        return 0;
    }

    return 1;
}


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
        if (translator.load(QString("langs/qcalcfilehash_") + locale)==false){
            translator.load(QString("/usr/share/qcalcfilehash/langs/qcalcfilehash_") + locale);
        }
    }

    int gostSupport = init_gost();


    bool showProgress=false;
    bool showlistOption=false;
    bool isForceGui=false;
    QStringList listPositionalArguments;
    QString compareHash="";

    {
        QCoreApplication app(argc, argv);
        QCoreApplication::setApplicationName("QCalcFileHash");
        QCoreApplication::setApplicationVersion(VERSION);
        QCoreApplication::setOrganizationDomain("dansoft.ru");

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

        QCommandLineOption forceGui(QStringList() << "gui", QCoreApplication::tr("Open in gui"));
        parser.addOption(forceGui);

        parser.process(app);

        listPositionalArguments = parser.positionalArguments();
        showProgress = parser.isSet(showProgressOption);
        showlistOption = parser.isSet(listOption);
        compareHash = parser.value(CompareHash);
        isForceGui = parser.isSet(forceGui);
    }

    if (listPositionalArguments.size()!=0 or showlistOption!=false){
        useGUI=false;
    }
    if (isForceGui) useGUI=true;


    if (useGUI){
        QApplication app(argc, argv);

        app.installTranslator(&qtTranslator);
        app.installTranslator(&translator);

        MainWindow form(nullptr,gostSupport);
        if (listPositionalArguments.size()>=1) form.setFilename(listPositionalArguments.at(0));
        if (listPositionalArguments.size()>=2) form.setHash(listPositionalArguments.at(1));

        form.show();
        form.startCalc();

        return app.exec();
    }else{
        QCoreApplication app(argc, argv);

        app.installTranslator(&qtTranslator);
        app.installTranslator(&translator);

        ObjectConsole form(nullptr,gostSupport);
        form.calcHash(listPositionalArguments,showProgress,showlistOption,compareHash);

        return app.exec();
    }
}
