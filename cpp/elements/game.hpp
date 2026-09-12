#ifndef GAME_H
#define GAME_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMediaPlayer>
#include <QMouseEvent>
#include <QSharedPointer>

namespace elements {

class GameView : public QGraphicsView {
public:
    GameView(QWidget *parent = nullptr);
    ~GameView();

    static QSharedPointer<GameView> instance();

    void mousePressEvent(QMouseEvent *event) override;

private slots:
    void handleMediaError(QMediaPlayer::Error error);

private:
    void loadAudioWithoutReplayGain();
    void loadAudioAlternative();

private:
    QGraphicsScene *scene_;

    QMediaPlayer *mediaPlayer_;
    QAudioOutput *audioOutput_;
};

}

#endif // GAME_H
