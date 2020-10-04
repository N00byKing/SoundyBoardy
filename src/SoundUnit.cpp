#include "SoundUnit.hpp"

#include <QFileInfo>
#include <QUrl>

SoundUnit::SoundUnit(QObject *parent, int pKeycode, QSoundEffect* se) {

    if (se != nullptr) {
        sound = se;
        QObject::connect(sound, SIGNAL(playingChanged()), this, SLOT(soundHandler()));
    }
    

    QWidget* wparent = (QWidget*)parent;
    f.setParent(wparent);
    f.setFrameStyle(QFrame::Shape::Panel | QFrame::Shadow::Plain);
    f.setMidLineWidth(10);
    f.resize(600,55);

    setButton.setParent(&f);
    setButton.setText("Select Sound");
    setButton.setGeometry(5, 5, 150, 25);
    setButton.show();
    QObject::connect(&setButton, SIGNAL(clicked()), this, SLOT(selectHandler()));

    playButton.setParent(&f);
    playButton.setText("Play");
    playButton.setGeometry(160, 5, 100, 25);
    playButton.setVisible(false);
    QObject::connect(&playButton, SIGNAL(clicked()), this, SLOT(playHandler()));

    fileLabel.setParent(&f);
    fileLabel.setText("No Sound Selected");
    fileLabel.setGeometry(10, 30, 570, 20);
    fileLabel.show();
    f.show();

    keycode = pKeycode;    
}

void SoundUnit::setKeycode(int pKeycode) {
    keycode = pKeycode;
}

void SoundUnit::show() {
    f.show();
}

void SoundUnit::setGeometry(int xLoc, int yLoc, int xSize, int ySize) {
    f.setGeometry(xLoc, yLoc, xSize, ySize);
}

void SoundUnit::setParent(QWidget *parent) {
    QWidget* wparent = (QWidget*)parent;
    f.setParent(wparent);
}

void SoundUnit::selectHandler() {
    filePath = QFileDialog::getOpenFileName(this, "Open Sound", "/home", "WAVE Files (*.wav)");
    if(!filePath.isEmpty() && !filePath.isNull()){
        fileLabel.setText(QFileInfo(filePath).fileName());
        playButton.show();
    } else {
        playButton.setVisible(false);
        fileLabel.setText("No Sound Selected");
    }   
}

void SoundUnit::playHandler() {
    if(!filePath.isEmpty() && !filePath.isNull()){
        sound->setSource(QUrl::fromUserInput(filePath));
        sound->play();
    }
}

void SoundUnit::play() {
    playHandler();
}

int SoundUnit::getKeyCode() {
    return keycode;
}

void SoundUnit::setSoundObject(QSoundEffect* se) {
    sound = se;
}