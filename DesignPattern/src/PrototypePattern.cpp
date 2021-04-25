#include "QString"
#include "QDebug"

class QPrototype : public qLib::QObject
{
    protected :
        qLib::QString m_id;
        qLib::QString m_value;

        void init()
        {
            //复杂的初始化工作，比如从远端数据库获取真实值
            this->m_id = "name";
            this->m_value = "yonghang.qin";
        }

        QPrototype(const QPrototype &obj)
        {
            //从已经初始化完成的对象拷贝值
            this->m_id = obj.m_id;
            this->m_value = obj.m_value;
        }

        QPrototype &operator=(const QPrototype &obj);

    public :
        QPrototype()
        {
            init();
        }

        QPrototype *clone()
        {
            return new QPrototype(*this);
        }

        const qLib::QString &id() const
        {
            return this->m_id;
        }

        const qLib::QString &value() const
        {
            return this->m_value;
        }
};

void PrototypePatternDemo()
{
    QPrototype obj;

    qLib::qDebug() << obj.id() << " : " << obj.value();

    QPrototype *cloneObj = obj.clone();
    if (cloneObj == NULL)
    {
        qLib::qDebug() << "clone fail.";
        return;
    }

    qLib::qDebug() << cloneObj->id() << " : " << cloneObj->value();

    delete cloneObj;
}