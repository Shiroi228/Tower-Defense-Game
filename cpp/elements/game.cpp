#include <QAudioDecoder>
#include <QAudioOutput>
#include <QCoreApplication>
#include <QDebug>
#include <QImage>
#include <QTimer>

#include "bullet.hpp"
#include "game.hpp"
#include "enemy.hpp"

namespace elements {

static QSharedPointer<GameView> game_ = {};

QSharedPointer<GameView> GameView::instance() {
    if (game_) { return game_; }

    game_ = QSharedPointer<GameView>(new GameView);
    return game_;
}

GameView::GameView(QWidget *parent) : QGraphicsView(parent), scene_(new QGraphicsScene(this)), tower_(new TowerElement()),  mediaPlayer_(new QMediaPlayer(this)),
    audioOutput_(new QAudioOutput(this)), cursor_(nullptr), buildButton_(new BuildButton()) {
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(800, 600);
    setScene(scene_);
    setMouseTracking(true);
    // setBackgroundBrush(QBrush(QImage(":/images/background.jpg")));
    
    scene_->addItem(buildButton_);
    scene_->addItem(tower_);
    scene_->setSceneRect(0, 0, 800, 600);

    tower_->setPos(width() / 2 - tower_->boundingRect().width() / 2, height() / 2 - tower_->boundingRect().height() / 2);

    EnemyElement *enemy = new EnemyElement();
    scene_->addItem(enemy);

    // QTimer *timer = new QTimer();
    // connect(timer, &QTimer::timeout, player_, &PlayerElement::spawn);
    // timer->start(2000);

    mediaPlayer_->setAudioOutput(audioOutput_);
    // mediaPlayer_->setSource(QUrl("qrc:/sounds/background.mp3"));
    
    connect(mediaPlayer_, &QMediaPlayer::mediaStatusChanged, this, [=](QMediaPlayer::MediaStatus status){
        if (status == QMediaPlayer::EndOfMedia) {
            mediaPlayer_->setPosition(0);
            mediaPlayer_->play();
        }
    });
    connect(mediaPlayer_, &QMediaPlayer::errorOccurred, 
                this, &GameView::handleMediaError);

    loadAudioWithoutReplayGain();
}

GameView::~GameView() {
    if (mediaPlayer_) {
        mediaPlayer_->stop();
        mediaPlayer_->disconnect();
    }

    if (audioOutput_) {
        audioOutput_->disconnect();
    }

    delete mediaPlayer_;
    delete audioOutput_;

    QCoreApplication::processEvents();
}


void GameView::mousePressEvent(QMouseEvent *event) {
    if (tower_) {
        scene_->addItem(tower_);
        tower_->setPos(event->pos());
        cursor_ = nullptr;
        tower_ = nullptr;
    } else {
        QGraphicsView::mousePressEvent(event);
    }
}

void GameView::mouseMoveEvent(QMouseEvent *event) {
    if (cursor_) {
        cursor_->setPos(event->pos());
    }
}

TowerElement *GameView::tower() const {
    return tower_;
}

void GameView::setTower(TowerElement *tower) {
    tower_ = tower;
}

void GameView::handleMediaError(QMediaPlayer::Error error) {
    qDebug() << "Media Error:" << error << mediaPlayer_->errorString();
        
    if (error == QMediaPlayer::FormatError) {
        loadAudioAlternative();
    }
}

void GameView::loadAudioWithoutReplayGain() {
    QUrl url = QUrl("qrc:/sounds/VikiShow.mp3");
    url.setQuery("ffmpeg=replaygain=0");
    
    mediaPlayer_->setSource(url);
    mediaPlayer_->play();
}

void GameView::loadAudioAlternative() {
    QAudioDecoder *decoder = new QAudioDecoder(this);
    decoder->setSource(QUrl("qrc:/sounds/VikiShow.mp3"));
    
    connect(decoder, &QAudioDecoder::bufferReady, [this, decoder]() {
        QAudioBuffer buffer = decoder->read();
    });
    
    decoder->start();
}

void GameView::setCursor(const QString &filename) {
    if (cursor_) {
        scene_->removeItem(cursor_);
        delete cursor_;
    }

    QPixmap pixmap(filename);
    pixmap.scaled(10, 10);
    
    cursor_ = new QGraphicsPixmapItem();
    cursor_->setPixmap(pixmap);

    scene_->addItem(cursor_);
}

void GameView::addItem(QGraphicsItem *item) {
    scene_->addItem(item);
}

}