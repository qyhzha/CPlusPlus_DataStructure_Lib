#include "QObject"
#include "QString"
#include "QExcePtion"
#include "QDebug"

class QMedirPlayer : public qLib::QObject
{
    public :
        virtual void play(const qLib::QString &fileName, const qLib::QString &fileFormat) const = 0;
};

class QAdvancedMediaPlayer : public qLib::QObject
{
    public :
        virtual void playVlc(const qLib::QString &fileName) const = 0;
        virtual void playMp4(const qLib::QString &fileName) const = 0;
};

class QVlcPlayer : public QAdvancedMediaPlayer
{
    public :
        void playVlc(const qLib::QString &fileName) const
        {
            qLib::qDebug() << "this is a vlc filename. filename : " << fileName;
        }

        void playMp4(const qLib::QString &fileName) const
        {
            //null
        }
};

class QMp4Player : public QAdvancedMediaPlayer
{
    public :
        void playVlc(const qLib::QString &fileName) const
        {
            //null
        }

        void playMp4(const qLib::QString &fileName) const
        {
            qLib::qDebug() << "this is a mp4 filename. filename : " << fileName;
        }
};

class QMedirPlayerAdapter : public QMedirPlayer
{
    public :
        void play(const qLib::QString &fileName, const qLib::QString &fileFormat) const
        {
            if (qLib::QString::compare(fileFormat, "vlc", qLib::CaseInsensitive) == 0)
            {
                QVlcPlayer().playVlc(fileName);
            }
            else if (qLib::QString::compare(fileFormat, "mp4", qLib::CaseInsensitive) == 0)
            {
                QMp4Player().playMp4(fileName);
            }
            else
            {
                qLib::qDebug() << "not support format.";
            }
        }
};

class QAudioPlayer : public QMedirPlayer
{
    public :
        void play(const qLib::QString &fileName, const qLib::QString &fileFormat) const
        {
            QMedirPlayerAdapter().play(fileName, fileFormat);
        }
};

void AdapterPatternDemo()
{
    try
    {
        QAudioPlayer().play("audio.mp4", "mp4");
    }
    catch(const qLib::QException& e)
    {
        qLib::qDebug() << "Location : " << e.location();
        qLib::qDebug() << "Message : " << e.message();
    }
}