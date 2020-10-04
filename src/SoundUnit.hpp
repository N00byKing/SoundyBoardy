#pragma once

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QFrame>
#include <QFileDialog>
#include <QSoundEffect>

class SoundUnit : public QWidget {
    Q_OBJECT
    public:
        SoundUnit(QObject *parent = 0, int pKeycode = 0, QSoundEffect* se = nullptr);

        void show();
        void setGeometry(int,int,int,int);
        void setParent(QWidget *parent);

        void play();

        void setKeycode(int);
        int getKeyCode();

        void setSoundObject(QSoundEffect* se);

    private:
        QFrame f;
        QPushButton setButton;
        QPushButton playButton;
        QLabel fileLabel;
        QFileDialog fileDialog;
        QString filePath;

        QSoundEffect* sound;

        int keycode;

    private slots:
        void selectHandler();
        void playHandler();
};
