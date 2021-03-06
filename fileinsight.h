// Header file for FileInsight: this declares variables, functions, modules to depend on,
// etc.
#ifndef FILEINSIGHT_H
#define FILEINSIGHT_H

#include <magic.h>
#include <iostream>
#include <cstring>
#include "fileinsightsubdialog.h"

#include <QWidget>
#include <QMainWindow>
#include <QFileDialog>
#include <QByteArray>
#include <QFileIconProvider>
#include <QProcess>
#include <QMimeDatabase>
#include <QMessageBox>
#include <QProcessEnvironment>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QUrl>
#include <QMimeData>
#include <QList>
#include <QDebug>

#ifdef Q_OS_WIN
#include <windows.h>
#include <QtWinExtras>
#endif

enum FileInsightBackend { BACKEND_MAGIC, BACKEND_TRID, BACKEND_QT, BACKEND_QT_FILEONLY};

namespace Ui {
class FileInsight;
}

class FileInsight : public QMainWindow
{
    Q_OBJECT

public:
    explicit FileInsight(QWidget *parent = 0);
    ~FileInsight();
    void chooseFile();
    FileInsightBackend getBackend();
    FileInsightSubdialog * getCurrentTab();
    QIcon getIcon(QString mimetype, QString filename);
    QString getMagicInfo(QString filename);
    QString getMimeType(QString filename);
    QString getTridInfo(QString filename);
    FileInsightSubdialog * newTab(bool starting = false);
    void openFile(QString filename, bool starting = true);
    const char * QStringToConstChar(QString text);

protected slots:
    void on_actionQuit_triggered();
    void on_selectFileButton_clicked();
    void on_actionSelect_triggered();
    void on_reloadButton_clicked();
    void on_tabWidget_tabCloseRequested(int index);
    void on_addTabButton_clicked();
    void on_actionAbout_triggered();
    void on_actionAbout_Qt_triggered();

private:
    Ui::FileInsight *ui;

protected:
    QProcess trid_subprocess;
    QString trid_command;
    magic_t magic_cookie;
    magic_t magic_cookie_mime;
    QFileIconProvider iconprovider;

    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);

    bool getMagicError(magic_t magic_cookie);
};

#endif // FILEINSIGHT_H
