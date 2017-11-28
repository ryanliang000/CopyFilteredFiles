#ifndef WAITDLG_H
#define WAITDLG_H

#include <QWidget>
#include "ui_waitdlg.h"
#include "qmovie.h"

class WaitDlg : public QWidget
{
    Q_OBJECT

public:
    WaitDlg(QWidget *parent = 0);
    ~WaitDlg();

private:
    Ui::WaitDlg ui;
    QMovie* m_pMovie;
};

#endif // WAITDLG_H
