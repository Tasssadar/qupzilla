/* ============================================================
* QupZilla - WebKit based browser
* Copyright (C) 2010-2014 Franz Fellner <alpine.art.de@googlemail.com>
*                         David Rosca <nowrep@gmail.com>
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
#include "restoremanager.h"
#include "datapaths.h"

#include <QFile>

RestoreManager::RestoreManager()
{
    createFromFile(DataPaths::currentProfilePath() + QLatin1String("/session.dat"));
}

RestoreData RestoreManager::restoreData() const
{
    return m_data;
}

bool RestoreManager::isValid() const
{
    return !m_data.isEmpty();
}

void RestoreManager::createFromFile(const QString &file)
{
    if (!QFile::exists(file)) {
        return;
    }

    QFile recoveryFile(file);
    recoveryFile.open(QIODevice::ReadOnly);
    QDataStream stream(&recoveryFile);

    int version;
    stream >> version;

    if (version != Qz::sessionVersion) {
        return;
    }

    int windowCount;
    stream >> windowCount;

    for (int win = 0; win < windowCount; ++win) {
        QByteArray tabState;
        QByteArray windowState;
        stream >> tabState;
        stream >> windowState;

        WindowData wd;
        wd.windowState = windowState;

        QDataStream tabStream(tabState);
        if (tabStream.atEnd()) {
            continue;
        }

        QVector<WebTab::SavedTab> tabs;
        int tabListCount = 0;
        tabStream >> tabListCount;
        for (int i = 0; i < tabListCount; ++i) {
            WebTab::SavedTab tab;
            tabStream >> tab;
            tabs.append(tab);
        }
        wd.tabsState = tabs;

        int currentTab;
        tabStream >> currentTab;
        wd.currentTab = currentTab;

        m_data.append(wd);
    }
}
