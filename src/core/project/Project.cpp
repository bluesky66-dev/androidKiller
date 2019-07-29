#include "Project.h"
#include <src/Common.h>
#include <QFileInfo>
#include <QDir>


Project::Project(QString strApkName, QObject* parent /*= Q_NULLPTR*/)
	:m_strApkFileName(strApkName), QObject(parent)
{

}

void Project::start()
{
	generator();
}

QString Project::projectPath()
{
	QFileInfo fi(m_strApkFileName);
	return getWorksSpacePath() + "/" + fi.fileName();
}

void Project::startReadLog()
{
	QProcess* pProcess = dynamic_cast<QProcess*>(sender());
	if (pProcess)
	{
		logOutPut(pProcess->readLine());
	}
}

void Project::progcessFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
	sender()->deleteLater();
}

void Project::generator()
{
	createProjectPath();
	generatorSmali();
	

}

void Project::createProjectPath()
{
	QString strProjectPath = projectPath();
	QDir pathDir(strProjectPath);
	if (pathDir.exists())
	{
		return;
	}
	pathDir.mkpath(strProjectPath);
}

void Project::generatorSmali()
{
	QProcess* pProcess = new QProcess(this);
	pProcess->setWorkingDirectory(projectPath());
	pProcess->start(getResPath("tools/apktool/apktool.bat"), QStringList() << "d" << m_strApkFileName << "-o" << "smali");
	connect(pProcess, &QProcess::readyReadStandardOutput, this, &Project::startReadLog);
	connect(pProcess,SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(progcessFinished(int, QProcess::ExitStatus)));
}

