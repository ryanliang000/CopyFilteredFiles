#ifndef GETCPPSRCFILES_H
#define GETCPPSRCFILES_H

#include <QtWidgets/QMainWindow>
#include "ui_getcppsrcfiles.h"


class GetCppSrcFiles : public QMainWindow
{
    Q_OBJECT

public:
    GetCppSrcFiles(QWidget *parent = 0);
    ~GetCppSrcFiles();

public slots:
    void onProcessFiles();
    void onSelectSrc();
    void onSelectDest();
    void onOption();
private:
    Ui::GetCppSrcFilesClass ui;

};

#endif // GETCPPSRCFILES_H
