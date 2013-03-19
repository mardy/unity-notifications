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

#include "notificationmodel.h"
#include "notification.hpp"
#include<QTimer>

NotificationModel::NotificationModel(QObject *parent) : QAbstractListModel(parent) {
}

NotificationModel::~NotificationModel() {
    for(int i=0; i<notifications.size(); i++)
        delete notifications[i];
    notifications.clear();
}

int NotificationModel::rowCount(const QModelIndex &parent) const {
    //printf("Count %d\n", notifications.size());
    return notifications.size();
}

QVariant NotificationModel::data(const QModelIndex &parent, int role) const {
    //printf("Data %d.\n", parent.row());
    if (!parent.isValid())
            return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();
    return QVariant(notifications[parent.row()]->getText());
}

void NotificationModel::testInsert(QString text) {
    QModelIndex insertionPoint = QAbstractItemModel::createIndex(0, 0);
    beginInsertRows(insertionPoint, 0, 0);
    notifications.push_front(new Notification(55, URGENCY_LOW, text));
    endInsertRows();
    QTimer::singleShot(5000, this, SLOT(testDelete()));
}

void NotificationModel::testDelete() {
    if(notifications.empty())
        return;
    int loc = notifications.size()-1;
    QModelIndex deletePoint = QAbstractItemModel::createIndex(loc, 0);
    beginRemoveRows(deletePoint, loc, loc);
    delete notifications[loc];
    notifications.pop_back();
    endRemoveRows();
}
