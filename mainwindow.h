#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDropEvent>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0,int gostSupport=0);
        ~MainWindow();
        void setFilename(QString filename);
        void setHash(QString hashName);
        void startCalc();

    protected:
        void dragEnterEvent(QDragEnterEvent *event) override;
        void dropEvent(QDropEvent* event) override;

    private:
        Ui::MainWindow *ui;

        QString _filename;
        int _gostSupport;

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
