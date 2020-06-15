import QtQuick 2.12
import QtQuick.Window 2.12
import Openthinks.Graph 1.0

Window {
    id: root
    visible: true
    width: 640
    height: 480
    title: qsTr("QML C++ Plugin Sample")

    Rectangle{
        width:600
        height:400
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        color: "#2a2a2a"
        GraphChart{
            id:graphChart
            anchors.fill: parent
            lineColor:"#ff0000"            
        }
    }

    Component.onCompleted: {
        graphChart.startEventTimer()
    }
}
