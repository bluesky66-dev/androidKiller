#include <QApplication>
#include <src/MainWindow.h>
#include <QTextCodec>
#include <QSettings>
#include <src/Common.h>
#include "WorkSpaceSetting.h"

int main(int argc, char** argv)
{
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
	QApplication app(argc, argv);
	QCoreApplication::setOrganizationName("androidKiller");
	QCoreApplication::setOrganizationDomain("androidKiller.com");
	QCoreApplication::setApplicationName("androidKiller");
	QSettings setting;
	QString name = setting.fileName();
	if (getWorksSpacePath().isEmpty())
	{
		WorkSpaceSetting setting;
		if (setting.exec() == QDialog::Rejected)
		{
			return 0;
		}
		if (getWorksSpacePath().isEmpty())
		{
			return 0;
		}
	}

	MainWindow widget;
	widget.show();

	return app.exec();
}