#ifndef OBJECTCONSOLE_H
#define OBJECTCONSOLE_H

#include <QObject>

class ObjectConsole : public QObject{
    Q_OBJECT
    public:
        explicit ObjectConsole(QObject *parent = nullptr);

        void calcHash(QStringList listPositionalArguments, bool showProgress, bool showlistOption);

    private:
        int current_progress;

        bool _showProgress;

    signals:

    private slots:
        void calcHashChangeValue(int value);
        void calcHashResult(QString hash);
};

#endif // OBJECTCONSOLE_H
