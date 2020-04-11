/*
 * This file was generated by qdbusxml2cpp version 0.8
 * Command line was: qdbusxml2cpp -a notifications_adaptor.h: ../../../theDesk/plugins/NotificationsPlugin/dbus/org.freedesktop.Notifications.xml
 *
 * qdbusxml2cpp is Copyright (C) 2020 The Qt Company Ltd.
 *
 * This is an auto-generated file.
 * This file may have been hand-edited. Look for HAND-EDIT comments
 * before re-generating it.
 */

#ifndef NOTIFICATIONS_ADAPTOR_H
#define NOTIFICATIONS_ADAPTOR_H

#include <QtCore/QObject>
#include <QtDBus/QtDBus>
QT_BEGIN_NAMESPACE
class QByteArray;
template<class T> class QList;
template<class Key, class Value> class QMap;
class QString;
class QStringList;
class QVariant;
QT_END_NAMESPACE

/*
 * Adaptor class for interface org.freedesktop.Notifications
 */
class NotificationsAdaptor: public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.freedesktop.Notifications")
    Q_CLASSINFO("D-Bus Introspection", ""
"  <interface name=\"org.freedesktop.Notifications\">\n"
"    <signal name=\"NotificationClosed\">\n"
"      <arg direction=\"out\" type=\"u\" name=\"id\"/>\n"
"      <arg direction=\"out\" type=\"u\" name=\"reason\"/>\n"
"    </signal>\n"
"    <signal name=\"ActionInvoked\">\n"
"      <arg direction=\"out\" type=\"u\" name=\"id\"/>\n"
"      <arg direction=\"out\" type=\"s\" name=\"actionKey\"/>\n"
"    </signal>\n"
"    <method name=\"GetCapabilities\">\n"
"      <arg direction=\"out\" type=\"as\"/>\n"
"    </method>\n"
"    <method name=\"Notify\">\n"
"      <arg direction=\"out\" type=\"u\"/>\n"
"      <arg direction=\"in\" type=\"s\" name=\"appName\"/>\n"
"      <arg direction=\"in\" type=\"u\" name=\"replacesId\"/>\n"
"      <arg direction=\"in\" type=\"s\" name=\"appIcon\"/>\n"
"      <arg direction=\"in\" type=\"s\" name=\"summary\"/>\n"
"      <arg direction=\"in\" type=\"s\" name=\"body\"/>\n"
"      <arg direction=\"in\" type=\"as\" name=\"actions\"/>\n"
"      <arg direction=\"in\" type=\"a{sv}\" name=\"hints\"/>\n"
"      <annotation value=\"QVariantMap\" name=\"org.qtproject.QtDBus.QtTypeName.In6\"/>\n"
"      <arg direction=\"in\" type=\"i\" name=\"expireTimeout\"/>\n"
"    </method>\n"
"    <method name=\"CloseNotification\">\n"
"      <arg direction=\"in\" type=\"u\" name=\"id\"/>\n"
"    </method>\n"
"    <method name=\"GetServerInformation\">\n"
"      <arg direction=\"out\" type=\"s\"/>\n"
"      <arg direction=\"out\" type=\"s\" name=\"vendor\"/>\n"
"      <arg direction=\"out\" type=\"s\" name=\"version\"/>\n"
"      <arg direction=\"out\" type=\"s\" name=\"specVersion\"/>\n"
"    </method>\n"
"  </interface>\n"
        "")
public:
    NotificationsAdaptor(QObject *parent);
    virtual ~NotificationsAdaptor();

public: // PROPERTIES
public Q_SLOTS: // METHODS
    void CloseNotification(uint id);
    QStringList GetCapabilities();
    QString GetServerInformation(QString &vendor, QString &version, QString &specVersion);
    uint Notify(const QString &appName, uint replacesId, const QString &appIcon, const QString &summary, const QString &body, const QStringList &actions, const QVariantMap &hints, int expireTimeout);
Q_SIGNALS: // SIGNALS
    void ActionInvoked(uint id, const QString &actionKey);
    void NotificationClosed(uint id, uint reason);
};

#endif
