#include "Project.h"
#include <src/Common.h>
#include <QFileInfo>
#include <QDir>
#include <src/core/zip/QMiniZip.h>

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
	switch (m_nCurrentOrder)
	{
		case Project::Idle:
			break;
		case Project::Generator_ProjectPath_Start:
			break;
		case Project::Generator_JarFile_Start:
			if (m_nCurrentDexIndex == m_listDexFile.count() - 1)
			{
				logOutPut(QStringLiteral("生成jar成功\n"));
				generatorSmali();
				break;
			}
			m_nCurrentDexIndex++;
			logOutPut(QStringLiteral("正在生成jar包:%1\n").arg(m_listDexFile[m_nCurrentDexIndex]));
			startExecCommand(getResPath("tools/dex-tools-2.1-SNAPSHOT/d2j-dex2jar.bat"),
				QStringList() << (getJarFilePath() + "/" + m_listDexFile[m_nCurrentDexIndex]), getJarFilePath());
			break;
		case Project::Generator_Smali_Start:
			logOutPut(QStringLiteral("反编译apk包成功\n"));
			break;
		default:
			break;
	}
}

void Project::generator()
{
	createProjectPath();
	generatorJarFile();
}

void Project::createProjectPath()
{
	m_nCurrentOrder = Generator_ProjectPath_Start;
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
	m_nCurrentOrder = Generator_Smali_Start;
	logOutPut(QStringLiteral("开始反编译apk包\n"));
	startExecCommand(getResPath("tools/apktool/apktool.bat"), 
		QStringList() << "d" << m_strApkFileName << "-o" << "smali", projectPath());
}

void Project::generatorJarFile()
{
	m_nCurrentOrder = Generator_JarFile_Start;
	logOutPut(QStringLiteral("开始生成jar包\n"));
	QString jarFilePath = getJarFilePath();
	QDir dir(jarFilePath);
	if (!dir.exists())
	{
		dir.mkpath(jarFilePath);
	}

	QMiniZip miniZip;
	m_listDexFile = miniZip.extractFiles(m_strApkFileName, QRegExp(".+(.dex)$"), jarFilePath);
	if (m_listDexFile.isEmpty())
		return;

	m_nCurrentDexIndex = 0;
	logOutPut(QStringLiteral("正在生成jar包:%1\n").arg(m_listDexFile[m_nCurrentDexIndex]));
	startExecCommand(getResPath("tools/dex-tools-2.1-SNAPSHOT/d2j-dex2jar.bat"),
		QStringList() << (jarFilePath + "/" + m_listDexFile[m_nCurrentDexIndex]), jarFilePath);

	
}

void Project::startExecCommand(QString program, QStringList& arguments, QString workingDirectory)
{
	QProcess* pProcess = new QProcess(this);
	pProcess->setWorkingDirectory(workingDirectory);
	pProcess->start(program, arguments);
	connect(pProcess, &QProcess::readyReadStandardOutput, this, &Project::startReadLog);
	connect(pProcess, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(progcessFinished(int, QProcess::ExitStatus)));
}

QString Project::getJarFilePath()
{
	return projectPath() + "/jar";
}

