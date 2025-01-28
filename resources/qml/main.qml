import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Basic
import QtQuick.Layouts

import Helpers 1.0

ApplicationWindow {
    id: root

    property string message: transferDataHandler ? transferDataHandler.transferData : ""
    property string messageHex: transferDataHandler ? transferDataHandler.transferDataHex : ""

    width: 500
    height: 600
    minimumWidth: 500
    visible: true
    color: Colors.backgroundSurface1
    title: qsTr("RobotechTestTask")

    AppTheme {
        id: appTheme
    }

    header: Rectangle {
        width: parent.width
        height: 40
        color: Colors.backgroundSurface2

        Column {
            anchors.fill: parent

            RowLayout {
                width: parent.width

                Text {
                    leftPadding: 16
                    text: qsTr("Server")
                    font: Constants.heading1
                    color: Colors.textPrimary
                }

                Item {
                    Layout.fillWidth: true
                }

                ToolButton {
                    id: pinger
                    icon.source: "qrc:/img/notconnected.svg"
                    icon.color: pressed ? Colors.iconSecondary : Colors.iconBasic
                    background: Rectangle {
                        color: pinger.pressed ? Colors.iconFillPressed :
                                                pinger.hovered ? Colors.iconFillHover :
                                                                 Colors.transparent
                    }

                    Layout.minimumWidth: 40
                    Layout.minimumHeight: 40

                    onClicked: drawerPinger.open()
                }

                ToolButton {
                    id: notification
                    icon.source: "qrc:/img/settings.svg"
                    icon.color: pressed ? Colors.iconSecondary : Colors.iconBasic
                    background: Rectangle {
                        color: notification.pressed ? Colors.iconFillPressed :
                                                      notification.hovered ? Colors.iconFillHover :
                                                                             Colors.transparent
                    }

                    Layout.minimumWidth: 40
                    Layout.minimumHeight: 40

                    onClicked: drawerSettings.open()
                }
            }

            Separator { orientation: Qt.Horizontal }
        }
    }

    DrawerSettings {
        id: drawerSettings
    }

    DrawerPinger {
        id: drawerPinger
    }

    Column {
        anchors.fill: parent
        anchors.margins: 8
        spacing: 8

        Text {
            topPadding: 16
            text: qsTr("Incoming data:")
            font: Constants.heading2
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            color: Colors.textPrimary
        }

        Rectangle {
            width: parent.width
            height: root.height * 0.2

            ScrollView {
                anchors.fill: parent
                TextArea {
                    text: message
                    color: Colors.textSecondary
                    font: Constants.textArea
                    readOnly: true
                    wrapMode: TextEdit.WordWrap
                    background: Rectangle {
                        color: Colors.backgroundTextArea
                        border.color: Colors.strokePrimary
                    }
                }
            }
        }

        Text {
            topPadding: 16
            text: qsTr("Incoming hex-data:")
            color: Colors.textSecondary
            font: Constants.heading2

            // horizontalAlignment: Text.AlignHCenter
            // verticalAlignment: Text.AlignVCenter

        }

        Rectangle {
            width: parent.width
            height: root.height * 0.2

            ScrollView {
                anchors.fill: parent
                TextArea {
                    text: messageHex
                    color: Colors.textSecondary
                    font: Constants.textArea
                    readOnly: true
                    wrapMode: TextEdit.WordWrap
                    background: Rectangle {
                        color: Colors.backgroundTextArea
                        border.color: Colors.strokePrimary
                    }
                }
            }
        }

    }

    footer: Rectangle {
        width: parent.width
        height: 64
        color: Colors.backgroundSurface2

        Separator { orientation: Qt.Horizontal }

        RowLayout {
            anchors.fill: parent

            ListView {
                id: logView

                spacing: 4
                model: transferDataHandler ? transferDataHandler.serviceDataList : {}
                delegate: Text {
                    text: modelData                    
                    font.pixelSize: 12
                    color: Colors.textPrimary
                }
                clip: true

                Layout.margins: 8
                Layout.fillHeight: true
                Layout.fillWidth: true

                onCountChanged: {
                    if (count > 0) {
                        logView.positionViewAtEnd();
                    }
                }
            }

        }
    }

    Component.onCompleted: {
        appTheme.setDarkTheme()
        tcpServerHandler.startServer()       
    }

}
