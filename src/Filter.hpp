#pragma once

#include <QAbstractNativeEventFilter>

#include "SoundUnit.hpp"

class Filter : public QAbstractNativeEventFilter {
    public:
        Filter(SoundUnit (*pUnits)[4]);
        bool nativeEventFilter(const QByteArray &eventType, void *message, long *result) Q_DECL_OVERRIDE;

    private:
        SoundUnit (*units)[4];
};
