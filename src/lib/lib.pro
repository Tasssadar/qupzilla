isEqual(QT_MAJOR_VERSION, 5) {
    QT += webkitwidgets network widgets printsupport sql script gui-private
} else {
    QT += core gui webkit sql network script concurrent
}

TARGET = QupZilla
TEMPLATE = lib

DEFINES *= QUPZILLA_SHAREDLIBRARY

include(../defines.pri)
include(3rdparty/qtsingleapplication.pri)
include(../../translations/translations.pri)
include(plugins/qtwebkit/qtwebkit-plugins.pri)

CONFIG(debug, debug|release): include(../../tests/modeltest/modeltest.pri)

unix:!contains(DEFINES, "DISABLE_DBUS") QT += dbus

INCLUDEPATH += 3rdparty\
               app\
               autofill\
               bookmarks\
               cookies\
               session\
               downloads\
               history\
               navigation\
               network\
               other\
               preferences\
               rss\
               tools\
               utils\
               webview\
               plugins\
               sidebar\
               data\
               adblock\
               desktopnotifications\
               opensearch\
               popupwindow\

DEPENDPATH += 3rdparty\
              app\
              autofill\
              bookmarks\
              cookies\
              session\
              downloads\
              history\
              navigation\
              network\
              other\
              preferences\
              rss\
              tools\
              utils\
              webview\
              plugins\
              sidebar\
              data\
              adblock\
              desktopnotifications\
              opensearch\
              popupwindow\

SOURCES += \
    webview/tabpreview.cpp \
    3rdparty/qtwin.cpp \
    3rdparty/lineedit.cpp \
    app/mainapplication.cpp \
    app/autosaver.cpp \
    preferences/autofillmanager.cpp \
    bookmarks/bookmarkstoolbar.cpp \
    bookmarks/bookmarksmanager.cpp \
    cookies/cookiemanager.cpp \
    cookies/cookiejar.cpp \
    downloads/downloadmanager.cpp \
    history/historymanager.cpp \
    navigation/websearchbar.cpp \
    navigation/locationbar.cpp \
    navigation/locationbarpopup.cpp \
    network/networkmanagerproxy.cpp \
    network/networkmanager.cpp \
    other/updater.cpp \
    other/sourceviewer.cpp \
    preferences/preferences.cpp \
    rss/rssmanager.cpp \
    other/clearprivatedata.cpp \
    webview/webpage.cpp \
    webview/tabwidget.cpp \
    webview/tabbar.cpp \
    webview/siteinfo.cpp \
    webview/searchtoolbar.cpp \
    app/commandlineoptions.cpp \
    other/aboutdialog.cpp \
    plugins/plugins.cpp \
    plugins/pluginproxy.cpp \
    tools/clickablelabel.cpp \
    downloads/downloadoptionsdialog.cpp \
    tools/treewidget.cpp \
    bookmarks/bookmarkswidget.cpp \
    tools/frame.cpp \
    sidebar/sidebar.cpp \
    webview/siteinfowidget.cpp \
    plugins/clicktoflash.cpp \
    plugins/webpluginfactory.cpp \
    downloads/downloaditem.cpp \
    3rdparty/ecwin7.cpp \
    webview/webtab.cpp \
    rss/rsswidget.cpp \
    autofill/autofillnotification.cpp \
    rss/rssnotification.cpp \
    preferences/sslmanager.cpp \
    preferences/jsoptions.cpp \
    tools/animatedwidget.cpp \
    tools/htmlhighlighter.cpp \
    tools/colors.cpp \
    other/sourceviewersearch.cpp \
    adblock/adblocksubscription.cpp \
    adblock/adblockrule.cpp \
    adblock/adblockmanager.cpp \
    adblock/adblockdialog.cpp \
    adblock/adblockblockednetworkreply.cpp \
    adblock/adblockicon.cpp \
    tools/docktitlebarwidget.cpp \
    sidebar/bookmarkssidebar.cpp \
    sidebar/historysidebar.cpp \
    desktopnotifications/desktopnotification.cpp \
    desktopnotifications/desktopnotificationsfactory.cpp \
    tools/progressbar.cpp \
    tools/iconprovider.cpp \
    network/networkproxyfactory.cpp \
    tools/closedtabsmanager.cpp \
    other/statusbarmessage.cpp \
    tools/buttonbox.cpp \
    tools/widget.cpp \
    3rdparty/squeezelabelv2.cpp \
    3rdparty/squeezelabelv1.cpp \
    tools/buttonwithmenu.cpp \
    other/browsinglibrary.cpp \
    3rdparty/stylehelper.cpp \
    3rdparty/fancytabwidget.cpp \
    history/webhistoryinterface.cpp \
    tools/toolbutton.cpp \
    navigation/navigationbar.cpp \
    navigation/reloadstopbutton.cpp \
    preferences/thememanager.cpp \
    tools/qztools.cpp \
    other/pagescreen.cpp \
    downloads/downloadfilehelper.cpp \
    tools/certificateinfowidget.cpp \
    webview/webinspectordockwidget.cpp \
    preferences/acceptlanguage.cpp \
    opensearch/opensearchreader.cpp \
    opensearch/opensearchengine.cpp \
    opensearch/opensearchenginedelegate.cpp \
    opensearch/searchenginesmanager.cpp \
    opensearch/searchenginesdialog.cpp \
    opensearch/editsearchengine.cpp \
    bookmarks/bookmarksimport/bookmarksimporter.cpp \
    bookmarks/bookmarksimport/firefoximporter.cpp \
    bookmarks/bookmarksimport/chromeimporter.cpp \
    bookmarks/bookmarksimport/operaimporter.cpp \
    bookmarks/bookmarksimport/ieimporter.cpp \
    bookmarks/bookmarksimport/htmlimporter.cpp \
    bookmarks/bookmarksimport/bookmarksimportdialog.cpp \
    tools/iconfetcher.cpp \
    tools/followredirectreply.cpp \
    webview/webhistorywrapper.cpp \
    tools/pagethumbnailer.cpp \
    plugins/speeddial.cpp \
    tools/enhancedmenu.cpp \
    navigation/siteicon.cpp \
    navigation/goicon.cpp \
    rss/rssicon.cpp \
    navigation/downicon.cpp \
    network/cabundleupdater.cpp \
    app/settings.cpp \
    app/proxystyle.cpp \
    popupwindow/popupwebpage.cpp \
    popupwindow/popupwebview.cpp \
    popupwindow/popupwindow.cpp \
    popupwindow/popuplocationbar.cpp \
    webview/tabbedwebview.cpp \
    webview/webview.cpp \
    preferences/pluginlistdelegate.cpp \
    popupwindow/popupstatusbarmessage.cpp \
    other/licenseviewer.cpp \
    other/checkboxdialog.cpp \
    tools/plaineditwithlines.cpp \
    tools/focusselectlineedit.cpp \
    navigation/completer/locationcompleterdelegate.cpp \
    navigation/completer/locationcompleter.cpp \
    navigation/completer/locationcompletermodel.cpp \
    navigation/completer/locationcompleterview.cpp \
    history/history.cpp \
    history/historymodel.cpp \
    history/historyview.cpp \
    history/historyitem.cpp \
    tools/headerview.cpp \
    other/iconchooser.cpp \
    adblock/adblocktreewidget.cpp \
    adblock/adblockaddsubscriptiondialog.cpp \
    tools/emptynetworkreply.cpp \
    3rdparty/processinfo.cpp \
    preferences/pluginsmanager.cpp \
    other/qzsettings.cpp \
    other/useragentmanager.cpp \
    preferences/useragentdialog.cpp \
    session/recoverywidget.cpp \
    session/restoremanager.cpp \
    network/schemehandlers/qupzillaschemehandler.cpp \
    network/schemehandlers/adblockschemehandler.cpp \
    network/schemehandlers/fileschemehandler.cpp \
    tools/listitemdelegate.cpp \
    tools/html5permissions/html5permissionsmanager.cpp \
    tools/html5permissions/html5permissionsnotification.cpp \
    tools/html5permissions/html5permissionsdialog.cpp \
    autofill/pageformcompleter.cpp \
    autofill/autofill.cpp \
    network/schemehandlers/ftpschemehandler.cpp \
    autofill/autofillicon.cpp \
    autofill/autofillwidget.cpp \
    tools/menubar.cpp \
    navigation/navigationcontainer.cpp \
    tools/horizontallistwidget.cpp \
    tools/mactoolbutton.cpp \
    tools/actioncopy.cpp \
    network/pac/proxyautoconfig.cpp \
    network/pac/pacmanager.cpp \
    tools/delayedfilewatcher.cpp \
    autofill/passwordmanager.cpp \
    autofill/passwordbackends/databasepasswordbackend.cpp \
    autofill/passwordbackends/passwordbackend.cpp \
    tools/aesinterface.cpp \
    autofill/passwordbackends/databaseencryptedpasswordbackend.cpp \
    network/sslerrordialog.cpp \
    adblock/adblocksearchtree.cpp \
    tools/tabstackedwidget.cpp \
    tools/combotabbar.cpp \
    webview/javascript/externaljsobject.cpp \
    bookmarks/bookmarks.cpp \
    bookmarks/bookmarkitem.cpp \
    tools/json.cpp \
    bookmarks/bookmarksmodel.cpp \
    bookmarks/bookmarkstreeview.cpp \
    bookmarks/bookmarkstools.cpp \
    bookmarks/bookmarksmenu.cpp \
    bookmarks/bookmarksicon.cpp \
    bookmarks/bookmarksitemdelegate.cpp \
    bookmarks/bookmarkstoolbarbutton.cpp \
    bookmarks/bookmarksexport/bookmarksexporter.cpp \
    bookmarks/bookmarksexport/bookmarksexportdialog.cpp \
    bookmarks/bookmarksexport/htmlexporter.cpp \
    app/browserwindow.cpp \
    history/historymenu.cpp \
    app/datapaths.cpp \
    app/profilemanager.cpp \
    app/mainmenu.cpp \
    tools/sqldatabase.cpp \
    navigation/completer/locationcompleterrefreshjob.cpp \
    webview/tabicon.cpp


HEADERS  += \
    webview/tabpreview.h \
    3rdparty/qtwin.h \
    3rdparty/lineedit.h \
    app/mainapplication.h \
    app/autosaver.h \
    preferences/autofillmanager.h \
    bookmarks/bookmarkstoolbar.h \
    bookmarks/bookmarksmanager.h \
    cookies/cookiemanager.h \
    cookies/cookiejar.h \
    downloads/downloadmanager.h \
    history/historymanager.h \
    navigation/websearchbar.h \
    navigation/locationbar.h \
    network/networkmanagerproxy.h \
    network/networkmanager.h \
    other/updater.h \
    other/sourceviewer.h \
    preferences/preferences.h \
    rss/rssmanager.h \
    other/clearprivatedata.h \
    webview/webpage.h \
    webview/tabwidget.h \
    webview/tabbar.h \
    webview/siteinfo.h \
    webview/searchtoolbar.h \
    app/commandlineoptions.h \
    other/aboutdialog.h \
    plugins/plugininterface.h \
    plugins/plugins.h \
    plugins/pluginproxy.h \
    tools/clickablelabel.h \
    downloads/downloadoptionsdialog.h \
    tools/treewidget.h \
    bookmarks/bookmarkswidget.h \
    tools/frame.h \
    sidebar/sidebar.h \
    webview/siteinfowidget.h \
    plugins/clicktoflash.h \
    plugins/webpluginfactory.h \
    downloads/downloaditem.h \
    3rdparty/ecwin7.h \
    webview/webtab.h \
    rss/rsswidget.h \
    autofill/autofillnotification.h \
    rss/rssnotification.h \
    preferences/sslmanager.h \
    preferences/jsoptions.h \
    tools/animatedwidget.h \
    tools/htmlhighlighter.h \
    other/sourceviewersearch.h \
    adblock/adblocksubscription.h \
    adblock/adblockrule.h \
    adblock/adblockmanager.h \
    adblock/adblockdialog.h \
    adblock/adblockblockednetworkreply.h \
    adblock/adblockicon.h \
    tools/docktitlebarwidget.h \
    sidebar/bookmarkssidebar.h \
    sidebar/historysidebar.h \
    desktopnotifications/desktopnotification.h \
    desktopnotifications/desktopnotificationsfactory.h \
    tools/progressbar.h \
    tools/iconprovider.h \
    network/networkproxyfactory.h \
    tools/closedtabsmanager.h \
    other/statusbarmessage.h \
    tools/buttonbox.h \
    tools/widget.h \
    3rdparty/squeezelabelv2.h \
    3rdparty/squeezelabelv1.h \
    tools/buttonwithmenu.h \
    other/browsinglibrary.h \
    3rdparty/stylehelper.h \
    3rdparty/fancytabwidget.h \
    history/webhistoryinterface.h \
    tools/toolbutton.h \
    navigation/navigationbar.h \
    navigation/reloadstopbutton.h \
    preferences/thememanager.h \
    tools/qztools.h \
    other/pagescreen.h \
    downloads/downloadfilehelper.h \
    tools/certificateinfowidget.h \
    webview/webinspectordockwidget.h \
    3rdparty/msvc2008.h \
    preferences/acceptlanguage.h \
    opensearch/opensearchreader.h \
    opensearch/opensearchengine.h \
    opensearch/opensearchenginedelegate.h \
    opensearch/searchenginesmanager.h \
    opensearch/searchenginesdialog.h \
    opensearch/editsearchengine.h \
    bookmarks/bookmarksimport/bookmarksimporter.h \
    bookmarks/bookmarksimport/firefoximporter.h \
    bookmarks/bookmarksimport/chromeimporter.h \
    bookmarks/bookmarksimport/operaimporter.h \
    bookmarks/bookmarksimport/ieimporter.h \
    bookmarks/bookmarksimport/htmlimporter.h \
    bookmarks/bookmarksimport/bookmarksimportdialog.h \
    tools/iconfetcher.h \
    tools/followredirectreply.h \
    webview/webhistorywrapper.h \
    tools/pagethumbnailer.h \
    plugins/speeddial.h \
    tools/enhancedmenu.h \
    navigation/siteicon.h \
    navigation/goicon.h \
    rss/rssicon.h \
    navigation/downicon.h \
    network/cabundleupdater.h \
    app/settings.h \
    app/proxystyle.h \
    popupwindow/popupwebpage.h \
    popupwindow/popupwebview.h \
    popupwindow/popupwindow.h \
    popupwindow/popuplocationbar.h \
    webview/tabbedwebview.h \
    webview/webview.h \
    preferences/pluginlistdelegate.h \
    popupwindow/popupstatusbarmessage.h \
    other/licenseviewer.h \
    other/checkboxdialog.h \
    tools/plaineditwithlines.h \
    sidebar/sidebarinterface.h \
    tools/focusselectlineedit.h \
    navigation/completer/locationcompleterdelegate.h \
    navigation/completer/locationcompleter.h \
    navigation/completer/locationcompleterview.h \
    history/history.h \
    history/historymodel.h \
    history/historyview.h \
    history/historyitem.h \
    tools/headerview.h \
    other/iconchooser.h \
    adblock/adblocktreewidget.h \
    adblock/adblockaddsubscriptiondialog.h \
    tools/emptynetworkreply.h \
    3rdparty/processinfo.h \
    preferences/pluginsmanager.h \
    other/qzsettings.h \
    other/useragentmanager.h \
    preferences/useragentdialog.h \
    session/recoverywidget.h \
    session/restoremanager.h \
    network/schemehandlers/schemehandler.h \
    network/schemehandlers/qupzillaschemehandler.h \
    network/schemehandlers/adblockschemehandler.h \
    network/schemehandlers/fileschemehandler.h \
    tools/listitemdelegate.h \
    tools/html5permissions/html5permissionsmanager.h \
    tools/html5permissions/html5permissionsnotification.h \
    tools/html5permissions/html5permissionsdialog.h \
    autofill/pageformcompleter.h \
    autofill/autofill.h \
    network/schemehandlers/ftpschemehandler.h \
    autofill/autofillicon.h \
    autofill/autofillwidget.h \
    tools/menubar.h \
    navigation/navigationcontainer.h \
    tools/horizontallistwidget.h \
    tools/mactoolbutton.h \
    tools/qzregexp.h \
    tools/actioncopy.h \
    network/pac/proxyautoconfig.h \
    network/pac/pacmanager.h \
    network/pac/pacdatetime.h \
    tools/delayedfilewatcher.h \
    autofill/passwordmanager.h \
    autofill/passwordbackends/passwordbackend.h \
    autofill/passwordbackends/databasepasswordbackend.h \
    tools/aesinterface.h \
    autofill/passwordbackends/databaseencryptedpasswordbackend.h \
    network/sslerrordialog.h \
    adblock/adblocksearchtree.h \
    tools/tabstackedwidget.h \
    tools/combotabbar.h \
    webview/javascript/externaljsobject.h \
    bookmarks/bookmarks.h \
    bookmarks/bookmarkitem.h \
    tools/json.h \
    bookmarks/bookmarksmodel.h \
    bookmarks/bookmarkstreeview.h \
    bookmarks/bookmarkstools.h \
    bookmarks/bookmarksmenu.h \
    bookmarks/bookmarksicon.h \
    bookmarks/bookmarksitemdelegate.h \
    bookmarks/bookmarkstoolbarbutton.h \
    bookmarks/bookmarksexport/bookmarksexporter.h \
    bookmarks/bookmarksexport/bookmarksexportdialog.h \
    bookmarks/bookmarksexport/htmlexporter.h \
    app/browserwindow.h \
    app/qzcommon.h \
    history/historymenu.h \
    app/datapaths.h \
    app/profilemanager.h \
    app/mainmenu.h \
    tools/sqldatabase.h \
    navigation/completer/locationcompleterrefreshjob.h \
    webview/tabicon.h

FORMS    += \
    preferences/autofillmanager.ui \
    bookmarks/bookmarksmanager.ui \
    cookies/cookiemanager.ui \
    history/historymanager.ui \
    preferences/preferences.ui \
    rss/rssmanager.ui \
    webview/siteinfo.ui \
    other/aboutdialog.ui \
    preferences/pluginslist.ui \
    downloads/downloadoptionsdialog.ui \
    bookmarks/bookmarkswidget.ui \
    webview/siteinfowidget.ui \
    downloads/downloaditem.ui \
    downloads/downloadmanager.ui \
    rss/rsswidget.ui \
    autofill/autofillnotification.ui \
    rss/rssnotification.ui \
    preferences/sslmanager.ui \
    preferences/jsoptions.ui \
    other/clearprivatedata.ui \
    other/sourceviewersearch.ui \
    adblock/adblockdialog.ui \
    tools/docktitlebarwidget.ui \
    sidebar/bookmarkssidebar.ui \
    sidebar/historysidebar.ui \
    desktopnotifications/desktopnotification.ui \
    webview/jsconfirm.ui \
    webview/jsalert.ui \
    webview/jsprompt.ui \
    other/browsinglibrary.ui \
    webview/searchtoolbar.ui \
    preferences/thememanager.ui \
    other/pagescreen.ui \
    tools/certificateinfowidget.ui \
    preferences/acceptlanguage.ui \
    preferences/addacceptlanguage.ui \
    opensearch/searchenginesdialog.ui \
    opensearch/editsearchengine.ui \
    bookmarks/bookmarksimport/bookmarksimportdialog.ui \
    other/checkboxdialog.ui \
    other/iconchooser.ui \
    adblock/adblockaddsubscriptiondialog.ui \
    preferences/useragentdialog.ui \
    session/recoverywidget.ui \
    tools/html5permissions/html5permissionsnotification.ui \
    tools/html5permissions/html5permissionsdialog.ui \
    autofill/autofillwidget.ui \
    autofill/passwordbackends/masterpassworddialog.ui \
    network/sslerrordialog.ui \
    bookmarks/bookmarksexport/bookmarksexportdialog.ui

RESOURCES += \
    data/icons.qrc \
    data/html.qrc \
    data/data.qrc \
    data/certs.qrc \

isEqual(QT_MAJOR_VERSION, 5) {
    include(3rdparty/qftp.pri)

    SOURCES += tools/qzregexp.cpp
}

!mac:unix {
    target.path = $$library_folder

    INSTALLS += target

    !contains(DEFINES, NO_X11):LIBS += -lX11
    LIBS += -lcrypto

    RESOURCES -= data/certs.qrc
}

win32 {
    HEADERS += other/registerqappassociation.h
    SOURCES += other/registerqappassociation.cpp

    LIBS += -llibeay32
}

os2 {
    LIBS += -lcrypto
}

freebsd-* {
    LIBS += -lexecinfo
}

mac {
    HEADERS += other/macmenureceiver.h \
               webview/macwebviewscroller.h
    SOURCES += other/macmenureceiver.cpp \
               webview/macwebviewscroller.cpp
    RESOURCES -= data/certs.qrc

    LIBS += -lcrypto -framework CoreServices
}

message(===========================================)
message( Using following defines:)
message(  $$DEFINES)
