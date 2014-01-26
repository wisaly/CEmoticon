HEADERS   += qxt\qxtglobal.h \
             qxt\qxtglobalshortcut.h \
             qxt\qxtglobalshortcut_p.h

SOURCES   += qxt\qxtglobal.cpp \
             qxt\qxtglobalshortcut.cpp

win32 {
  SOURCES += qxt\qxtglobalshortcut_win.cpp
} else:macx {
  SOURCES += qxt\qxtglobalshortcut_mac.cpp
} else:haiku {
  SOURCES += qxt\qxtglobalshortcut_haiku.cpp
} else {
  SOURCES += qxt\qxtglobalshortcut_x11.cpp
}
