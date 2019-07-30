#include "ProjectPage.h"
#include <QSplitter>
#include <QHBoxLayout>
#include "ProJectInfoPage.h"
#include <QTextEdit>
#include <src/core/project/Project.h>
#include <3rd/Qsci/qsciscintilla.h>
#include <src/core/lexer/QsciLexerSmali.h>


ProjectPage::ProjectPage(QString fileName, QWidget* parent /*= Q_NULLPTR*/)
{
	m_pProject = new Project(fileName, this);
	QHBoxLayout* pLayout = new QHBoxLayout;
	setLayout(pLayout);
	QSplitter* pMainSplitter = new QSplitter(Qt::Orientation::Horizontal, this);
	ProjectInfoPage* pProjectInfoPage = new ProjectInfoPage(m_pProject, pMainSplitter);
	pMainSplitter->addWidget(pProjectInfoPage);
	pMainSplitter->setSizes(QList<int>() << 100 << 60);
	QSplitter* pShowInfoSplitter = new QSplitter(Qt::Orientation::Vertical, this);
	m_pFileWindow = new QsciScintilla(pShowInfoSplitter);
	QsciLexerSmali* smaliLexer = new QsciLexerSmali(m_pFileWindow);
	m_pFileWindow->setLexer(smaliLexer);
	m_pFileWindow->setMarginType(0, QsciScintilla::NumberMargin);
	m_pFileWindow->setMarginLineNumbers(0, true);
	m_pFileWindow->setMarginWidth(0, 30);
	m_pFileWindow->setUtf8(true);
	m_pFileWindow->setWrapMode(QsciScintilla::WrapMode::WrapWord);
	m_pFileWindow->setAutoCompletionSource(QsciScintilla::AcsAll);
	m_pFileWindow->setAutoCompletionThreshold(1);
	m_pFileWindow->setFolding(QsciScintilla::FoldStyle::PlainFoldStyle);
	
	pShowInfoSplitter->addWidget(m_pFileWindow);
	m_pLogWindow = new QTextEdit(pShowInfoSplitter);
	pShowInfoSplitter->addWidget(m_pLogWindow);
	pShowInfoSplitter->setStretchFactor(0, 3);
	pShowInfoSplitter->setStretchFactor(1, 1);
	pMainSplitter->addWidget(pShowInfoSplitter);
	pLayout->addWidget(pMainSplitter);
	connect(m_pProject, &Project::logOutPut, this, &ProjectPage::logOutPut);
	connect(pProjectInfoPage, &ProjectInfoPage::showSmaliFile, this, &ProjectPage::showSmaliFile);
}

void ProjectPage::start()
{
	m_pProject->start();
}

void ProjectPage::logOutPut(const QString& strlog)
{
	m_pLogWindow->insertPlainText(strlog);
}

void ProjectPage::showSmaliFile(QString smaliFilePath)
{
	QFile file(smaliFilePath);
	if (!file.open(QIODevice::ReadWrite))
	{
		return;
	}
	m_pFileWindow->setText(file.readAll());
}

