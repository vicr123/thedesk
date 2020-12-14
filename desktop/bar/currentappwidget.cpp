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
#include "currentappwidget.h"
#include "ui_currentappwidget.h"

#include <the-libs_global.h>
#include <Wm/desktopwm.h>
#include <Applications/application.h>
#include <QIcon>

struct CurrentAppWidgetPrivate {
    QPalette pal;
};

CurrentAppWidget::CurrentAppWidget(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::CurrentAppWidget) {
    ui->setupUi(this);

    d = new CurrentAppWidgetPrivate();
    d->pal = this->palette();

    connect(DesktopWm::instance(), &DesktopWm::activeWindowChanged, this, &CurrentAppWidget::activeWindowChanged);
    activeWindowChanged();
}

CurrentAppWidget::~CurrentAppWidget() {
    delete d;
    delete ui;
}

void CurrentAppWidget::barHeightChanging(float barTransitionPercentage) {
    if (qFuzzyIsNull(barTransitionPercentage)) {
        this->setFixedWidth(QWIDGETSIZE_MAX);
        this->setVisible(true);
    } else if (qFuzzyCompare(barTransitionPercentage, 1)) {
        this->setVisible(false);
    } else {
        this->setFixedWidth(this->sizeHint().width() * (1 - barTransitionPercentage));
        this->setVisible(true);
    }
}

void CurrentAppWidget::activeWindowChanged() {
    DesktopWmWindowPtr active = DesktopWm::activeWindow();
    if (active) {
        ApplicationPointer app = active->application();
        if (app) {
            ui->iconLabel->setPixmap(QIcon::fromTheme(app->getProperty("Icon").toString()).pixmap(SC_DPI_T(QSize(16, 16), QSize)));
            ui->currentAppLabel->setText(app->getProperty("Name").toString());
        } else {
            ui->iconLabel->setPixmap(active->icon().pixmap(SC_DPI_T(QSize(16, 16), QSize)));
            ui->currentAppLabel->setText(tr("Application"));
        }
    } else {
        ui->iconLabel->setPixmap(QIcon(":/thedesk/desktop/thedesk.svg").pixmap(SC_DPI_T(QSize(16, 16), QSize)));
        ui->currentAppLabel->setText(QStringLiteral("theDesk"));
    }
}


void CurrentAppWidget::enterEvent(QEvent* event) {
    QPalette pal = d->pal;
    pal.setColor(QPalette::Window, QColor(255, 255, 255, 100));
    this->setPalette(pal);
}

void CurrentAppWidget::leaveEvent(QEvent* event) {
    this->setPalette(d->pal);
}