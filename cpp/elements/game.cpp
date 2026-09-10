#include <QAudioDecoder>
#include <QAudioOutput>
#include <QCoreApplication>
#include <QDebug>
#include <QImage>
#include <QTimer>

#include "game.hpp"
#include "tower.hpp"

namespace elements {

static QSharedPointer<GameView> game_ = {};

QSharedPointer<GameView> GameView::instance() {
    if (game_) { return game_; }

    game_ = QSharedPointer<GameView>(new GameView);
    return game_;
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

GameView::GameView(QWidget *parent) : QGraphicsView(parent), scene_(new QGraphicsScene(this)), mediaPlayer_(new QMediaPlayer(this)),
    audioOutput_(new QAudioOutput(this)) {
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(800, 600);
    setScene(scene_);
    // setBackgroundBrush(QBrush(QImage(":/images/background.jpg")));
    
    TowerElement *tower = new TowerElement();
    
    scene_->addItem(tower);
    scene_->setSceneRect(0, 0, 800, 600);

    tower->setPos(width() / 2 - tower->boundingRect().width() / 2, height() / 2 - tower->boundingRect().height() / 2);

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

}