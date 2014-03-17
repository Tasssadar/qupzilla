/* ============================================================
* QupZilla - WebKit based browser
* Copyright (C) 2014  David Rosca <nowrep@gmail.com>
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
#include "tabicon.h"
#include "webtab.h"
#include "tabbedwebview.h"

#include <QTimer>

#define ANIMATION_INTERVAL 70

TabIcon::TabIcon(QWidget* parent)
    : QWidget(parent)
    , m_tab(0)
    , m_currentFrame(0)
    , m_animationRunning(false)
{
    setObjectName(QSL("tab-icon"));

    m_animationImage = QImage(QSL(":icons/other/loading.png"));
    m_framesCount = m_animationImage.width() / 16;

    m_updateTimer = new QTimer(this);
    m_updateTimer->setInterval(ANIMATION_INTERVAL);
    connect(m_updateTimer, SIGNAL(timeout()), this, SLOT(updateAnimationFrame()));

    resize(16, 16);
}

void TabIcon::setWebTab(WebTab* tab)
{
    m_tab = tab;

    connect(m_tab->view(), SIGNAL(loadStarted()), this, SLOT(showLoadingAnimation()));
    connect(m_tab->view(), SIGNAL(loadFinished(bool)), this, SLOT(hideLoadingAnimation()));
    connect(m_tab->view(), SIGNAL(iconChanged()), this, SLOT(showIcon()));

    showIcon();
}

void TabIcon::setIcon(const QIcon &icon)
{
    m_siteImage = icon.pixmap(16).toImage();
    update();
}

void TabIcon::showLoadingAnimation()
{
    m_currentFrame = 0;

    // Start animation delayed with 100 ms
    m_updateTimer->setInterval(100);
    m_updateTimer->start();
}

void TabIcon::hideLoadingAnimation()
{
    m_animationRunning = false;

    m_updateTimer->stop();
    showIcon();
}

void TabIcon::showIcon()
{
    m_siteImage = m_tab->icon().pixmap(16).toImage();
    update();
}

void TabIcon::updateAnimationFrame()
{
    if (!m_animationRunning) {
        m_animationRunning = true;
        m_updateTimer->setInterval(ANIMATION_INTERVAL);
    }

    update();
    m_currentFrame = (m_currentFrame + 1) % m_framesCount;
}

void TabIcon::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    QPainter p(this);

    if (m_animationRunning) {
        p.drawImage(0, 0, m_animationImage, m_currentFrame * 16, 0, 16, 16);
    }
    else {
        p.drawImage(0, 0, m_siteImage);
    }
}
