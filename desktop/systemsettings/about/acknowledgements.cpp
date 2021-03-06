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
#include "acknowledgements.h"
#include "ui_acknowledgements.h"

#include <statemanager.h>
#include <statuscentermanager.h>
#include <QDesktopServices>

Acknowledgements::Acknowledgements(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::Acknowledgements) {
    ui->setupUi(this);

    ui->titleLabel->setBackButtonShown(true);
    ui->textBrowser->setSource(QUrl::fromLocalFile(QStringLiteral("/usr/share/thedesk/acknowledgements.html")), QTextDocument::HtmlResource);
}

Acknowledgements::~Acknowledgements() {
    delete ui;
}

void Acknowledgements::on_titleLabel_backButtonClicked() {
    emit done();
}

void Acknowledgements::on_textBrowser_anchorClicked(const QUrl& arg1) {
    emit done();
    StateManager::statusCenterManager()->hide();
    QDesktopServices::openUrl(arg1);
}
