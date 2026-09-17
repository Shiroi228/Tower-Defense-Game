#ifndef GAME_H
#define GAME_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMediaPlayer>
#include <QMouseEvent>
#include <QSharedPointer>
#include <QGraphicsPixmapItem>

#include "tower.hpp"
#include "toolbar.hpp"

namespace elements {

class GameView : public QGraphicsView {
    Q_OBJECT
public:
    GameView(QWidget *parent = nullptr);
    ~GameView();

    void setCursor(const QString &filename);
    void addItem(QGraphicsItem *item);

    static QSharedPointer<GameView> instance();

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

    TowerElement *tower() const;
    void setTower(TowerElement *tower);

private slots:
    void handleMediaError(QMediaPlayer::Error error);

private:
    void loadAudioWithoutReplayGain();
    void loadAudioAlternative();

private:
    QGraphicsScene *scene_;
    TowerElement *tower_;

    QMediaPlayer *mediaPlayer_;
    QAudioOutput *audioOutput_;
    QGraphicsPixmapItem *cursor_;

    BuildButton *buildButton_;
};

}

#endif // GAME_H
