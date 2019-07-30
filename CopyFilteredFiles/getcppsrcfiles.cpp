#include "getcppsrcfiles.h"
#include "waitdlg.h"

GetCppSrcFiles::GetCppSrcFiles(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    connect(ui.btnProc, SIGNAL(pressed()), SLOT(onProcessFiles()));
    connect(ui.btnCancel, SIGNAL(pressed()), SLOT(close()));
    connect(ui.btnSelectSrc, SIGNAL(pressed()), SLOT(onSelectSrc()));
    connect(ui.btnSelectDest, SIGNAL(pressed()), SLOT(onSelectDest()));

    ui.editSrcPath->setText("");
    ui.editDestPath->setText(""); 
	ui.editFileTails->setText("h;cpp;vcxproj;sln;bat;filters;proj;ui;qrc;res;ts;hpp;lib;dll;py");
}

GetCppSrcFiles::~GetCppSrcFiles()
{

}

#include "CopyTask.h"
void GetCppSrcFiles::onProcessFiles()
{
    QString sSrcPath = ui.editSrcPath->text();
    QString sDestPath = ui.editDestPath->text();
    QString sFileTails = ui.editFileTails->text();

    if (sSrcPath.isEmpty() || sDestPath.isEmpty())
    {
        return;
    }

    // 目录打开并检查
    QDir dirSrc(sSrcPath);
    if (!dirSrc.exists())
        return;

    // 目录打开并检查
    QDir dirDest(sDestPath);
    if (!dirDest.exists())
    {
        if (!dirDest.mkdir(sDestPath))
        {
            qDebug("open dest foder error!");
            return;
        }
    }
    
    // 显示处理等待WaitDlg & 禁用按钮
    WaitDlg dlg(this);
    dlg.show();
    ui.btnProc->setEnabled(false);

    // 启动线程处理并等待处理完成
    MyThreadWaitTask task;
    MyCopyThread* pThread = new MyCopyThread(this, &task, sSrcPath, sDestPath, sFileTails);
    pThread->start();
    task.waitTaskFinish();

    // 处理完成隐藏WaitDlg并启用按钮
    dlg.hide();
    ui.btnProc->setEnabled(true);
    
    // 弹出提示处理完成
    QMessageBox::information(this, "Info", "Pcoess finished!", QMessageBox::Ok);
}


void GetCppSrcFiles::onSelectSrc()
{
    QString sFileName = QFileDialog::getExistingDirectory(this, tr("Open Directory"));
    if (!sFileName.isEmpty())
    {
        ui.editSrcPath->setText(sFileName);
    }
}

void GetCppSrcFiles::onSelectDest()
{
    QString sFileName = QFileDialog::getExistingDirectory(this, tr("Open Directory"));
    if (!sFileName.isEmpty())
    {
        ui.editDestPath->setText(sFileName);
    }
}

void GetCppSrcFiles::onOption()
{

}


