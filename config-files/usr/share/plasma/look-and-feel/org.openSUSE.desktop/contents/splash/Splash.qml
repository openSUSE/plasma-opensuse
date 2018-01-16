/*
 *   Copyright 2014 Marco Martin <mart@kde.org>
 *   Copyright 2018 Fabian Vogt <fabian@ritter-vogt.de>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License version 2,
 *   or (at your option) any later version, as published by the Free
 *   Software Foundation
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details
 *
 *   You should have received a copy of the GNU General Public
 *   License along with this program; if not, write to the
 *   Free Software Foundation, Inc.,
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

import QtQuick 2.5

Rectangle {
    id: root
    color: "black"

    property int stage

    onStageChanged: {
        if (stage == 1) {
            introAnimation.running = true;
            casingIntroAnimation.running = true;
        } else if (stage == 2) {
            bulbOn.running = true;
        } else if (stage == 5) {
            introAnimation.target = busyIndicator;
            introAnimation.from = 1;
            introAnimation.to = 0;
            introAnimation.running = true;
        }
    }

    Image {
        id: casing
        opacity: 0
        source: "images/bulb.svg"
        fillMode: Image.PreserveAspectFit
        height: parent.height
        width: parent.height // The image is square
        anchors.horizontalCenter: parent.horizontalCenter
        y: height * -0.1
    }

    Image {
        id: bulb
        source: "images/filamentglow.svg"
        opacity: 0
        fillMode: Image.PreserveAspectFit
        anchors.fill: casing
        OpacityAnimator on opacity {
            running: false
            id: bulbOn
            from: 0
            to: 1
            duration: 1000
            easing.type: Easing.InOutBounce
        }
    }

    Item {
        id: content
        anchors.fill: parent
        opacity: 0
        TextMetrics {
            id: units
            text: "M"
            property int gridUnit: boundingRect.height
            property int largeSpacing: units.gridUnit
            property int smallSpacing: Math.max(2, gridUnit/4)
        }

        Image {
            id: busyIndicator
            anchors.horizontalCenter: parent.horizontalCenter
            y: parent.height * 0.7
            source: "images/busywidget.svgz"
            sourceSize.height: units.gridUnit * 4
            sourceSize.width: units.gridUnit * 4
            RotationAnimator on rotation {
                id: rotationAnimator
                from: 0
                to: 360
                duration: 1500
                loops: Animation.Infinite
            }
        }
    }

    OpacityAnimator {
        id: introAnimation
        running: false
        target: content
        from: 0
        to: 1
        duration: 1000
        easing.type: Easing.InOutQuad
    }

    OpacityAnimator {
        id: casingIntroAnimation
        running: false
        target: casing
        from: 0
        to: 0.5
        duration: 500
        easing.type: Easing.InOutQuad
    }
}
