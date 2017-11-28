#include "CopyTask.h"

void CopyDirsEx(QString sSrcPath, QString sDestPath, QStringList& listFileTails)
{
    // 目录打开并检查
    QDir dirSrc(sSrcPath);
    if (!dirSrc.exists())
        return;

    // 设置过滤类型与文件排序方式
    dirSrc.setFilter(QDir::Dirs|QDir::Files);
    dirSrc.setSorting(QDir::DirsLast);

    //获取文件信息列表
    QFileInfoList fileInfoList = dirSrc.entryInfoList();

    // 不为空，才创建列表
    if (!fileInfoList.empty())
    {
        QDir().mkdir(sDestPath);
    }

    // 遍历处理
    for (size_t i=0; i<fileInfoList.size(); i++)
    {
        QFileInfo fileInfo = fileInfoList.at(i);

        // 处理特殊文件
        if(fileInfo.fileName() == "." | fileInfo.fileName() == "..")
        {
            continue;
        }

        bool bIsDir = fileInfo.isDir();
        if (bIsDir)
        {
            CopyDirsEx(sSrcPath + "\\" + fileInfo.fileName(), sDestPath + "\\" + fileInfo.fileName(), listFileTails);
        }
        else
        {
            if (listFileTails.contains(fileInfo.suffix()))
            {
                bool bRt = QFile::copy(sSrcPath  + "\\" + fileInfo.fileName(), sDestPath +  "\\" + fileInfo.fileName());

                if (!bRt)
                {
                    QString sDebugInfo = QString("Copy %1 to %2 rt=%3")
                        .arg(sSrcPath  + "\\" + fileInfo.fileName())
                        .arg(sDestPath  + "\\" + fileInfo.fileName())
                        .arg(bRt);
                    qDebug(sDebugInfo.toLocal8Bit());
                }
            }
        }
    }
}

void MyCopyThread::run()
{
    // 获取输入参数
    QStringList lstFileTails = m_sFileTails.split(";");
    for (int i=lstFileTails.count() - 1; i>=0; i--)
    {
        lstFileTails[i] = lstFileTails[i].trimmed();
        if (lstFileTails[i].isEmpty())
        {
            lstFileTails.removeAt(i);
        }
    }
    CopyDirsEx(m_sSrcPath, m_sDestPath, lstFileTails);
    m_pTask->onFinishProc();
}



