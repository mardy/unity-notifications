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

#include "notificationclient.h"
#include "notificationserver.h"
#include <QStringList>
#include <QDBusReply>

NotificationClient::NotificationClient(QObject *parent) : QObject(parent),
    service(DBUS_SERVICE_NAME, DBUS_PATH, DBUS_INTERFACE){

}

NotificationClient::~NotificationClient() {

}

unsigned int NotificationClient::sendNotification(NotificationType ntype, Urgency urg, QString text) {
    QString app_name("client test");
    unsigned int replaces_id = 0;
    QString app_icon;
    QString summary("summary");
    QStringList actions;
    Hints hints;
    QVariant tmp = 5;
    int timeout = 5000;
    QDBusReply<unsigned int> result = service.call("Notify", app_name, replaces_id, app_icon, summary, text, actions, tmp, timeout);
    if(!result.isValid()) {
        return 0;
    }
    return result.value();
/*
    QString app_name, int replaces_id, QString app_icon,
            QString summary, QString body,
            QStringList actions, Hints hints, int expire_timeout*/
}

void NotificationClient::NotificationClosed(unsigned int id, unsigned int reason) {
    printf("Got NotificationClosed signal for notification %d.\n", id);
}

void NotificationClient::ActionInvoked(unsigned int id, QString key) {
    printf("Got ActionInvoked signal for notification %d.\n", id);
}
