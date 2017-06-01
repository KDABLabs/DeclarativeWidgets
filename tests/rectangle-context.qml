import QtQuick 2.0

Rectangle {
    anchors.fill: parent
    color: _colour

    Component.onCompleted: {
        console.log("_colour is", _colour)
    }
}
