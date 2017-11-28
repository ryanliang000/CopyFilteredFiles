#include "CopyTask.h"

void CopyDirsEx(QString sSrcPath, QString sDestPath, QStringList& listFileTails)
{
    // Ŀ¼�򿪲����
    QDir dirSrc(sSrcPath);
    if (!dirSrc.exists())
        return;

    // ���ù����������ļ�����ʽ
    dirSrc.setFilter(QDir::Dirs|QDir::Files);
    dirSrc.setSorting(QDir::DirsLast);

    //��ȡ�ļ���Ϣ�б�
    QFileInfoList fileInfoList = dirSrc.entryInfoList();

    // ��Ϊ�գ��Ŵ����б�
    if (!fileInfoList.empty())
    {
        QDir().mkdir(sDestPath);
    }

    // ��������
    for (size_t i=0; i<fileInfoList.size(); i++)
    {
        QFileInfo fileInfo = fileInfoList.at(i);

        // ���������ļ�
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
    // ��ȡ�������
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



