include("$$PWD/../auto.pri")

qtHaveModule(webenginewidgets) {
    QT += webenginewidgets
}

SOURCES +=  tst_instantiatetypes.cpp

RESOURCES += \
    qml.qrc
