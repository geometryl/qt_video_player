#include "mediaplayer.h"
#include "ui_mediaplayer.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QTimer>
#include <QVBoxLayout>

MediaPlayer::MediaPlayer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MediaPlayer),
    player(new QMediaPlayer),
    playlist(new QMediaPlaylist),
    widget(new QVideoWidget),
    timer(new QTimer),
    playState(QMediaPlayer::StoppedState)
{
    ui->setupUi(this);

    QVBoxLayout* layout_video = new QVBoxLayout;
    layout_video->setMargin(1);
    widget->resize(ui->label->size());
    layout_video->addWidget(widget);
    ui->label->setLayout(layout_video);

    player->setPlaylist(playlist);
    player->setVideoOutput(widget);

    timer->setInterval(1000);
    connect(timer,SIGNAL(timeout()),this,SLOT(onTimerOut()));
}

MediaPlayer::~MediaPlayer()
{
    timer->stop();
    player->stop();
    delete widget;
    delete playlist;
    delete player;

    delete ui;
}


void MediaPlayer::on_pushButton_open_clicked()
{
    //video file
    QString filename = QFileDialog::getOpenFileName(this,tr("open file"),".",tr("(*.avi *.mp4 *.flv *.mkv) | (*.*)"));
    QFileInfo fileInfo(filename);
    QUrl url = QUrl::fromLocalFile(fileInfo.absoluteFilePath());
    if (fileInfo.exists()) {
        if (fileInfo.suffix().toLower() == QLatin1String("m3u")) {
            playlist->load(url);
        } else {
            playlist->addMedia(url);
        }
    } else {
        QUrl url(filename);
        if (url.isValid()) {
            playlist->addMedia(url);
        }
    }
}

void MediaPlayer::on_pushButton_play_clicked()
{
    //start to play
    playState = QMediaPlayer::PlayingState;
    player->play();
    timer->start();
}

void MediaPlayer::on_pushButton_pause_clicked() {
    playState = QMediaPlayer::PausedState;
    player->pause();
}

void MediaPlayer::on_pushButton_stop_clicked() {
    playState = QMediaPlayer::StoppedState;
    player->stop();
    timer->stop();
}

void MediaPlayer::onTimerOut()
{
    if (QMediaPlayer::PlayingState == playState) {
        ui->horizontalSlider_progress->setValue(player->position()*1000/player->duration());
    }
}
