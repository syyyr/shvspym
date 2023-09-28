#include "application.h"
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QStandardItemModel>

int main(int argc, char *argv[])
{
	QCoreApplication::setOrganizationName("Elektroline");
	QCoreApplication::setOrganizationDomain("elektroline.cz");
	QCoreApplication::setApplicationName("shvspym");
	QCoreApplication::setApplicationVersion("0.0.1");

	Application app(argc, argv);

	QQmlApplicationEngine engine;
	QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed, &app, []() {
		QCoreApplication::exit(-1);
	},
	Qt::QueuedConnection);

	QStringList builtInStyles = {
		QLatin1String("Basic"),
		QLatin1String("Fusion"),
		QLatin1String("Imagine"),
		QLatin1String("Material"),
		QLatin1String("Universal")
	};
	engine.setInitialProperties({{ "builtInStyles", builtInStyles }});
	engine.rootContext()->setContextProperty("brokerListModel", app.brokerListModelObject());
	engine.loadFromModule("shvspymqml", "Main");

	return app.exec();
}
