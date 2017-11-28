#pragma once
#include "qdir.h"
#include "qwaitcondition.h"
#include "qfiledialog.h"
#include "qmessagebox.h"
#include "qthread.h"
#include "qexception.h"
#include "qeventloop.h"

class MyThreadWaitTask : public QObject
{
    Q_OBJECT   
public:
    MyThreadWaitTask(){}

signals:
    void finished();

public:
    // ���̵߳��ã��ȴ�finished��Ϣ
    void waitTaskFinish()
    {
        connect(this, SIGNAL(finished()), &m_loop, SLOT(quit()));
        m_loop.exec();
    }

    // ���̵߳��ã�����finished��Ϣ
    void onFinishProc()
    {
        emit finished();
    }
private:
    QEventLoop m_loop;
};


class MyCopyThread  : public QThread
{
public:
    MyCopyThread(QObject * pParent, MyThreadWaitTask* pTask, QString srcPath, QString destPath, QString fileTails)
        : QThread(pParent)
        , m_pTask(pTask)
        , m_sSrcPath(srcPath)
        , m_sDestPath(destPath)
        , m_sFileTails(fileTails)
    {
        // �������뵽�߳���
        pTask->moveToThread(this);
    };
    ~MyCopyThread(){};
    virtual void run();

private:
    MyThreadWaitTask* m_pTask; 
    QString m_sSrcPath;
    QString m_sDestPath;
    QString m_sFileTails;
};


