#include "ToolButtonBox.h"


ToolButtonBox::ToolButtonBox(QWidget* parent /*= Q_NULLPTR*/)
	:QFrame(parent)
{
	m_Ui.setupUi(this);
}

void ToolButtonBox::setText(QString strText)
{
	m_Ui.toolButtonBoxName->setText(strText);
}

