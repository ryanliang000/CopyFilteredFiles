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
    // 主线程调用：等待finished消息
    void waitTaskFinish()
    {
        connect(this, SIGNAL(finished()), &m_loop, SLOT(quit()));
        m_loop.exec();
    }

    // 子线程调用：发送finished消息
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
        // 任务移入到线程中
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


