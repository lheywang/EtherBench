pragma Singleton
import QtQuick

QtObject {
    /*
     * Global colors :
     */
    readonly property color background: '#191a1b'
    readonly property color panelBackground: '#313233'
    readonly property color popUpBackground: '#b3b9be'
    readonly property color border: '#707070'
    readonly property color borderSelected: '#8755c0'
    readonly property int standardMargin: 15
    readonly property int standardSpacing: 20

    readonly property int borderHeight: 3
    readonly property int borderRadius: 10

    /*
     * Delimiter
     */
    readonly property int delimiterHeight: 2
    readonly property int delimiterRadius: 5
    readonly property color delimitedColor: '#3994bc'

    /*
     * Menubar settings
     */

    /*
     * Text colors
     */
    // General purpose text
    readonly property color textPrimary: "#90a4ae"
    readonly property color textSecondary: '#6e7b81'
    readonly property color textDisabled: "#2e2f30"
    readonly property int fontSizeNormal: 12
    readonly property bool fontBoldNormal: false
    readonly property int fontSizeTitle: 14
    readonly property bool fontBoldTitle: true
    readonly property int fontSizeSmall: 11
    readonly property bool fontBoldSmall: false
    readonly property string fontStandard: "Consolas"

    // Statuses
    readonly property color textStatusValid: '#46b946'
    readonly property color textStatusInvalid: "#e01010"
    readonly property bool textStatusBold: true

    // Selected
    readonly property color textSelected: '#ffffff'

    /*
     * Buttons colors
     */
    readonly property color controlBg: "#bfbfbf"
    readonly property color controlBorderFocus: '#6b6b6b'
    readonly property int controlRadius: 3

    /*
     * Pop ups :
     */

    /*
     * Splitwidths settings
     */
    readonly property int panelPreferredWidth: 300
    readonly property int panelMaximalWidth: 600
    readonly property int panelMinimalWidth: 220

    /*
     * Accent colors
     */
    readonly property color textStatusAccentYellow: '#d8bb3a'

    readonly property color textStatusAccentPink: '#da4adf'

    readonly property color textStatusAccentBlue1: '#00BCD4'
    readonly property color textStatusAccentBlue2: '#094771'

    readonly property color textStatusAccentGreen: '#4CAF50'

    readonly property color textStatusAccentMagenta: '#9c1a50'
}
