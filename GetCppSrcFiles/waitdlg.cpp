#include "waitdlg.h"

WaitDlg::WaitDlg(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    m_pMovie = new QMovie(this);
    m_pMovie->setFileName("Process.gif");
    ui.m_labelShow->setMovie(m_pMovie);
    m_pMovie->setScaledSize(QSize(100, 100));
    m_pMovie->start();

}

WaitDlg::~WaitDlg()
{

}
