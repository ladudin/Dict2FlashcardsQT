#include "ISentencePluginWrapper.h"
#include "SentencePluginWrapper.h"
#include "mainwindow.h"

#include <QApplication>
#include <memory>
#include "SentencesWidget.hpp"
#include "ServerConnection.h"
#include "Card.h"
#include "spdlog/spdlog.h"
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
    SPDLOG_DEBUG("hello");
    auto connection = std::make_shared<ServerConnection>(8888);
    std::unique_ptr<ISentencePluginWrapper> sentencePlugin = std::make_unique<SentencePluginWrapper>(connection);
    SentencesWidget wgt(std::move(sentencePlugin));
    wgt.show();
    app.exec();
    return 0;
}
