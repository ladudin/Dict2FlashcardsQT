#include "IImagePluginWrapper.h"
#include "ISentencePluginWrapper.h"
#include "Media.h"
#include "SentencePluginWrapper.h"
#include "AudioPluginWrapper.h"
#include "mainwindow.h"
#include "ImagePluginWrapper.h"
#include <QApplication>
#include <iostream>
#include <memory>
#include "SentencesWidget.hpp"
#include "AudiosWidget.hpp"
#include "ImagesWWidget.hpp"
#include "ServerConnection.h"
#include "Card.h"
#include "spdlog/spdlog.h"
#include "Player.hpp"
#include <QMediaPlayer>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <qmediacontent.h>
#include <qmediaplayer.h>
#include <thread>
#include <chrono>
#include <thread>
#include <QBuffer>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // SourceWithAdditionalInfo source1;
    // source1.info = "Test audio";
    // source1.src = "http://music.arizona-rp.com/rodina/1682374558.mp3";

    // SourceWithAdditionalInfo source2;
    // source2.info = "Test audio";
    // source2.src = "http://music.arizona-rp.com/rodina/1682288834.mp3";

    // SourceWithAdditionalInfo source3;
    // source3.info = "Test audio";
    // source3.src = "http://music.arizona-rp.com/rodina/1682374575.mp3";

    // auto connection = std::make_shared<ServerConnection>(8888);
    // std::unique_ptr<IAudioPluginWrapper> audioPlugin = std::make_unique<AudioPluginWrapper>(connection);
    // AudiosWidget wgt(std::move(audioPlugin));
    // wgt.addAudio(source1, false, false);
    // wgt.addAudio(source2, false, false);
    // wgt.addAudio(source3, false, false);
    // wgt.show();

    SourceWithAdditionalInfo source1;
    source1.info = "Test audio";
    source1.src = "https://mobimg.b-cdn.net/v3/fetch/ae/ae3617367cfef8ee5cba5db54cde1360.jpeg?w=1470&r=0.5625";

    SourceWithAdditionalInfo source2;
    source2.info = "Test audio";
    source2.src = "https://i.pinimg.com/originals/d3/0f/c8/d30fc877ade673509416fa5fe9917f71.jpg";

    SourceWithAdditionalInfo source3;
    source3.info = "Test audio";
    source3.src = "https://w-dog.ru/wallpapers/11/0/500831153565704/priroda-pejzazh-prosmotret-nebo-zakat-pole-derevya-oblaka-vid-krasivyj-doroga.jpg";

    auto connection = std::make_shared<ServerConnection>(8888);
    std::unique_ptr<IImagePluginWrapper> imagePlugin = std::make_unique<ImagePluginWrapper>(connection);
    ImagesWidget wgt(std::move(imagePlugin));
    wgt.addImage(source1, false);
    wgt.addImage(source2, false);
    wgt.addImage(source3, false);
    wgt.show();
    app.exec();
    return 0;
}
