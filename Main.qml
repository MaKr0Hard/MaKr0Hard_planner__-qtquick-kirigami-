import QtQuick
import QtQuick.Layouts 1.15
import QtQuick.Controls as Controls
import org.kde.kirigami as Kirigami
import MaKrodule 1.0

Kirigami.ApplicationWindow {
    id: window
    width: 640
    height: 480
    minimumWidth: 200
    minimumHeight: 250
    visible: true
    title: qsTr("Planner")

    Func_class {
        id: functions
    }

    ListModel {
        id: categoriesModel

        ListElement {
            categoryName: "Stuff"
            // Nested model definition
            items: []
        }

    }

    function sortListModel(model, parameter) {
        var items = [];
        for (var i = 0; i < model.count; i++) {
            items.push(model.get(i));
        }

        items.sort((a, b) => (a[parameter] > b[parameter]) ? 1 : -1);

        model.clear();
        for (var j = 0; j < items.length; j++) {
            model.append(items[j]);
        }
    }

    property int month: nullptr
    property int dayofweek: nullptr

    function get_month() {
        month = functions.month();
        switch (month) {
        default:
            return " ";
            break;  // Just in case, you know if it already got there
        case 0: return "January";
        case 1: return "February";
        case 2: return "March";
        case 3: return "April";
        case 4: return "May";
        case 5: return "June";
        case 6: return "July";
        case 7: return "August";
        case 8: return "September";
        case 9: return "October";
        case 10: return "November";
        case 11: return "December";
        }

    }


    //property Holiday holida: nullptr

    function get_dayofweek() {
        dayofweek = functions.dayOfWeek();
        switch (dayofweek) {
        default:
            return " ";
            break;  // Just in case, you know if it already got there
        case 0: return "Monday";
        case 1: return "Tuesday";
        case 2: return "Wednesday";
        case 3: return "Thursday";
        case 4: return "Friday";
        case 5: return "Saturday";
        case 6: return "Sunday";
        }

    }

    pageStack.initialPage: homePage
    //property name: functions.get_events();
    Component.onCompleted: {
        pageStack.layers.replace(homePage);

    }

    // Bottom Navigation Bar using Kirigami's native NavigationTabBar
    footer: Kirigami.NavigationTabBar {
        actions: [
            Kirigami.Action {
                text: "Home"
                icon.name: "go-home"
                checked: true
                onTriggered: {pageStack.layers.replace(homePage)}
            },
            Kirigami.Action {
                text: "Planner"
                icon.name: "korganizer"
                onTriggered: pageStack.layers.replace(plannerPage)
            },
            Kirigami.Action {
                text: "More"
                icon.name: "chronometer"
                onTriggered: pageStack.layers.replace(morePage)
            }
        ]
    }

    // Views
    Component {
        id: homePage
        Kirigami.ScrollablePage {
            //title: "Home"

            ColumnLayout {
                Controls.Label {
                    anchors.top: parent

                    text: "Overview"
                    font.pixelSize: 36
                }
                Controls.MenuSeparator {
                    Layout.fillWidth: true
                }

                spacing: 10
                id: col_lay_in_scroll
                Kirigami.CardsLayout {


                    Kirigami.AbstractCard {
                        //padding: 10
                        contentItem: ColumnLayout {
                            Controls.Label {
                                text: get_dayofweek()
                            }

                            Controls.Label {
                                text: functions.dayOfMonth()
                                font.pixelSize: 36
                            }
                            Controls.Label {
                                text: get_month()
                            }
                        }

                    }
                    Kirigami.AbstractCard {
                        showClickFeedback: true
                        Component.onCompleted: {
                                var jsonString = functions.get_json_elements();

                                var items = JSON.parse(jsonString);
                                label_hol_name.text = items[0].name

                            }
                        contentItem: ColumnLayout {
                            RowLayout{
                                Controls.Label {
                                    text: "Days until"
                                }
                                Controls.Label {
                                    id: label_hol_name
                                }
                            }
                            Controls.Label {
                                id: label_days_before
                                text: functions.number_of_days_before_holiday();
                                font.pixelSize: 36;
                            }
                        }
                        onClicked: {pageStack.layers.push(more_holidays)}
                    }
                }

            }


        }
    }

    Component {
        id: plannerPage
        Kirigami.ScrollablePage {
            //title: "Planner"

            /*Controls.Label {
                //anchors.centerIn: parent
                text: "No Alarms Set"
            }*/
            ColumnLayout {
                id: col_lay
                ListModel {
                    id: dataModel
                }
                anchors.fill: parent
                Component.onCompleted: {
                        var jsonString = functions.get_json_elements();

                        var items = JSON.parse(jsonString)




                        for (var i = 0; i < items.length; i++) {//TODO: fix FIXED !! //TODO: now all the others
                            dataModel.append(items[i])
                        }
                    }
                ListView {

                    anchors.fill: parent
                    spacing: 5
                    model: dataModel
                    delegate:

                    Kirigami.Card {
                        padding: 5
                        Layout.fillWidth: true


                        contentItem: ColumnLayout{
                            Layout.fillWidth: true
                            Controls.Label {
                                text: model.name
                            }

                            Controls.Label {
                                text: model.description
                            }
                        }


                        showClickFeedback: true
                    }

                }



            }
        }
    }

    Component {
        id: morePage
        Kirigami.ScrollablePage {
            //title: "More"
            ColumnLayout {
                Controls.Label {
                    anchors.top: parent

                    text: "More"
                    font.pixelSize: 36
                }
                Controls.MenuSeparator {
                    Layout.fillWidth: true
                }

                ColumnLayout {

                    Kirigami.SubtitleDelegate {
                        text: "Settings"
                        icon.name: "configure"
                        Layout.fillWidth: true
                    }

                }
            }
        }
    }

    Component {
        id: more_holidays
        Kirigami.ScrollablePage {
            ColumnLayout {
                anchors.fill: parent
                ListModel {
                    id: listModel_more_holid

                }
                function update_list() {

                    var jsonString = functions.get_json_elements();

                    var items = JSON.parse(jsonString);

                    // Populate the ListModel
                    for (var i = 0; i < items.length; i++) {
                        listModel_more_holid.append(items[i])
                    }
                }

                Component.onCompleted: {
                        var jsonString = functions.get_json_elements();

                        var items = JSON.parse(jsonString)

                        // Populate the ListModel
                        for (var i = 0; i < items.length; i++) {
                            listModel_more_holid.append(items[i])
                        }
                    }
                ListView {
                    anchors.fill: parent
                    model: listModel_more_holid
                    spacing: 5
                    delegate:
                    Kirigami.AbstractCard {
                        padding: 5
                        Layout.fillWidth: true


                        contentItem: ColumnLayout{
                            Layout.fillWidth: true
                            Controls.Label {
                                text: model.name
                            }

                            Controls.Label {
                                text: model.description
                            }
                            Controls.Label {
                                text: functions.day_from_timestamp(model.timestamp) + "/" + functions.month_from_timestamp(model.timestamp) + "/" + functions.year_from_timestamp(model.timestamp);
                            }
                        }

                    }
                }
                Controls.Button {
                    text: "pls clk"
                    onClicked: {functions.save_to_json("hii", 50, "hiiii");
                        var jsonString = functions.get_json_elements();

                        var items = JSON.parse(jsonString);
                        listModel_more_holid.clear();
                        // Populate the ListModel
                        for (var i = 0; i < items.length; i++) {
                            listModel_more_holid.append(items[i])
                        }
                    }
                }
            }
        }
    }

}
