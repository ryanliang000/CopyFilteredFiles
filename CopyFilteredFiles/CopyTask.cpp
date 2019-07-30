#include "CopyTask.h"
const static bool gs_bIsDeleteEmptyDir = true;
int CopyDirsEx(QString sSrcPath, QString sDestPath, QStringList& listFileTails)
{
	int nProcessFiles = 0;
    // Ŀ¼�򿪲����
    QDir dirSrc(sSrcPath);
    if (!dirSrc.exists())
        return nProcessFiles;

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
			nProcessFiles += CopyDirsEx(sSrcPath + "\\" + fileInfo.fileName(), sDestPath + "\\" + fileInfo.fileName(), listFileTails);
        }
        else
        {
            if (listFileTails.contains(fileInfo.suffix()))
            {
                bool bRt = QFile::copy(sSrcPath  + "\\" + fileInfo.fileName(), sDestPath +  "\\" + fileInfo.fileName());
				nProcessFiles++;
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
	if (gs_bIsDeleteEmptyDir && nProcessFiles == 0)
		QDir().rmdir(sDestPath);

	return nProcessFiles;
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



