#include "ToolPage.h"



ToolPage::ToolPage(QWidget* parent /*= Q_NULLPTR*/)
	:QFrame(parent)
{
	m_Ui.setupUi(this);
}

void ToolPage::addWidget(QWidget* pWidget)
{
	m_Ui.itemLayout->addWidget(pWidget);
}

