/****************************************
 *
 *   INSERT-PROJECT-NAME-HERE - INSERT-GENERIC-NAME-HERE
 *   Copyright (C) 2020 Victor Tran
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * *************************************/
#include "pluginitemdelegate.h"

#include <the-libs_global.h>
#include <QPainter>
#include <statemanager.h>
#include <statuscentermanager.h>

struct PluginItemDelegatePrivate {
    struct Rects {
        QRect iconRect;
        QRect textRect;
        QRect descRect;
        QRect arrowRect;

        Rects(const QStyleOptionViewItem& option) {
            QRect newRect = option.rect;
            QPoint center = newRect.center();
            newRect.setWidth(StateManager::statusCenterManager()->preferredContentWidth());
            newRect.moveCenter(center);

            iconRect.setLeft(newRect.left() + SC_DPI(6));
            iconRect.setTop(newRect.top() + SC_DPI(6));
            iconRect.setBottom(iconRect.top() + SC_DPI(32));
            iconRect.setRight(iconRect.left() + SC_DPI(32));

            arrowRect.setSize(SC_DPI_T(QSize(16, 16), QSize));
            arrowRect.moveCenter(newRect.center());
            arrowRect.moveRight(newRect.right() - SC_DPI(6));

            textRect.setLeft(iconRect.right() + SC_DPI(6));
            textRect.setTop(newRect.top() + SC_DPI(6));
            textRect.setBottom(newRect.top() + option.fontMetrics.height() + SC_DPI(6));
            textRect.setRight(arrowRect.left() - SC_DPI(6));

            descRect.setLeft(iconRect.right() + SC_DPI(6));
            descRect.setTop(newRect.top() + option.fontMetrics.height() + SC_DPI(8));
            descRect.setBottom(newRect.top() + option.fontMetrics.height() * 2 + SC_DPI(6));
            descRect.setRight(arrowRect.left() - SC_DPI(6));
        }
    };
};

PluginItemDelegate::PluginItemDelegate(QObject* parent) : QAbstractItemDelegate(parent) {
    d = new PluginItemDelegatePrivate();
}

PluginItemDelegate::~PluginItemDelegate() {
    delete d;
}

void PluginItemDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const {
    painter->save();

    painter->setFont(option.font);
    painter->setLayoutDirection(option.direction);

    PluginItemDelegatePrivate::Rects rects(option);
    QString text = index.data().toString();
    QString desc = index.data(Qt::UserRole).toString();
    QIcon icon = index.data(Qt::DecorationRole).value<QIcon>();
    bool active = index.data(Qt::UserRole + 2).toBool();
    bool blacklisted = index.data(Qt::UserRole + 3).toBool();

    if (option.direction == Qt::RightToLeft) {
        rects.iconRect.moveRight(option.rect.right() - SC_DPI(6));
        rects.textRect.moveRight(rects.iconRect.left() - SC_DPI(6));
        rects.descRect.moveRight(rects.iconRect.left() - SC_DPI(6));
    }

    if (option.state & QStyle::State_Selected) {
        painter->setPen(Qt::transparent);
        painter->setBrush(option.palette.color(QPalette::Highlight));
        painter->drawRect(option.rect);
        painter->setBrush(Qt::transparent);
        painter->setPen(option.palette.color(QPalette::HighlightedText));

        if (!active) painter->setOpacity(0.5);
        painter->drawText(rects.textRect, Qt::AlignLeading, text);
        painter->drawText(rects.descRect, Qt::AlignLeading, desc);
    } else if (option.state & QStyle::State_MouseOver) {
        QColor col = option.palette.color(QPalette::Highlight);
        col.setAlpha(127);
        painter->setBrush(col);
        painter->setPen(Qt::transparent);
        painter->drawRect(option.rect);

        if (!active) painter->setOpacity(0.5);
        painter->setBrush(Qt::transparent);
        painter->setPen(option.palette.color(QPalette::WindowText));
        painter->drawText(rects.textRect, Qt::AlignLeading, text);
        painter->setPen(option.palette.color(QPalette::Disabled, QPalette::WindowText));
        painter->drawText(rects.descRect, Qt::AlignLeading, desc);
    } else {
        if (!active) painter->setOpacity(0.5);
        painter->setPen(option.palette.color(QPalette::WindowText));
        painter->drawText(rects.textRect, Qt::AlignLeading, text);
        painter->setPen(option.palette.color(QPalette::Disabled, QPalette::WindowText));
        painter->drawText(rects.descRect, Qt::AlignLeading, desc);
    }

    if (!icon.isNull()) {
        painter->drawPixmap(rects.iconRect, icon.pixmap(rects.iconRect.size()));
    }

    if (blacklisted) {
        painter->setOpacity(1);
        painter->setPen(QPen(option.palette.color(QPalette::WindowText), 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
//        painter->drawLine(rects.iconRect.left() - SC_DPI(6), rects.iconRect.center().y(), rects.textRect.right(), rects.iconRect.center().y());
        painter->drawLine(rects.iconRect.topLeft(), rects.iconRect.bottomRight());
        painter->drawLine(rects.iconRect.bottomLeft(), rects.iconRect.topRight());
    }

    painter->setOpacity(1);
    painter->drawPixmap(rects.arrowRect, QIcon::fromTheme("go-next").pixmap(rects.arrowRect.size()));

    painter->restore();
}

QSize PluginItemDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const {
    PluginItemDelegatePrivate::Rects rects(option);

    QRect u = rects.iconRect;
    u = u.united(rects.textRect);
    u = u.united(rects.descRect);
    u.adjust(SC_DPI(-6), SC_DPI(-6), SC_DPI(6), SC_DPI(6));

    return u.size();
}
