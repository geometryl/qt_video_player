#ifndef MEDIAPLAYER_H
#define MEDIAPLAYER_H

#include <QWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QVideoWidget>

namespace Ui {
class MediaPlayer;
}

class MediaPlayer : public QWidget
{
    Q_OBJECT

public:
    explicit MediaPlayer(QWidget *parent = 0);
    ~MediaPlayer();

private slots:
    void on_pushButton_open_clicked();
    void on_pushButton_play_clicked();
    void on_pushButton_pause_clicked();
    void on_pushButton_stop_clicked();
    void onTimerOut();

private:
    Ui::MediaPlayer *ui;
    QMediaPlayer *player;
    QMediaPlaylist *playlist;
    QVideoWidget *widget;
    QTimer *timer;

    QMediaPlayer::State playState;
};

#endif // MEDIAPLAYER_H
