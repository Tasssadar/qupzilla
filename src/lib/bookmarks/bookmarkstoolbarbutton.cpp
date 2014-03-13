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
#include "bookmarkstoolbarbutton.h"
#include "bookmarkstools.h"
#include "bookmarkitem.h"
#include "bookmarks.h"
#include "mainapplication.h"
#include "enhancedmenu.h"

#include <QStyle>
#include <QPainter>
#include <QMouseEvent>
#include <QStyleOptionButton>

#define MAX_WIDTH 150
#define SEPARATOR_WIDTH 8
#define PADDING 5

BookmarksToolbarButton::BookmarksToolbarButton(BookmarkItem* bookmark, QWidget* parent)
    : QPushButton(parent)
    , m_bookmark(bookmark)
    , m_window(0)
    , m_showOnlyIcon(false)
{
    init();
}

BookmarkItem* BookmarksToolbarButton::bookmark() const
{
    return m_bookmark;
}

void BookmarksToolbarButton::setMainWindow(BrowserWindow* window)
{
    m_window = window;
}

bool BookmarksToolbarButton::showOnlyIcon() const
{
    return m_showOnlyIcon;
}

void BookmarksToolbarButton::setShowOnlyIcon(bool show)
{
    m_showOnlyIcon = show;
    updateGeometry();
}

QSize BookmarksToolbarButton::sizeHint() const
{
    int width = PADDING * 2 + 16;

    if (m_bookmark->isSeparator()) {
        width = SEPARATOR_WIDTH;
    }
    else if (!m_showOnlyIcon) {
        width += PADDING * 2 + fontMetrics().width(m_bookmark->title());

        if (menu()) {
            width += PADDING + 8;
        }
    }

    return QSize(qMin(width, MAX_WIDTH), preferredHeight());
}

QSize BookmarksToolbarButton::minimumSizeHint() const
{
    int width = PADDING * 2 + 16;

    if (m_bookmark->isSeparator()) {
        width = SEPARATOR_WIDTH;
    }
    else if (!m_showOnlyIcon && menu()) {
        width += PADDING + 8;
    }

    return QSize(width, preferredHeight());
}

int BookmarksToolbarButton::preferredHeight() const
{
    return fontMetrics().height() + PADDING * 2;
}

void BookmarksToolbarButton::createMenu()
{
    if (!menu()->isEmpty()) {
        return;
    }

    Menu* m = qobject_cast<Menu*>(menu());
    Q_ASSERT(m);

    foreach (BookmarkItem* child, m_bookmark->children()) {
        BookmarksTools::addActionToMenu(this, m, child);
    }

    if (m->isEmpty()) {
        m->addAction(Bookmarks::tr("Empty"))->setDisabled(true);
    }
}

void BookmarksToolbarButton::menuMiddleClicked(Menu* menu)
{
    BookmarkItem* item = static_cast<BookmarkItem*>(menu->menuAction()->data().value<void*>());
    Q_ASSERT(item);
    openFolder(item);
}

void BookmarksToolbarButton::bookmarkActivated(BookmarkItem* item)
{
    if (QAction* action = qobject_cast<QAction*>(sender())) {
        item = static_cast<BookmarkItem*>(action->data().value<void*>());
    }

    Q_ASSERT(item);
    openBookmark(item);
}

void BookmarksToolbarButton::bookmarkCtrlActivated(BookmarkItem* item)
{
    if (QAction* action = qobject_cast<QAction*>(sender())) {
        item = static_cast<BookmarkItem*>(action->data().value<void*>());
    }

    Q_ASSERT(item);
    openBookmarkInNewTab(item);
}

void BookmarksToolbarButton::bookmarkShiftActivated(BookmarkItem* item)
{
    if (QAction* action = qobject_cast<QAction*>(sender())) {
        item = static_cast<BookmarkItem*>(action->data().value<void*>());
    }

    Q_ASSERT(item);
    openBookmarkInNewWindow(item);
}

void BookmarksToolbarButton::openFolder(BookmarkItem* item)
{
    Q_ASSERT(item->isFolder());

    if (m_window) {
        BookmarksTools::openFolderInTabs(m_window, item);
    }
}

void BookmarksToolbarButton::openBookmark(BookmarkItem* item)
{
    Q_ASSERT(item->isUrl());

    if (m_window) {
        BookmarksTools::openBookmark(m_window, item);
    }
}

void BookmarksToolbarButton::openBookmarkInNewTab(BookmarkItem* item)
{
    Q_ASSERT(item->isUrl());

    if (m_window) {
        BookmarksTools::openBookmarkInNewTab(m_window, item);
    }
}

void BookmarksToolbarButton::openBookmarkInNewWindow(BookmarkItem* item)
{
    Q_ASSERT(item->isUrl());

    BookmarksTools::openBookmarkInNewWindow(item);
}

void BookmarksToolbarButton::init()
{
    Q_ASSERT(m_bookmark);

    setFlat(true);
    setFocusPolicy(Qt::NoFocus);
    setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
    setIconSize(QSize(16, 16));
    setToolTip(createTooltip());

    if (m_bookmark->isFolder()) {
        Menu* m = new Menu(this);
        connect(m, SIGNAL(aboutToShow()), this, SLOT(createMenu()));
        connect(m, SIGNAL(menuMiddleClicked(Menu*)), this, SLOT(menuMiddleClicked(Menu*)));
        setMenu(m);
    }
}

QString BookmarksToolbarButton::createTooltip() const
{
    if (!m_bookmark->description().isEmpty()) {
        if (!m_bookmark->urlString().isEmpty()) {
            return QString("%1\n%2").arg(m_bookmark->description(), m_bookmark->urlString());
        }
        return m_bookmark->description();
    }

    if (!m_bookmark->url().isEmpty()) {
        return QString("%1\n%2").arg(m_bookmark->title(), m_bookmark->urlString());
    }

    return m_bookmark->title();
}

void BookmarksToolbarButton::mousePressEvent(QMouseEvent* event)
{
    if (m_bookmark && m_bookmark->isFolder()) {
        if (event->buttons() == Qt::LeftButton && event->modifiers() == Qt::ControlModifier) {
            openFolder(m_bookmark);
            return;
        }
    }

    QPushButton::mousePressEvent(event);
}

void BookmarksToolbarButton::mouseReleaseEvent(QMouseEvent* event)
{
    if (m_bookmark && rect().contains(event->pos())) {
        Qt::MouseButton button = event->button();
        Qt::KeyboardModifiers modifiers = event->modifiers();

        if (m_bookmark->isUrl()) {
            if (button == Qt::LeftButton && modifiers == Qt::NoModifier) {
                bookmarkActivated(m_bookmark);
            }
            else if (button == Qt::LeftButton && modifiers == Qt::ShiftModifier) {
                bookmarkShiftActivated(m_bookmark);
            }
            else if (button == Qt::MiddleButton || modifiers == Qt::ControlModifier) {
                bookmarkCtrlActivated(m_bookmark);
            }
        }
        else if (m_bookmark->isFolder() && button == Qt::MiddleButton) {
            openFolder(m_bookmark);
        }
    }

    QPushButton::mouseReleaseEvent(event);
}

void BookmarksToolbarButton::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event)

    QPainter p(this);
    QStyleOptionButton option;
    initStyleOption(&option);

    // Just draw separator
    if (m_bookmark->isSeparator()) {
        QStyleOption opt = option;
        opt.state |= QStyle::State_Horizontal;
        style()->drawPrimitive(QStyle::PE_IndicatorToolBarSeparator, &opt, &p);
        return;
    }

    // This ensures correct rendering of Down state with Oxygen
    if (isDown())  {
        option.state &= ~QStyle::State_MouseOver;
    }

    // Draw button base
    style()->drawControl(QStyle::CE_PushButtonBevel, &option, &p, this);

    const int height = option.rect.height();
    const int center = height / 2 + option.rect.top();

    const int iconSize = 16;
    const int iconYPos = center - iconSize / 2;

    int leftPosition = PADDING;
    int rightPosition = option.rect.right() - PADDING;

    // Draw icon
    QRect iconRect(leftPosition, iconYPos, iconSize, iconSize);
    p.drawPixmap(iconRect, m_bookmark->icon().pixmap(iconSize));
    leftPosition = iconRect.right() + PADDING;

    // Draw menu arrow
    if (!m_showOnlyIcon && menu()) {
        const int arrowSize = 8;
        QStyleOption opt;
        opt.initFrom(this);
        opt.rect = QRect(rightPosition - 8, center - arrowSize / 2, arrowSize, arrowSize);
        opt.state &= QStyle::State_MouseOver;
        style()->drawPrimitive(QStyle::PE_IndicatorArrowDown, &opt, &p, this);
        rightPosition = opt.rect.left() - PADDING;
    }

    // Draw text
    if (!m_showOnlyIcon) {
        const int textWidth = rightPosition - leftPosition;
        const int textYPos = center - fontMetrics().height() / 2;
        const QString txt = fontMetrics().elidedText(m_bookmark->title(), Qt::ElideRight, textWidth);
        QRect textRect(leftPosition, textYPos, textWidth, fontMetrics().height());
        style()->drawItemText(&p, textRect, Qt::TextSingleLine | Qt::AlignCenter, option.palette, true, txt);
    }
}
