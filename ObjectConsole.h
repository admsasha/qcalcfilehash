#ifndef OBJECTCONSOLE_H
#define OBJECTCONSOLE_H

#include <QObject>

class ObjectConsole : public QObject{
    Q_OBJECT
    public:
        explicit ObjectConsole(QObject *parent = nullptr,int gostSupport=0);

        void calcHash(QStringList listPositionalArguments, bool showProgress, bool showlistOption, QString compareHash);

    private:
        int _gostSupport;

        int current_progress;

        bool _showProgress;
        QString _compareHash;

    signals:

    private slots:
        void calcHashChangeValue(int value);
        void calcHashResult(QString hash);
};

#endif // OBJECTCONSOLE_H
