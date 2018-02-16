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
import QtGraphicalEffects 1.0

Rectangle {
    id: root
    color: "black"

    property int stage

    onStageChanged: {
        if (stage == 1) {
            introAnimation.running = true;
            casingIntroAnimation.running = true;
        } else if (stage == 2) {
            highlightIntroAnimation.running = true;
        } else if (stage == 5) {
            introAnimation.target = busyIndicator;
            introAnimation.from = 1;
            introAnimation.to = 0;
            introAnimation.running = true;
        }
    }
    FastBlur {
        anchors.fill: highlight
        radius: 25
        source: highlight
    }
    Image {
        id: highlight
        opacity: 0
        source: "images/highlight.svg"
        fillMode: Image.PreserveAspectFit
        height: parent.height * 0.3
        width: parent.height * 0.3 // The image is square
        anchors.horizontalCenter: parent.horizontalCenter
        y: parent.height * 0.2
        OpacityAnimator on opacity {
            running: false
            id: bulbShadowOn
            from: 0
            to: 1
            duration: 500
            easing.type: Easing.InBounce
        }
        OpacityAnimator on opacity {
            running: false
            id: bulbShadowOff
            from: 0.5
            to: 0
            duration: 750
            easing.type: Easing.InExpo
        }
        
    }
    Image {
        id: casing
        opacity: 0
        source: "images/bulb.svg"
        fillMode: Image.PreserveAspectFit
        height: parent.height * 0.3
        width: parent.height * 0.3 // The image is square
        anchors.horizontalCenter: parent.horizontalCenter
        y: parent.height * 0.2
        OpacityAnimator on opacity {
            running: false
            id: bulbOn
            from: 0
            to: 1
            duration: 500
            easing.type: Easing.InBounce
        }
        OpacityAnimator on opacity {
            running: false
            id: bulbOff
            from: 0.5
            to: 0
            duration: 750
            easing.type: Easing.InExpo
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
            y: parent.height * 0.75
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
            easing.type: Easing.InExpo
        }
        ColorAnimation {
            id: colorIntroAnimation
            running: true
            target: root
            property: "color"
            from: "black"
            to: "#081c2d"
            duration: 1000
            easing.type: Easing.InExpo
        }
        OpacityAnimator {
            id: casingIntroAnimation
            running: false
            target: casing
            from: 0
            to: 0.5
            duration: 500
            easing.type: Easing.InBounce
        }
        OpacityAnimator {
            id: highlightIntroAnimation
            running: false
            target: highlight
            from: 0
            to: 0.5
            duration: 500
            easing.type: Easing.InBounce
        }
        
}
