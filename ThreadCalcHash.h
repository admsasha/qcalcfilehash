#ifndef THREADCALCHASH_H
#define THREADCALCHASH_H

#include <QThread>

enum class HASH_ALGORITHM : int {
    Crc8,
    Crc32,
    Md5,
    Sha1,
    Sha224,
    Sha256,
    Sha384,
    Sha512,
};

class ThreadCalcHash : public QThread {
    Q_OBJECT
    public:
        ThreadCalcHash();
        ~ThreadCalcHash();
        void run();

        void setFilename(QString filename);
        void setHashAlgorithm(HASH_ALGORITHM algorithm);

    private:
        QString _filename;
        HASH_ALGORITHM _hashAlgorithm;

        std::string getCrc8FromFile(const std::string &filename);
        std::string getCrc32FromFile(const std::string &filename);
        std::string getMD5FromFile(const std::string &filename);
        std::string getSHA1FromFile(const std::string &filename);
        std::string getSHA224FromFile(const std::string &filename);
        std::string getSHA256FromFile(const std::string &filename);
        std::string getSHA384FromFile(const std::string &filename);
        std::string getSHA512FromFile(const std::string &filename);

    private slots:

    signals:
        void changeValue(int);
        void result(QString);

};

#endif // THREADCALCHASH_H
