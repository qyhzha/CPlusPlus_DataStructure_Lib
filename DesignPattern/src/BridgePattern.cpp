#include "QObject"
#include "QString"
#include "QSize"
#include "QDebug"
#include "QException"
#include <cstring>

class QDownloader : public qLib::QObject
{
    public :
        virtual int download(void *buffer, int size) const = 0;
};

class QHttpDownloader : public QDownloader
{
    public :
        int download(void *buffer, int size) const
        {
            if (buffer == NULL || size <= 0) return -1;

            const char *data = "http12345678901234567890";

            int length = size < strlen(data) ? size : strlen(data);

            memcpy(buffer, data, length);

            return length;
        }
};

class QUartDownloader : public QDownloader
{
    public :
        int download(void *buffer, int size) const
        {
            if (buffer == NULL || size <= 0) return -1;

            const char *data = "uart12345678901234567890";

            int length = size < strlen(data) ? size : strlen(data);

            memcpy(buffer, data, length);

            return length;
        }
};

class QDownloadDemo : public qLib::QObject
{
    protected :
        QDownloader *m_downloader;

    public :
        QDownloadDemo()
        {
            this->m_downloader = NULL;
        }

        QDownloader *downloader() const
        {
            return this->m_downloader;
        }

        void setDownloader(QDownloader *downloader)
        {
            this->m_downloader = downloader;
        }

        int download(int size) const
        {
            if (this->m_downloader == NULL)
            {
                return -1;
            }

            char *buffer = new char[size + 1];

            int result = this->m_downloader->download(buffer, size);
            if (result > 0)
            {
                buffer[result] = '\0';
                qLib::qDebug() << "data : " << buffer;
            }

            delete[] buffer;

            return result;
        }
};

void BridgePatternDemo()
{
    QDownloadDemo downloadDemo;

    int size = downloadDemo.download(50);

    qLib::qDebug() << "size : " << size;

    downloadDemo.setDownloader(new QHttpDownloader());

    size = downloadDemo.download(50);

    qLib::qDebug() << "size : " << size;

    delete downloadDemo.downloader();

    downloadDemo.setDownloader(new QUartDownloader());

    size = downloadDemo.download(50);

    qLib::qDebug() << "size : " << size;

    delete downloadDemo.downloader();
}