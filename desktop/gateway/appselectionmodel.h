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
#ifndef APPSELECTIONMODEL_H
#define APPSELECTIONMODEL_H

#include <QAbstractListModel>

struct AppSelectionModelPrivate;
class AppSelectionModel : public QAbstractListModel {
        Q_OBJECT

    public:
        explicit AppSelectionModel(QObject* parent = nullptr);
        ~AppSelectionModel() override;

        // Basic functionality:
        int rowCount(const QModelIndex& parent = QModelIndex()) const override;
        QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

        void search(QString query);
        void filterCategory(QString category);

    signals:
        void loading();
        void ready();

    private:
        AppSelectionModelPrivate* d;

        void updateData();
};



#endif // APPSELECTIONMODEL_H
