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
#include "onboardingregion.h"
#include "ui_onboardingregion.h"

#include <statemanager.h>
#include <onboardingmanager.h>
#include <localemanager.h>
#include <QLocale>

#include "common.h"

OnboardingRegion::OnboardingRegion(QWidget* parent) :
    OnboardingPage(parent),
    ui(new Ui::OnboardingRegion) {
    ui->setupUi(this);

    ui->titleLabel->setBackButtonShown(true);

    QList<Common::Country> countries = Common::countries();
    for (Common::Country country : countries) {
        QListWidgetItem* item = new QListWidgetItem();
        item->setText(country.text);
        item->setData(Qt::UserRole, country.country);
        ui->countriesWidget->addItem(item);
        if (country.isCurrent) ui->countriesWidget->setCurrentItem(item);
    }
}

OnboardingRegion::~OnboardingRegion() {
    delete ui;
}

void OnboardingRegion::on_nextButton_clicked() {
    StateManager::onboardingManager()->nextStep();
}

QString OnboardingRegion::name() {
    return "OnboardingRegion";
}

QString OnboardingRegion::displayName() {
    return tr("Region");
}
void OnboardingRegion::on_titleLabel_backButtonClicked() {
    StateManager::onboardingManager()->previousStep();
}

void OnboardingRegion::on_countriesWidget_currentItemChanged(QListWidgetItem* current, QListWidgetItem* previous) {
    if (current) {
        StateManager::localeManager()->setFormatCountry(current->data(Qt::UserRole).value<QLocale::Country>());
    }
}
