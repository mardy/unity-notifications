/*
 * Copyright (C) 2013 Canonical, Ltd.
 *
 * Authors:
 *    Jussi Pakkanen <jussi.pakkanen@canonical.com>
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 3, as published
 * by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "notify-backend.hpp"
#include "notificationmodel.h"
#include "mainWindow.h"
#include "notification.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setupUi(this);
    m = new NotificationModel();
    notificationCount = 0;
    syncCount = 0;
    interactiveCount = 0;
    snapCount = 0;
    listView->setModel(m);

    connect(this->synchronousSendButton, SIGNAL(clicked()), this, SLOT(sendSynchronousNotification()));

    connect(this->notificationSendButton, SIGNAL(clicked()), this, SLOT(sendLowNotification()));
    connect(this->notificationNormalButton, SIGNAL(clicked()), this, SLOT(sendNormalNotification()));
    connect(this->notificationCriticalButton, SIGNAL(clicked()), this, SLOT(sendCriticalNotification()));

    connect(this->interactiveSendButton, SIGNAL(clicked()), this, SLOT(sendLowInteractiveNotification()));
    connect(this->interactiveNormalButton, SIGNAL(clicked()), this, SLOT(sendNormalInteractiveNotification()));
    connect(this->interactiveCriticalButton, SIGNAL(clicked()), this, SLOT(sendCriticalInteractiveNotification()));

    connect(this->snapSendButton, SIGNAL(clicked()), this, SLOT(sendSnapNotification()));
    connect(this->snapNormalButton, SIGNAL(clicked()), this, SLOT(sendNormalSnapNotification()));
    connect(this->snapCriticalButton, SIGNAL(clicked()), this, SLOT(sendCriticalSnapNotification()));

    connect(m, SIGNAL(queueSizeChanged(int)), this, SLOT(queueSizeChanged(int)));

}

MainWindow::~MainWindow() {

}

void MainWindow::sendLowNotification() {
    QString text("low async number ");
    text += QString::number(notificationCount, 10);
    sendNotification(notificationOffset + notificationCount++, ASYNCHRONOUS, URGENCY_LOW, text);
}

void MainWindow::sendNormalNotification() {
    QString text("normal async number ");
    text += QString::number(notificationCount, 10);
    sendNotification(notificationOffset + notificationCount++, ASYNCHRONOUS, URGENCY_NORMAL, text);
}

void MainWindow::sendCriticalNotification() {
    QString text("critical async number ");
    text += QString::number(notificationCount, 10);
    sendNotification(notificationOffset + notificationCount++, ASYNCHRONOUS, URGENCY_CRITICAL, text);
}

void MainWindow::queueSizeChanged(int newsize) {
    QString text("Notifications in queue: ");
    text += QString::number(newsize, 10);
    queueLabel->setText(text);
}

void MainWindow::sendSynchronousNotification() {
    QString text("sync number ");
    text += QString::number(syncCount, 10);
    QSharedPointer<Notification> n(new Notification(syncOffset + syncCount++, URGENCY_LOW, text, SYNCHRONOUS));

    m->insertNotification(n); // Wrap in a try/catch eventually.
}

void MainWindow::sendLowInteractiveNotification() {
    QString text("low interactive number ");
    text += QString::number(interactiveCount, 10);
    sendNotification(interactiveOffset + interactiveCount++, INTERACTIVE, URGENCY_LOW, text);
}

void MainWindow::sendNormalInteractiveNotification() {
    QString text("normal interactive number ");
    text += QString::number(interactiveCount, 10);
    sendNotification(interactiveOffset + interactiveCount++, INTERACTIVE, URGENCY_NORMAL, text);
}

void MainWindow::sendCriticalInteractiveNotification() {
    QString text("critical interactive number ");
    text += QString::number(interactiveCount, 10);
    sendNotification(interactiveOffset + interactiveCount++, INTERACTIVE, URGENCY_CRITICAL, text);
}

void MainWindow::sendSnapNotification() {
    QString text("low snap number ");
    text += QString::number(snapCount, 10);
    sendNotification(snapOffset + snapCount++, SNAP, URGENCY_LOW, text);
}

void MainWindow::sendNormalSnapNotification() {
    QString text("normal snap number ");
    text += QString::number(snapCount, 10);
    sendNotification(snapOffset + snapCount++, SNAP, URGENCY_NORMAL, text);
}

void MainWindow::sendCriticalSnapNotification() {
    QString text("critical snap number ");
    text += QString::number(snapCount, 10);
    sendNotification(snapOffset + snapCount++, SNAP, URGENCY_CRITICAL, text);
}

void MainWindow::sendNotification(int id, NotificationType type, Urgency urg, QString text) const {
    QSharedPointer<Notification> n(new Notification(id, urg, text, type));
    m->insertNotification(n); // Wrap in a try/catch eventually.
}
