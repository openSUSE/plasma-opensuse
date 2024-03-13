/* Plasma 6 no longer uses start-here-branding by default, it needs to be set explicitly.
 * Utility functions from https://develop.kde.org/docs/plasma/scripting/examples/. */

function forEachWidgetInContainmentList(containmentList, callback) {
    for (var containmentIndex = 0; containmentIndex < containmentList.length; containmentIndex++) {
        var containment = containmentList[containmentIndex];

        var widgets = containment.widgets();
        for (var widgetIndex = 0; widgetIndex < widgets.length; widgetIndex++) {
            var widget = widgets[widgetIndex];
            callback(widget, containment);
            if (widget.type === "org.kde.plasma.systemtray") {
                systemtrayId = widget.readConfig("SystrayContainmentId");
                if (systemtrayId) {
                    forEachWidgetInContainmentList([desktopById(systemtrayId)], callback)
                }
            }
        }
    }
}

function forEachWidget(callback) {
    forEachWidgetInContainmentList(desktops(), callback);
    forEachWidgetInContainmentList(panels(), callback);
}

forEachWidget(function(widget, containment) {
    if (widget.type != "org.kde.plasma.kicker" && widget.type != "org.kde.plasma.kickoff")
         return;

    widget.currentConfigGroup = ["General"];
    print("Icon for " + widget.type + ": " + widget.readConfig("icon"));
    // If using the builtin hardcoded default, switch to the branding icon
    if (widget.readConfig("icon") == "")
        widget.writeConfig("icon", "start-here-branding")
});
