#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

    private:
        Ui::MainWindow *ui;

        QString _filename;

        int oldValueProcHash;

    private slots:
        void calcHash();
        void openfile();

        void calcHashChangeValue(int value);
        void calcHashResult(QString hash);

        void changeShowCompareForm();
        void resultCompare();

};

#endif // MAINWINDOW_H
