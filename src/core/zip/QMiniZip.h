#include <QObject>
#include <QString>
#include <QRegExp>
#include <QStringList>

class QMiniZip :public QObject
{
public:
	QMiniZip(QObject* parent = Q_NULLPTR);
	QStringList extractFiles(QString zipFileName, QRegExp& regExp, QString outPutPath);
private:
	bool isDir(QString fileName);
};