#ifndef THREADCALCHASH_H
#define THREADCALCHASH_H

#include <QThread>

enum class HASH_ALGORITHM : int {
    Crc8,
    Crc32,
    Md4,
    Md5,
    Sha1,
    Sha224,
    Sha256,
    Sha384,
    Sha512,
    md_gost94,
    md_gost12_256,
    md_gost12_512
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

        std::string opensslEvp(const std::string &filename,const std::string &digest);

        std::string getCrc8FromFile(const std::string &filename);
        std::string getCrc32FromFile(const std::string &filename);
        std::string getMD4FromFile(const std::string &filename);
        std::string getMD5FromFile(const std::string &filename);
        std::string getSHA1FromFile(const std::string &filename);
        std::string getSHA224FromFile(const std::string &filename);
        std::string getSHA256FromFile(const std::string &filename);
        std::string getSHA384FromFile(const std::string &filename);
        std::string getSHA512FromFile(const std::string &filename);

        std::string getGost94FromFile(const std::string &filename);
        std::string getGost12_256FromFile(const std::string &filename);
        std::string getGost12_512FromFile(const std::string &filename);
    private slots:

    signals:
        void changeValue(int);
        void result(QString);

};

#endif // THREADCALCHASH_H
