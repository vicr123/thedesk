/****************************************
 *
 *   INSERT-PROJECT-NAME-HERE - INSERT-GENERIC-NAME-HERE
 *   Copyright (C) 2021 Victor Tran
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
#include "devicedelegate.h"


#include <the-libs_global.h>
#include <QPainter>
#include <statemanager.h>
#include <statuscentermanager.h>
#include "common.h"

#include <BluezQt/DevicesModel>

struct DeviceDelegatePrivate {
    bool isPair;

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

DeviceDelegate::DeviceDelegate(bool isPair, QObject* parent) : QAbstractItemDelegate(parent) {
    d = new DeviceDelegatePrivate();
    d->isPair = isPair;
}

DeviceDelegate::~DeviceDelegate() {
    delete d;
}

void DeviceDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const {
    painter->save();

    painter->setFont(option.font);
    painter->setLayoutDirection(option.direction);

    DeviceDelegatePrivate::Rects rects(option);
    QString text = index.data().toString();
    QString desc = Common::stringForDeviceType(index.data(BluezQt::DevicesModel::TypeRole).value<BluezQt::Device::Type>());
    QIcon icon = QIcon::fromTheme(index.data(BluezQt::DevicesModel::IconRole).toString());
    bool active = index.data(BluezQt::DevicesModel::ConnectedRole).toBool();

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

        if (!active && !d->isPair) painter->setOpacity(0.5);
        painter->drawText(rects.textRect, Qt::AlignLeading, text);
        painter->drawText(rects.descRect, Qt::AlignLeading, desc);
    } else if (option.state & QStyle::State_MouseOver) {
        QColor col = option.palette.color(QPalette::Highlight);
        col.setAlpha(127);
        painter->setBrush(col);
        painter->setPen(Qt::transparent);
        painter->drawRect(option.rect);

        if (!active && !d->isPair) painter->setOpacity(0.5);
        painter->setBrush(Qt::transparent);
        painter->setPen(option.palette.color(QPalette::WindowText));
        painter->drawText(rects.textRect, Qt::AlignLeading, text);
        painter->setPen(option.palette.color(QPalette::Disabled, QPalette::WindowText));
        painter->drawText(rects.descRect, Qt::AlignLeading, desc);
    } else {
        if (!active && !d->isPair) painter->setOpacity(0.5);
        painter->setPen(option.palette.color(QPalette::WindowText));
        painter->drawText(rects.textRect, Qt::AlignLeading, text);
        painter->setPen(option.palette.color(QPalette::Disabled, QPalette::WindowText));
        painter->drawText(rects.descRect, Qt::AlignLeading, desc);
    }

    if (!icon.isNull()) {
        painter->drawPixmap(rects.iconRect, icon.pixmap(rects.iconRect.size()));
    }

    painter->setOpacity(1);
    painter->drawPixmap(rects.arrowRect, QIcon::fromTheme("go-next").pixmap(rects.arrowRect.size()));

    painter->restore();
}

QSize DeviceDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const {
    DeviceDelegatePrivate::Rects rects(option);

    QRect u = rects.iconRect;
    u = u.united(rects.textRect);
    u = u.united(rects.descRect);
    u.adjust(SC_DPI(-6), SC_DPI(-6), SC_DPI(6), SC_DPI(6));

    return u.size();
}
