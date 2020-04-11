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
#include "statuscentermanager.h"

#include <the-libs_global.h>
#include <QMap>

struct StatusCenterManagerPrivate {
    bool isShowing = false;
    bool hamburgerMenuRequired = false;

    QList<StatusCenterPane*> panes;
    QMap<StatusCenterPane*, StatusCenterManager::PaneType> paneTypes;
};

StatusCenterManager::StatusCenterManager(QObject* parent) : QObject(parent) {
    d = new StatusCenterManagerPrivate();
}

StatusCenterManager::~StatusCenterManager() {
    delete d;
}

void StatusCenterManager::show() {
    emit showStatusCenter();
}

void StatusCenterManager::hide() {
    emit hideStatusCenter();
}

bool StatusCenterManager::isShowingStatusCenter() {
    return d->isShowing;
}

bool StatusCenterManager::isHamburgerMenuRequired() {
    return d->hamburgerMenuRequired;
}

void StatusCenterManager::showStatusCenterHamburgerMenu() {
    emit showHamburgerMenu();
}

void StatusCenterManager::hideStatusCenterHamburgerMenu() {
    emit hideHamburgerMenu();
}

void StatusCenterManager::returnToRootMenu() {
    emit rootMenu();
}

void StatusCenterManager::addPane(StatusCenterPane* pane, StatusCenterManager::PaneType type) {
    if (!d->panes.contains(pane)) {
        d->paneTypes.insert(pane, type);
        d->panes.append(pane);
        emit paneAdded(pane, type);
    }
}

void StatusCenterManager::removePane(StatusCenterPane* pane) {
    if (d->panes.contains(pane)) {
        d->paneTypes.remove(pane);
        d->panes.removeOne(pane);
        emit paneRemoved(pane);
    }
}

int StatusCenterManager::preferredContentWidth() {
    return SC_DPI(600);
}

QList<StatusCenterPane*> StatusCenterManager::panes() {
    return d->panes;
}

StatusCenterManager::PaneType StatusCenterManager::paneType(StatusCenterPane* pane) {
    return d->paneTypes.value(pane);
}

void StatusCenterManager::setIsShowingStatusCenter(bool isShowing) {
    d->isShowing = isShowing;
}

void StatusCenterManager::setIsHamburgerMenuRequired(bool isRequired) {
    d->hamburgerMenuRequired = isRequired;
    emit isHamburgerMenuRequiredChanged(isRequired);
}
