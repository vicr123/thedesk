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
#include "endsession.h"
#include "ui_endsession.h"

#include <Wm/desktopwm.h>
#include <QPainter>
#include <tvariantanimation.h>
#include "transparentdialog.h"
#include <QTimer>
#include <tpopover.h>
#include <statemanager.h>
#include <powermanager.h>

struct EndSessionPrivate {
    tVariantAnimation* powerOffAnimation;
    EndSessionButton* timedButton;
};

EndSession::EndSession(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::EndSession) {
    ui->setupUi(this);

    d = new EndSessionPrivate();
    d->timedButton = ui->powerOffButton;

    d->powerOffAnimation = new tVariantAnimation();
    d->powerOffAnimation->setStartValue(60.0);
    d->powerOffAnimation->setEndValue(0.0);
    d->powerOffAnimation->setDuration(60000);
    connect(d->powerOffAnimation, &tVariantAnimation::valueChanged, this, [ = ](QVariant value) {
        const QMap<EndSessionButton*, const char*> text = {
            {ui->powerOffButton, QT_TR_NOOP("power off the system")},
            {ui->rebootButton, QT_TR_NOOP("reboot the system")},
            {ui->logoutButton, QT_TR_NOOP("log you out")},
            {ui->suspendButton, QT_TR_NOOP("suspend the system")},
            {ui->lockButton, QT_TR_NOOP("lock the screen")},
            {ui->screenOffButton, QT_TR_NOOP("turn off the screen")},
            {ui->switchUsersButton, QT_TR_NOOP("switch users")},
            {ui->hibernateButton, QT_TR_NOOP("hibernate the system")}
        };

        ui->descriptionLabel->setText(tr("Hey %1, ready to head out? We'll %2 in %n seconds if you don't do anything.", nullptr, value < 1 ? 1 : qRound(value.toDouble()))
            .arg(DesktopWm::userDisplayName()).arg(tr(text.value(d->timedButton))));
        d->timedButton->setTimeRemaining(value.toDouble());
    });
    connect(d->powerOffAnimation, &tVariantAnimation::finished, d->timedButton, &QCommandLinkButton::click);
    d->powerOffAnimation->start();

    ui->centeredWidget->setMaximumWidth(SC_DPI(600));
    ui->powerOffButton->setProperty("type", "destructive");
    ui->rebootButton->setProperty("type", "destructive");
    ui->titleLabel->setBackButtonShown(true);
}

EndSession::~EndSession() {
    d->powerOffAnimation->stop();
    delete d;
    delete ui;
}

void EndSession::showDialog() {
    TransparentDialog* dialog = new TransparentDialog();
    dialog->setWindowFlag(Qt::FramelessWindowHint);
    dialog->setWindowFlag(Qt::WindowStaysOnTopHint);
    dialog->showFullScreen();

    QTimer::singleShot(500, [ = ] {
        EndSession* popoverContents = new EndSession();

        tPopover* popover = new tPopover(popoverContents);
        popover->setPopoverSide(tPopover::Bottom);
        popover->setPopoverWidth(popoverContents->heightForWidth(dialog->width()));
        connect(popoverContents, &EndSession::done, popover, &tPopover::dismiss);
        connect(popover, &tPopover::dismissed, popoverContents, &EndSession::deleteLater);
        connect(popover, &tPopover::dismissed, dialog, &TransparentDialog::deleteLater);
        connect(popover, &tPopover::dismissed, popover, &tPopover::deleteLater);
        popover->show(dialog);
    });
}

void EndSession::on_titleLabel_backButtonClicked() {
    d->powerOffAnimation->stop();
    emit done();
}

void EndSession::on_powerOffButton_clicked() {
    StateManager::instance()->powerManager()->performPowerOperation(PowerManager::PowerOff);
    emit done();
}

void EndSession::on_rebootButton_clicked() {
    StateManager::instance()->powerManager()->performPowerOperation(PowerManager::Reboot);
    emit done();
}

void EndSession::on_logoutButton_clicked() {
    StateManager::instance()->powerManager()->performPowerOperation(PowerManager::LogOut);
    emit done();
}

void EndSession::on_suspendButton_clicked() {
    StateManager::instance()->powerManager()->performPowerOperation(PowerManager::Suspend);
    emit done();
}

void EndSession::on_lockButton_clicked() {
    StateManager::instance()->powerManager()->performPowerOperation(PowerManager::Lock);
    emit done();
}

void EndSession::on_screenOffButton_clicked() {
    StateManager::instance()->powerManager()->performPowerOperation(PowerManager::TurnOffScreen);
    emit done();
}

void EndSession::on_switchUsersButton_clicked() {

}

void EndSession::on_hibernateButton_clicked() {
    StateManager::instance()->powerManager()->performPowerOperation(PowerManager::Hibernate);
    emit done();
}
