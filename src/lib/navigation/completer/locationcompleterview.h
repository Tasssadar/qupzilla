/* ============================================================
* QupZilla - WebKit based browser
* Copyright (C) 2010-2014  David Rosca <nowrep@gmail.com>
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
#ifndef LOCATIONCOMPLETERVIEW_H
#define LOCATIONCOMPLETERVIEW_H

#include <QListView>

#include "qzcommon.h"

class LocationCompleterDelegate;

class QUPZILLA_EXPORT LocationCompleterView : public QListView
{
    Q_OBJECT
public:
    explicit LocationCompleterView();

    QPersistentModelIndex hoveredIndex() const;

    bool eventFilter(QObject* object, QEvent* event);

signals:
    void closed();

    void indexActivated(const QModelIndex &index);
    void indexCtrlActivated(const QModelIndex &index);
    void indexShiftActivated(const QModelIndex &index);
    void indexDeleteRequested(const QModelIndex &index);

public slots:
    void close();

private slots:
    void currentChanged(const QModelIndex &current, const QModelIndex &previous);

protected:
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

private:
    bool m_ignoreNextMouseMove;

    LocationCompleterDelegate* m_delegate;
    QPersistentModelIndex m_hoveredIndex;
};

#endif // LOCATIONCOMPLETERVIEW_H
