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
#ifndef ONBOARDINGPAGE_H
#define ONBOARDINGPAGE_H

#include <QWidget>

class OnboardingPage : public QWidget {
        Q_OBJECT
    public:
        explicit OnboardingPage(QWidget* parent = nullptr);

        virtual QString name() = 0;
        virtual QString displayName() = 0;

        virtual void pageActivated();

    signals:

};

#endif // ONBOARDINGPAGE_H
