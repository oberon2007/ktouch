/*
 *  Copyright 2012  Sebastian Gottfried <sebastiangottfried@web.de>
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License as
 *  published by the Free Software Foundation; either version 2 of
 *  the License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

import QtQuick 1.1
import org.kde.locale 0.1 as Locale
import org.kde.plasma.core 0.1 as PlasmaCore
import org.kde.plasma.components 0.1 as PlasmaComponents
import org.kde.ktouch.graph 0.1 as Graph
import ktouch 1.0

Item {
    id: root

    property Profile profile

    function update() {
        if (profile) {
            var isNewProfile = root.profile.id === -1
            profileForm.name = profile.name
            profileForm.skillLevel = profile.skillLevel
            profileForm.skillLevelSelectionEnabled = isNewProfile
            deleteConfirmationLabel.name = profile.name
            state = isNewProfile? "editor": "info"
        }

    }

    onProfileChanged: update()

    Locale.Locale {
        id: locale
    }

    Item {
        id: infoContainer
        width: parent.width
        height: childrenRect.height
        anchors.centerIn: parent

        Column {
            width: parent.width
            height: childrenRect.height
            spacing: 40

            LearningProgressModel {
                id: learningProgressModel
                profile: root.profile
            }


            Rectangle {

                anchors.horizontalCenter: parent.horizontalCenter
                width: parent.width - 40
                height: 250
                color: "white"

                border {
                    width: 1
                    color: "black"
                }

                Column {
                    id: column
                    anchors {
                        fill: parent
                        topMargin: column.spacing + spacing + legend.height
                        leftMargin: column.spacing
                        rightMargin: column.spacing
                        bottomMargin: column.spacing
                    }

                    spacing: 20

                    width: parent.width
                    height: parent.height - legend.height - parent.spacing

                    LearningProgressGraph {
                        id: learningProgressGraph
                        anchors.horizontalCenter: parent.horizontalCenter
                        width: parent.width
                        height: parent.height - legend.height - parent.spacing

                        model: learningProgressModel
                    }

                    Row {
                        id: legend
                        anchors.horizontalCenter: parent.horizontalCenter
                        spacing: 20
                        Graph.LegendItem {
                            dimension: learningProgressGraph.accuracy
                        }
                        Graph.LegendItem {
                            dimension: learningProgressGraph.charactersPerMinute
                        }
                    }
                }
            }

            InformationTable {
                property list<InfoItem> infoModel: [
                    InfoItem {
                        title: i18n("Lessons trained:")
                        text: profile? profileDataAccess.lessonsTrained(profile): ""
                    },
                    InfoItem {
                        title: i18n("Total training time:")
                        text: profile? locale.prettyFormatDuration(profileDataAccess.totalTrainingTime(profile)): ""
                    },
                    InfoItem {
                        title: i18n("Last trained:")
                        text: profile? locale.formatDateTime(profileDataAccess.lastTrainingSession(profile)): ""
                    }
                ]

                model: infoModel
            }

            Row {
                spacing: 10
                anchors.horizontalCenter: parent.horizontalCenter
                width: childrenRect.width
                height: childrenRect.height
                PlasmaComponents.ToolButton {
                    iconSource: "document-edit"
                    text: i18n("Edit")
                    onClicked: root.state = "editor"
                }
                PlasmaComponents.ToolButton {
                    iconSource: "edit-delete"
                    text: i18n("Delete")
                    enabled: profileDataAccess.profileCount > 1
                    onClicked: root.state = "deleteConfirmation"
                }
            }
        }
    }

    Item {
        id: editorContainer
        width: parent.width - 40
        height: childrenRect.height
        anchors.centerIn: parent
        ProfileForm {
            id: profileForm
            width: parent.width
            height: childrenRect.height
            showWelcomeLabel: false
            onDone: {
                root.profile.name = profileForm.name
                root.profile.skillLevel = profileForm.skillLevel
                if (root.profile.id === -1) {
                    profileDataAccess.addProfile(profile)
                }
                else {
                    profileDataAccess.updateProfile(profileDataAccess.indexOfProfile(root.profile))
                }
                root.update()
                root.state = "info"
            }
        }
    }

    Item {
        id: deleteConfirmationContainer
        width: parent.width - 40
        height: childrenRect.height
        anchors.centerIn: parent
        Column {
            width: parent.width
            height: childrenRect.height
            spacing: 15

            PlasmaComponents.Label {
                property string name
                id: deleteConfirmationLabel
                width: parent.width
                text: i18n("Do you really want to delete the profile \"<b>%1</b>\"?", name)
                wrapMode: Text.Wrap
                horizontalAlignment: Text.AlignHCenter
            }
            Row {
                spacing: 10
                anchors.horizontalCenter: parent.horizontalCenter
                width: childrenRect.width
                height: childrenRect.height
                PlasmaComponents.ToolButton {
                    iconSource: "edit-delete"
                    text: i18n("Delete")
                    onClicked: {
                        var index = profileDataAccess.indexOfProfile(root.profile)
                        root.profile = null
                        profileDataAccess.removeProfile(index)
                    }

                }
                PlasmaComponents.ToolButton {
                    text: i18n("Cancel")
                    onClicked: root.state = "info"
                }
            }
        }
    }

    states: [
        State {
            name: "info"
            PropertyChanges {
                target: infoContainer
                visible: true
            }
            PropertyChanges {
                target: editorContainer
                visible: false
            }
            PropertyChanges {
                target: deleteConfirmationContainer
                visible: false
            }
        },
        State {
            name: "editor"
            PropertyChanges {
                target: infoContainer
                visible: false
            }
            PropertyChanges {
                target: editorContainer
                visible: true
            }
            PropertyChanges {
                target: deleteConfirmationContainer
                visible: false
            }
        },
        State {
            name: "deleteConfirmation"
            PropertyChanges {
                target: infoContainer
                visible: false
            }
            PropertyChanges {
                target: editorContainer
                visible: false
            }
            PropertyChanges {
                target: deleteConfirmationContainer
                visible: true
            }
        }
    ]
}