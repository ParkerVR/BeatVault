#include "app.h"
#include "ui_app.h"

App::App(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::App)
{

    ui->setupUi(this);
    App::readSettings();


    //App::settingsFile = QApplication::applicationDirPath().left(1) + ":/demosettings.ini";
    if (App::customSongs_path != "") {
        QStringList entries = QDir(App::customSongs_path).entryList();
        ui->songList->addItems(entries);
    }
    //loadTextFile();
}

App::~App()
{
    delete ui;
}


void App::closeEvent(QCloseEvent *event)
{

    writeSettings();
    event->accept();

}

// This is the slot for selecting a BeatSaber Directory
void App::on_pathButton_clicked()
{
    App::beat_path = QFileDialog::getExistingDirectory(this, tr("Select Beat Saber Directory"),
                                                 "/",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);

    App::customSongs_path = App::beat_path + "/Beat Saber_Data/CustomLevels/";

    QStringList entries = QDir(customSongs_path).entryList();

    ui->songList->addItems(entries);
    App::writeSettings();
}

// Selecting a song from the list will load it's data
void App::on_songList_itemActivated(QListWidgetItem *item)
{

    QString meta_path = App::customSongs_path + item->text() + "/info.dat";
    QString img_path = App::customSongs_path + item->text() + "/cover.jpg";

    loadTextFile(meta_path);
    QPixmap coverPix;
    if (coverPix.load(img_path)){
        coverPix = coverPix.scaled(ui->coverLabel->size(), Qt::KeepAspectRatio);
        ui->coverLabel->setPixmap(coverPix);
    }
}

void App::readSettings()
{
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "Instantaneous Solutions", "BeatVault");

    settings.beginGroup("Paths");
    App::beat_path = settings.value("beat_path").toString();
    App::customSongs_path = settings.value("customSongs_path").toString();
    settings.endGroup();
}

void App::writeSettings()
{
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "Instantaneous Solutions", "BeatVault");

    settings.beginGroup("Paths");
    settings.setValue("beat_path", App::beat_path);
    settings.setValue("customSongs_path", App::customSongs_path);
    settings.endGroup();
}

// A simple text file load to a window
void App::loadTextFile(QString path)
{
    QFile inputFile(path);
    inputFile.open(QIODevice::ReadOnly);

    QTextStream in(&inputFile);
    QString line = in.readAll();
    inputFile.close();

    ui->textEdit->setPlainText(line);
    QTextCursor cursor = ui->textEdit->textCursor();
    cursor.movePosition(QTextCursor::Start, QTextCursor::MoveAnchor, 1);
}
