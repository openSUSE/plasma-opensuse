/*
 *   Copyright 2014 Marco Martin <mart@kde.org>
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
        } else if (stage == 2) {
            bulbOn.running = true;
        } else if (stage == 5) {
            introAnimation.target = busyIndicator;
            introAnimation.from = 1;
            introAnimation.to = 0;
            introAnimation.running = true;

            // bulbOff.running = true;
        }
    }

    Image {
        source: "images/bulb.png"
        fillMode: Image.PreserveAspectFit
        height: parent.height
        x: parent.width * 0.65
        anchors.top: parent.top
        opacity: 0
        OpacityAnimator on opacity {
            running: false
            id: bulbOn
            from: 0
            to: 1
            duration: 1000
            easing.type: Easing.InOutBounce
        }
        OpacityAnimator on opacity {
            running: false
            id: bulbOff
            from: 1
            to: 0
            duration: 1500
            easing.type: Easing.OutElastic
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
            //again sync from SDDM theme
            anchors.centerIn: parent
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
}
