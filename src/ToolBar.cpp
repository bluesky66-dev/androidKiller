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
	addTab(m_pHomePage, QStringLiteral("��ҳ"));
	addTab(m_pToolPage, QStringLiteral("����"));
	addTab(m_pAndroidPage, QStringLiteral("��׿"));
	ToolButtonBox* pFileButton = new ToolButtonBox(this);
	pFileButton->setText(QStringLiteral("�ļ�"));
	m_pHomePage->addWidget(pFileButton);
	setStyleSheet(getFileContent("qss/toolBar.qss"));
}

