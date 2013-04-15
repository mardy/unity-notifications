#include "notification.h"
#include "notificationmodel.h"

#include <QGuiApplication>
#include <QQmlEngine>
#include <QQmlContext>
#include <QQmlComponent>
#include <QQuickView>
#include <QTimer>

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);
    QQuickView view;


    QSharedPointer<Notification> msg(new Notification(55, URGENCY_CRITICAL, "default notification", ASYNCHRONOUS));
    QSharedPointer<Notification> msg2(new Notification(56, URGENCY_NORMAL, "default notification", ASYNCHRONOUS));
    QSharedPointer<Notification> msg3(new Notification(57, URGENCY_LOW, "default notification", ASYNCHRONOUS));
    NotificationModel *m = new NotificationModel();

    msg->setSummary("Foo bar");
    msg->setBody("Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua.");
    msg->setIcon("graphics/avatar1.jpg");
    msg->setSecondaryIcon("graphics/icon_phone.png");
    //msg->setUrgency(URGENCY_CRITICAL);
    //msg->setType(NotificationType type);
    //msg->setActions(QStringList actions);

    msg2->setSummary("Bla fasel");
    msg2->setBody("At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.");
    msg2->setIcon("graphics/avatar3.jpg");
    msg2->setSecondaryIcon("graphics/icon_phone.png");
    //msg2->setUrgency(URGENCY_NORMAL);
    //msg2->setType(NotificationType type);
    //msg2->setActions(QStringList actions);

    msg3->setSummary("Hacky jacky");
    msg3->setBody("Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.");
    msg3->setIcon("graphics/avatar2.jpg");
    msg3->setSecondaryIcon("graphics/facebook.png");
    //msg3->setUrgency(URGENCY_CRITICAL);
    //msg3->setType(NotificationType type);
    //msg3->setActions(QStringList actions);

    m->insertNotification(msg3);
    m->insertNotification(msg2);
    m->insertNotification(msg);
    printf("We have %d notifications in our model at the moment.\n", m->numNotifications());

    // Shared pointer problem: http://qt-project.org/wiki/SharedPointersAndQmlOwnership
    view.rootContext()->setContextProperty("notificationmodel", m);
    /* Hardcoded URLs are bad but tolerable here in test code. */
    view.setSource(QUrl::fromLocalFile("../tools/datatest.qml"));
    view.show();
    return app.exec();
}
