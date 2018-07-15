import QtQuick 2.9
import QtQuick.Controls 2.2

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("QtFactory")

    Row {
        spacing: 10

        Column {
            spacing: 10

            QFText {
                text: qsTr("Structure")
            }

            TextField {
                id: structNameTF

                placeholderText: "name"
                text: commonInterface.structName
                onTextChanged: modelNameTF.text = text.length > 0 ? text + "Model" : ""
            }

            QFText {
                text: qsTr("Fields")
            }

            ListView {
                id: memberView

                width: 200
                height: 300
                model: memberModel
                delegate: Row {
                    TextField {
                        text: member
                        onTextChanged: {
                            member = text
                            if (index + 1 === memberView.count) {
                                memberModel.addMember()
                            }
                        }
                    }

                    Button {
                        text: "-"
                        enabled: !(index === memberView.count - 1)
                        onClicked: memberModel.removeMember(index)
                    }
                }
            }
        }

        Column {
            spacing: 10

            QFText {
                text: qsTr("Model")
            }

            TextField {
                id: modelNameTF

                placeholderText: "name"
            }

            QFText {
                text: qsTr("Roles")
            }

            ListView {
                width: 200
                height: 300
                model: ["Id", "Name", "RegDate"]
                delegate: ItemDelegate {
                    text: modelData
                }
            }
        }

        Button {
            text: qsTr("Generate sources")
            onClicked: {
                commonInterface.structName = structNameTF.text
                commonInterface.generateSources()
            }
        }
    }
}
