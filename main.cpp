#include <QGuiApplication>
#include <QQmlApplicationEngine>

#ifdef ANDROID
#include <QtCore/private/qandroidextras_p.h>

bool check_permission(QString p) {
  QStringList perms = p.split(";");
  for (QStringList::iterator it = perms.begin(); it != perms.end() ; ++it)
    {
        QString perm = *it;

        qDebug() << "checking permission for" << perm;
        QFuture<QtAndroidPrivate::PermissionResult> r = QtAndroidPrivate::checkPermission(perm);
        r.waitForFinished();
        if (r.result() == QtAndroidPrivate::PermissionResult::Denied) {
          qDebug() << "I do not have " << perm << " permission, requiring";
          r = QtAndroidPrivate::requestPermission(perm);
          r.waitForFinished();
          if (r.result() == QtAndroidPrivate::PermissionResult::Denied) {
            qDebug() << "Permission denied" << perm;
            return false;
          }
        }
        qDebug() << "Permissions granted!";
    }
  qDebug() << "End of permission check, shall return true";
  return true;
}
#endif

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
#ifdef ANDROID
    check_permission("android.permission.WRITE_EXTERNAL_STORAGE");
#endif
    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/untitled11/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
