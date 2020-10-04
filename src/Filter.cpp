#include <QX11Info>

#include "Filter.hpp"

#include <xcb/xcb.h>
#include <X11/keysym.h>
#include <X11/Xlib.h>

bool Filter::nativeEventFilter(const QByteArray &eventType, void *message, long *result) {
    if (eventType == "xcb_generic_event_t") {
        xcb_generic_event_t* event = static_cast<xcb_generic_event_t *>(message);
        if ((event->response_type) == XCB_KEY_RELEASE) {
            xcb_key_press_event_t * keypress_event = static_cast<xcb_key_press_event_t *>(message);
            for (int i = 0; i < 4; i++) {
                if (keypress_event->detail == (*units)[i].getKeyCode()) {
                    (*units)[i].play();
                }
            }
        }
    }
    return false;
}

Filter::Filter(SoundUnit (*pUnits)[4]) {
    Display* display = QX11Info::display();

    units = pUnits;

    int keycode;
    for (int i = 0; i < 4; i++) {
        keycode = XKeysymToKeycode(display, XK_KP_1 + i);
        (*units)[i].setKeycode(keycode);
        XGrabKey(display, keycode, AnyModifier, DefaultRootWindow(display), 1, GrabModeAsync, GrabModeAsync);
    }
}