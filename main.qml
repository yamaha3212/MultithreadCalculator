import QtQuick 2.4
import QtQuick.Controls 2.1
import QtQuick.Window 2.1

Window {
    visible: true

    minimumWidth: 435
    minimumHeight: 355

    title: qsTr("Multithread Calculator")
    property int selectedOp : 9
    property bool opClicked: false
    property bool dotClicked: false
    property bool eqClicked: false
    property int cderr: 0

    Connections {
        target: calculator
        onSendResult: {
            cderr = code
            error.text = "ErrCode: " + code
            if (code == 3) {
                answer.text = "Result:     Inf"
                resultText.text = "C"
                }
            else {answer.text = "Result:     " +  Math.round(result * 100000) / 100000}
        }
    }

    Rectangle {
        id: resultArea
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        height: parent.height * 1.5 / 8
        color: "#4b374b"
        Text {
            id: resultText
            font.pixelSize: parent.height * 1.5 / 2
            anchors.leftMargin: buttons.implicitMargin
            anchors.rightMargin: buttons.implicitMargin + 10
            anchors.fill: parent
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignVCenter
            text: "0"
            color: "#e9e9e9"
            fontSizeMode: Text.Fit
        }
        Text {
            id: answer
            font.pixelSize: parent.height * 1.5 / 4
            anchors.leftMargin: buttons.implicitMargin + 5
            anchors.rightMargin: buttons.implicitMargin
            anchors.fill: parent
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignBottom
            property int result : 0
            text: "Result:     " + result
            color: "#e9e9e9"
            fontSizeMode: Text.Fit
        }
        Text {
            id: error
            font.pixelSize: parent.height * 1.5 / 4
            anchors.leftMargin: buttons.implicitMargin + 5
            anchors.rightMargin: buttons.implicitMargin
            anchors.fill: parent
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignTop
            property int ercode : 0
            text: "ErrCode: " + ercode
            color: "#e9e9e9"
            fontSizeMode: Text.Fit
        }
    }

    Item {
        id: buttons
        anchors.top: resultArea.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        property real implicitMargin: {
            var ret = 0;
            for (var i = 0; i < visibleChildren.length; ++i) {
                var child = visibleChildren[i];
                ret += (child.implicitMargin || 0);
            }
            return ret / visibleChildren.length;
        }

        Repeater {
            id: operations
            model: ["÷", "×", "+", "-"]
            Button {
                id: operation
                y: 0
                x: index * width
                width: parent.width / 4
                height: parent.height / 5
                text: modelData
                onClicked: {
                    if (eqClicked) {eqClicked = false}
                    if (cderr !== 3) {
                    if (!opClicked) {calculator.pushRequest(resultText.text)}
                    opClicked = true
                    dotClicked = false
                    if (selectedOp != 9) {
                        selectedOp = eventName
                        calculator.tryCalculate()
                    } else { selectedOp = eventName }
                    }
                }
                property string eventName: {
                    switch (text) {
                    case "+": return 0
                    case "-": return 1
                    case "÷": return 2
                    case "×": return 3
                    }
                }
                contentItem: Text {
                        color: "#e9e9e9"
                        font.pixelSize: parent.height * 1.5 / 3
                        text: operation.text
                        opacity: enabled ? 1.0 : 0.3
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        elide: Text.ElideRight
                    }

                    background: Rectangle {
                        color: operation.pressed ? "#736e66" : "#37373c"
                        opacity: enabled ? 1 : 0.3
                        border.color: "#4b374b"
                        border.width: 1
                    }
            }
        }

        Repeater {
            id: digits
            model: ["7", "8", "9", "4", "5", "6", "1", "2", "3", "0", "C", "."]
            Button {
                id: digit
                opacity: enabled ? 1.0 : 0.3
                x: (index % 3) * width
                y: Math.floor(index / 3 + 1) * height
                width: parent.width / 4
                height: parent.height / 5
                text: modelData
                onClicked: {
                        if (eventName == "C") {
                            calculator.terminate()
                            resultText.text = 0
                            answer.text = "Result:     " + 0;
                            error.text = "ErrCode: " + 0;
                            selectedOp = 9
                            opClicked = false
                            dotClicked = false
                            cderr = 0
                            return
                            }
                        if (cderr !== 3) {
                        if (eventName == ".") {
                            for (var i = 0; i < resultText.text.length; ++i) {
                                if (resultText.text[i] === ".") {
                                    dotClicked = true
                                    return }
                                }
                            resultText.text = dotClicked ? resultText.text : resultText.text.concat(eventName)
                            }
                        else {resultText.text = opClicked ? eventName : resultText.text == "0" ? eventName : resultText.text.length > 6 ? resultText.text : resultText.text.concat(eventName)}
                        if (selectedOp != 9 && opClicked && !eqClicked) { calculator.pushOperation(selectedOp) }
                        if (eqClicked) { calculator.pushOperation(4) }
                        opClicked = false
                        eqClicked = false
                    }
                    }
                property string eventName: {
                    switch (text) {
                    default: return text
                    }
                }
                contentItem: Text {
                        color: "#e9e9e9"
                        font.pixelSize: parent.height * 1.5 / 3
                        text: digit.text
                        opacity: enabled ? 1.0 : 0.3
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        elide: Text.ElideRight
                    }

                    background: Rectangle {
                        color: digit.down ? "#c97d20" : "#fd9e2b"
                        opacity: enabled ? 1 : 0.3
                        border.color: "#4b374b"
                        border.width: 1
                    }
            }
        }


        Button {
            id: resultButton
            x: 3 * width
            y: parent.height / 5
            width: parent.width / 4
            height: y * 3
            text: "="
            onClicked: {
                if (cderr !== 3) {
                if (!opClicked)
                calculator.pushRequest(resultText.text)
                calculator.tryCalculate()
                opClicked = true
                eqClicked = true
                }
            }
            contentItem: Text {
                    id: equal
                    color: "#e9e9e9"
                    font.pixelSize: parent.height * 1.5 / 10
                    text: resultButton.text
                    opacity: enabled ? 1.0 : 0.3
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    elide: Text.ElideRight
                }

                background: Rectangle {
                    border.color: "#4b374b"
                    border.width: 1
                    color: resultButton.down ? "#736e66" : "#37373c"
                    opacity: enabled ? 1 : 0.3
                }
        }

        Rectangle {
            x: 3 * width
            y: 4 * height
            width: parent.width / 4
            height: parent.height / 5
            color: "#fd9e2b"
            border.color: "#4b374b"
            border.width: 1
            Dial {
                id: dialDelay
                anchors.fill: parent
                live: true
                from: 0
                to: 10000
                onMoved: {
                    calculator.setDelay(value)
                }
            }
        }

    }
}
