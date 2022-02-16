import QtQuick
import QtQuick.Controls
import QtMultimedia

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Test video")
    Video {
        anchors.fill: parent
        width: parent.width
        height: parent.height
        id: v
        onPlaybackStateChanged: console.log('state', playbackState)
        onDurationChanged: console.log('Duration', duration)
        onErrorChanged: console.log('error', error)
        onErrorStringChanged: console.log('errorString', errorString)
    }
    Button {
        anchors.bottom: parent.bottom
        text: "Play"
        onClicked: {
            console.log('playing')
            v.source = 'file:///sdcard/bun33s.mp4'
            v.play()
        }
    }
}
