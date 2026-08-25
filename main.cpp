#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "func_class.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    qmlRegisterType<Func_class>("MaKrodule", 1, 0, "Func_class");

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("MaKr0Hard_Planner_4", "Main");

    return QGuiApplication::exec();
}
