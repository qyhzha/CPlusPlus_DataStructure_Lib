#include "QObject"
#include "QString"
#include "QSize"
#include "QDebug"
#include "QException"

class QDownloader : public qLib::QObject
{
    public :
        int download(void *buffer, int size) const;
};

class QHttpDownloader : public QDownloader
{
    public :
        int download(void *buffer, int size) const
        {
            if (buffer == NULL || size <= 0) return;

            
        }
};