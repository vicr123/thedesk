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
#ifndef SCREENSHOTWINDOW_H
#define SCREENSHOTWINDOW_H

#include <QWidget>

namespace Ui {
    class ScreenshotWindow;
}

struct ScreenshotWindowPrivate;
class ScreenshotWindow : public QWidget {
        Q_OBJECT

    public:
        ~ScreenshotWindow();

        static void take(QScreen* screen, int delay = 0);

    private slots:
        void on_discardButton_clicked();

        void on_copyButton_clicked();

        void on_cropButton_toggled(bool checked);

        void on_redactButton_toggled(bool checked);

        void on_resetButton_clicked();

    private:
        explicit ScreenshotWindow(QScreen* screen, QWidget* parent = nullptr);

        void paintEvent(QPaintEvent* event);
        void mousePressEvent(QMouseEvent* event);
        void mouseReleaseEvent(QMouseEvent* event);
        void mouseMoveEvent(QMouseEvent* event);

        QPixmap finalResult();

        Ui::ScreenshotWindow* ui;
        ScreenshotWindowPrivate* d;
};

#endif // SCREENSHOTWINDOW_H
