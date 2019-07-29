#include "ToolBar.h"
#include "ToolPage.h"
#include "Common.h"
#include "ToolButtonBox.h"

ToolBar::ToolBar(QWidget* parent /*= Q_NULLPTR*/)
	:QTabWidget(parent)
{
	setObjectName("toolBar");
	m_pHomePage = new ToolPage(this);
	m_pToolPage = new ToolPage(this);
	m_pAndroidPage = new ToolPage(this);
	addTab(m_pHomePage, QStringLiteral("主页"));
	addTab(m_pToolPage, QStringLiteral("工具"));
	addTab(m_pAndroidPage, QStringLiteral("安卓"));
	ToolButtonBox* pFileButton = new ToolButtonBox(this);
	pFileButton->setText(QStringLiteral("文件"));
	m_pHomePage->addWidget(pFileButton);
	setStyleSheet(getFileContent("qss/toolBar.qss"));
}

