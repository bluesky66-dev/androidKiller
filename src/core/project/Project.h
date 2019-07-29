#include <QObject>
#include <QString>
#include <QProcess>

class Project :public QObject
{
	Q_OBJECT
signals:
	void logOutPut(const QString& strLog);
public:
	Project(QString strApkName, QObject* parent = Q_NULLPTR);
	void start();
	QString projectPath();
private slots:
	void startReadLog();

	void progcessFinished(int exitCode, QProcess::ExitStatus exitStatus);
private:
	void generator();
	void createProjectPath();
	void generatorSmali();
private:
	QString m_strApkFileName;
};