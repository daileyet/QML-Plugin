import QtQuick 2.0

FocusScope {
    id: control

    property ListModel comboxMode:defaultModel
    property string textRole: "name"
    property Component comboxDelegate:defaultDelegate
    property alias comboxValueText: comboxValue.text
    property alias comboxValueFontpixelSize: comboxValue.font.pixelSize
    property color bgColor: "#323232"
    property color selectedColor: "#8e8e8e"
    property color pressedColor: "#666666"
    property color textColor: "#cccccc"
    property int selectedIndex: 0

    implicitHeight: 47
    implicitWidth: 300
    state: "normal"
    Rectangle{
        color: bgColor
        anchors.fill: parent
    }

    FocusScope{
        anchors.rightMargin: 1
        anchors.leftMargin: 1
        anchors.bottomMargin: 1
        anchors.topMargin: 1
        anchors.fill: parent
        Rectangle{
            anchors.fill: parent
            color: "#2a2a2a"
        }
        Text{
            id:comboxValue
            color: textColor
            font.pixelSize: 20
            verticalAlignment: Text.AlignVCenter
            anchors.right: parent.right
            anchors.rightMargin: 60
            anchors.left: parent.left
            anchors.leftMargin: 9
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            elide: Text.ElideRight
        }
        Item{
            height: parent.height
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: comboxValue.right
            anchors.leftMargin: 0
            Image {
                id: comboxArrowIcon
                width: 22
                height: 15
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                source: "combox_arrow.png"
                fillMode: Image.PreserveAspectFit
            }

        }
    }
    MouseArea{
        id:valueMouseArea
        anchors.fill: parent
        enabled: true
        hoverEnabled: true
        onClicked: {
            control.state= (control.state=="normal")?"dropdown":"normal";
        }

    }
    states: [
        State {
            name: "normal"
        },
        State {
            name: "dropdown"
        }
    ]

    ListModel{
        id:defaultModel
        ListElement {
            name: "name"
        }
    }

    Component{
        id:defaultDelegate
        Rectangle{
            height: control.height
            width: control.width
            color: bgColor
            Rectangle{
                id:rectElementBg
                anchors.fill: parent
                color: (index === selectedIndex)?selectedColor:
                                                  elementMouseArea.pressed ? pressedColor:"transparent"
            }
            Text{
                id: element
                text:model[textRole]
                height: parent.height
                anchors.left: parent.left
                anchors.leftMargin: 10
                anchors.right: parent.right
                anchors.rightMargin: 10
                verticalAlignment: Text.AlignVCenter
                color: textColor
                font.pixelSize: comboxValueFontpixelSize
                elide: Text.ElideRight
            }
            MouseArea{
                id:elementMouseArea
                anchors.fill: parent
                onClicked: {
                    selectedIndex=index;
                    control.state="normal"
                }
            }
        }
    }


    Item{
        id:popupPanel
        y: control.height
        width: control.width
        height: control.height
        visible: control.state=="dropdown"
        Rectangle{
            anchors.fill: parent
            color: bgColor
        }
        ListView{
            id:comboxListview
            anchors.fill: parent
            model: comboxMode
            delegate: comboxDelegate
        }

    }

    Component.onCompleted: {
        if(comboxMode.count>0){
            popupPanel.height = comboxMode.count*control.height
        }
        selectItem(selectedIndex)
    }

    onSelectedIndexChanged: {
        comboxListview.currentIndex=selectedIndex;
        selectItem(selectedIndex)
    }

    function selectItem(index){
        var size = comboxMode.count;
        if(size>0 && index>=0 && index<size ){
            comboxValueText=comboxMode.get(index)[textRole]
        }
    }
}
