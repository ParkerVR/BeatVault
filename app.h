#ifndef APP_H
#define APP_H

#include <QMainWindow>
#include <QDir>
#include <QListWidget>

#include <QFile>
#include <QTextStream>
#include <QString>

#include <QFileDialog>
#include <QPixmap>
#include <QStringList>

#include <QSettings>

#include <QCloseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class App; }
QT_END_NAMESPACE

class App : public QMainWindow
{
    Q_OBJECT

public:
    App(QWidget *parent = nullptr);
    ~App();

private slots:

    void closeEvent(QCloseEvent *event);

    void on_pathButton_clicked();

    void on_songList_itemActivated(QListWidgetItem *item);    

private:
    Ui::App *ui;

    QString beat_path;
    QString customSongs_path;

    void loadTextFile(QString);

    QString settingsFile;
    void readSettings();
    void writeSettings();
};
#endif // APP_H
