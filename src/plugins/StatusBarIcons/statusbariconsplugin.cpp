/* ============================================================
* StatusBarIcons - Extra icons in statusbar for QupZilla
* Copyright (C) 2013-2014  David Rosca <nowrep@gmail.com>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
* ============================================================ */
#include "statusbariconsplugin.h"
#include "sbi_iconsmanager.h"
#include "sbi_settingsdialog.h"
#include "pluginproxy.h"
#include "browserwindow.h"

#include <QTranslator>

StatusBarIconsPlugin::StatusBarIconsPlugin()
    : QObject()
    , m_manager(0)
{
}

PluginSpec StatusBarIconsPlugin::pluginSpec()
{
    PluginSpec spec;
    spec.name = "StatusBar Icons";
    spec.info = "Icons in statusbar providing various actions";
    spec.description = "Adds additional icons to statusbar";
    spec.version = "0.1.6";
    spec.author = "David Rosca <nowrep@gmail.com>";
    spec.icon = QPixmap(":sbi/data/icon.png");
    spec.hasSettings = true;

    return spec;
}

void StatusBarIconsPlugin::init(InitState state, const QString &settingsPath)
{
    m_manager = new SBI_IconsManager(settingsPath);

    connect(mApp->plugins(), SIGNAL(mainWindowCreated(BrowserWindow*)), m_manager, SLOT(mainWindowCreated(BrowserWindow*)));
    connect(mApp->plugins(), SIGNAL(mainWindowDeleted(BrowserWindow*)), m_manager, SLOT(mainWindowDeleted(BrowserWindow*)));

    // Make sure icons are added also to already created windows
    if (state == LateInitState) {
        foreach (BrowserWindow* window, mApp->mainWindows()) {
            m_manager->mainWindowCreated(window);
        }
    }
}

void StatusBarIconsPlugin::unload()
{
    // Make sure icons are properly removed when unloading plugin (but not when closing app)
    if (!mApp->isClosing()) {
        foreach (BrowserWindow* window, mApp->mainWindows()) {
            m_manager->mainWindowDeleted(window);
        }

        delete m_manager;
    }
}

bool StatusBarIconsPlugin::testPlugin()
{
    return (Qz::VERSION == QLatin1String("1.7.0"));
}

QTranslator* StatusBarIconsPlugin::getTranslator(const QString &locale)
{
    QTranslator* translator = new QTranslator(this);
    translator->load(locale, ":/sbi/locale/");
    return translator;
}

void StatusBarIconsPlugin::showSettings(QWidget* parent)
{
    SBI_SettingsDialog dialog(m_manager, parent);
    dialog.exec();
}

#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(StatusBarIcons, StatusBarIconsPlugin)
#endif
