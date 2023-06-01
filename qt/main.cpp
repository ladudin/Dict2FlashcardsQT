#include "ISentencePluginWrapper.h"
#include "Media.h"
#include "SentencePluginWrapper.h"
#include "mainwindow.h"

#include <QApplication>
#include <iostream>
#include <memory>
#include "SentencesWidget.hpp"
#include "AudiosWidget.hpp"
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
// #include <QPushButton>
// #include <QLabel>
// #include <QPixmap>
// #include <QTableWidget>
// #include <ImagesWidget.hpp>
// #include <memory>
// #include <qapplication.h>
// #include "AudioPlayer.hpp"
// #include "Media.hpp"
// #include "AudioWidget.hpp"
// #include "ExamplesWidget.hpp"
// #include "test.h"

// int main(int argc, char *argv[])
// {
//     QApplication a(argc, argv);
// //    SourceWithAdditionalInfo audio;
// //    audio.info = "That's a test audio\nPlease, work";
// //    audio.src = "/home/vlad/test.mp3";
// //    AudioPlayer audioPlayer;
// //    audioPlayer.set(audio, true);
// //    audioPlayer.set(audio, true);
// //    audioPlayer.resize(320, 75);
// //    audioPlayer.show();
// //    AudioWidget* wgt = new AudioWidget;
// //    Media media;
// //    for (int i = 0; i < 3; ++i) {
// //        SourceWithAdditionalInfo info;
// //        info.src = "https://samplelib.com/lib/preview/mp3/sample-15s.mp3";
// //        media.web.push_back(std::move(info));
// //    }
// //    wgt->set(media);
// //    wgt->show();
// //    test t;
// //    t.show();
// //    Media media;
// //    for (int i = 0; i < 6; ++i) {
// //        SourceWithAdditionalInfo info;
// //        info.src = "https://i.ytimg.com/vi/Ux5cQbO_ybw/maxresdefault.jpg?9289889566";
// //        media.web.push_back(std::move(info));
// //    }
// //    IMagesWidget imagesWidget;
// //    imagesWidget.set(media);
// //    imagesWidget.show();
//     ExamplesWidget wgt;
//     std::vector<std::string> vec = {"hello", "bye", "dog", "yes", "gg", "vp", "nice"};
//     wgt.set(&vec);
//     wgt.show();
//     return a.exec();
// }

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
//    MainWindow window;
//    window.show();
//    // window.resize(800, 400);
    // auto [cards, error] = load_cards("/home/vlad/park/cpp/Dict2FlashcardsQT/build/qt/savedDeck.json");
    // qDebug() << "Cards loaded: " << cards.size() << "with message" << QString::fromStdString(error);
    // SPDLOG_DEBUG("hello");
    // auto connection = std::make_shared<ServerConnection>(8888);
    // std::unique_ptr<ISentencePluginWrapper> sentencePlugin = std::make_unique<SentencePluginWrapper>(connection);
    // SentencesWidget wgt(std::move(sentencePlugin));
    // wgt.show();

    SourceWithAdditionalInfo source1;
    source1.info = "Test audio";
    source1.src = "http://music.arizona-rp.com/rodina/1682374558.mp3";

    SourceWithAdditionalInfo source2;
    source2.info = "Test audio";
    source2.src = "http://music.arizona-rp.com/rodina/1682288834.mp3";

    SourceWithAdditionalInfo source3;
    source3.info = "Test audio";
    source3.src = "http://music.arizona-rp.com/rodina/1682374575.mp3";

    AudiosWidget wgt;
    wgt.addAudio(source1, false, false);
    wgt.addAudio(source2, false, false);
    wgt.addAudio(source3, false, false);
    wgt.show();
    // QNetworkAccessManager manager;
    // QNetworkReply* reply = manager.get(QNetworkRequest(QUrl("https://www.1zoom.ru/big2/541/255095-Sepik.jpg")));

    // std::this_thread::sleep_for(std::chrono::seconds(10));
    // QByteArray bytes = reply->readAll();
    // std::cout << bytes.length() << " " << bytes.size() << std::endl;
    // QBuffer buffer(&bytes);
    // delete reply;
    // Player player;
    // player.download(QUrl("https://www.1zoom.ru/big2/541/255095-Sepik.jpg"));
    // std::this_thread::sleep_for(std::chrono::seconds(10));
    app.exec();
    return 0;
}
