#include "app.h"
#include "ui_app.h"

// BeatVault Application Constructor
App::App(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::App)
{
    ui->setupUi(this);
    //loadTextFile();
}

// BeatVault Application Constructor
App::~App()
{
    delete ui;
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
