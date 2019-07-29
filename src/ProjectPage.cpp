#include "ProjectPage.h"
#include <QSplitter>
#include <QHBoxLayout>
#include "ProJectInfoPage.h"
#include <QTextEdit>
#include <QPlainTextEdit>

ProjectPage::ProjectPage(QWidget* parent /*= Q_NULLPTR*/)
{
	QHBoxLayout* pLayout = new QHBoxLayout;
	setLayout(pLayout);
	QSplitter* pMainSplitter = new QSplitter(Qt::Orientation::Horizontal, this);
	pMainSplitter->addWidget(new ProjectInfoPage);
	pMainSplitter->setSizes(QList<int>() << 100 << 60);
	QSplitter* pShowInfoSplitter = new QSplitter(Qt::Orientation::Vertical, this);
	pShowInfoSplitter->addWidget(new QPlainTextEdit);
	m_pLogWindow = new QTextEdit(pShowInfoSplitter);
	pShowInfoSplitter->addWidget(m_pLogWindow);
	pShowInfoSplitter->setStretchFactor(0, 3);
	pShowInfoSplitter->setStretchFactor(1, 1);
	pMainSplitter->addWidget(pShowInfoSplitter);
	pLayout->addWidget(pMainSplitter);
}

void ProjectPage::logOutPut(const QString& strlog)
{
	m_pLogWindow->insertPlainText(strlog);
}

