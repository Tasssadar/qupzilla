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
#include "sbi_javascripticon.h"
#include "browserwindow.h"
#include "tabwidget.h"
#include "tabbedwebview.h"
#include "webpage.h"
#include "jsoptions.h"

#include <QGraphicsColorizeEffect>
#include <QWebSettings>
#include <QMenu>

SBI_JavaScriptIcon::SBI_JavaScriptIcon(BrowserWindow* window)
    : ClickableLabel(window)
    , m_window(window)
{
    setCursor(Qt::PointingHandCursor);
    setToolTip(tr("Modify JavaScript settings per-site and globally"));

    m_icon = QIcon::fromTheme("application-x-javascript", QIcon(":sbi/data/javascript.png"));
    setPixmap(m_icon.pixmap(16));

    connect(m_window->tabWidget(), SIGNAL(currentChanged(int)), this, SLOT(updateIcon()));
    connect(this, SIGNAL(clicked(QPoint)), this, SLOT(showMenu(QPoint)));
}

void SBI_JavaScriptIcon::showMenu(const QPoint &point)
{
    QFont boldFont = font();
    boldFont.setBold(true);

    QMenu menu;
    menu.addAction(m_icon, tr("Current page settings"))->setFont(boldFont);

    if (currentPageSettings()->testAttribute(QWebSettings::JavascriptEnabled)) {
        menu.addAction(tr("Disable JavaScript (temporarily)"), this, SLOT(toggleJavaScript()));
    }
    else {
        menu.addAction(tr("Enable JavaScript (temporarily)"), this, SLOT(toggleJavaScript()));
    }

    // JavaScript needs to be always enabled for qupzilla: sites
    if (currentPage()->url().scheme() == QLatin1String("qupzilla")) {
        menu.actions().at(1)->setEnabled(false);
    }

    menu.addSeparator();
    menu.addAction(m_icon, tr("Global settings"))->setFont(boldFont);
    menu.addAction(tr("Manage JavaScript settings"), this, SLOT(openJavaScriptSettings()));
    menu.exec(point);
}

void SBI_JavaScriptIcon::updateIcon()
{
    if (currentPageSettings()->testAttribute(QWebSettings::JavascriptEnabled)) {
        setGraphicsEffect(0);
    }
    else {
        QGraphicsColorizeEffect* effect = new QGraphicsColorizeEffect(this);
        effect->setColor(Qt::gray);
        setGraphicsEffect(effect);
    }
}

void SBI_JavaScriptIcon::toggleJavaScript()
{
    bool current = currentPageSettings()->testAttribute(QWebSettings::JavascriptEnabled);
    currentPage()->setJavaScriptEnabled(!current);

    m_window->weView()->reload();

    updateIcon();
}

void SBI_JavaScriptIcon::openJavaScriptSettings()
{
    JsOptions dialog(m_window);
    dialog.exec();
}

WebPage* SBI_JavaScriptIcon::currentPage()
{
    return m_window->weView()->page();
}

QWebSettings* SBI_JavaScriptIcon::currentPageSettings()
{
    return currentPage()->settings();
}
