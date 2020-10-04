#include <QApplication>
#include <QMainWindow>
#include <QSoundEffect>
#include <QPushButton>
#include <QAudioDeviceInfo>
#include <QMessageBox>

#include "SoundUnit.hpp"
#include "Filter.hpp"

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    QMainWindow w;
    QSoundEffect* se;
    
    const QAudioDeviceInfo* faout = nullptr;
    
    const auto deviceInfos = QAudioDeviceInfo::availableDevices(QAudio::AudioOutput);
    for (const QAudioDeviceInfo &deviceInfo : deviceInfos) {
        if (deviceInfo.deviceName().contains("FAout")) {
            faout = &deviceInfo;
            break;
        }
    }
    if (faout == nullptr) {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Did not find the required Audio Output. Did you run pulse_setup.sh? Automatic Output change disabled.");
        messageBox.setFixedSize(500,200);
        se = new QSoundEffect();
    } else {
        se = new QSoundEffect(*faout);
    }

    QPushButton stopButton("Stop Playback", &w);
    stopButton.setGeometry(620, 10, 100, 55);
    stopButton.setVisible(false);
    QObject::connect(&stopButton, &QPushButton::clicked, [&]{ (*se).stop();});

    QObject::connect(se, &QSoundEffect::playingChanged, [&]{
                                                            if (se->isPlaying()) {
                                                                stopButton.setVisible(true);
                                                            } else {
                                                                stopButton.setVisible(false);
                                                            }});

    w.resize(820, 285);
    w.show();
    
    SoundUnit su[4];
    QApplication::instance()->installNativeEventFilter(new Filter(&su));
    for (int i = 0; i < 4; i++) {
        su[i].setParent(&w);
        su[i].setSoundObject(se);
        su[i].setGeometry(10, 10+i*70, 600, 55);
        su[i].show();
    }

    return app.exec();
}