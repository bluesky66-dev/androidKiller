#include "ContentBar.h"
#include <src/StartPage.h>

ContentBar::ContentBar(QWidget* parent /*= Q_NULLPTR*/)
	:QTabWidget(parent)
{
	addTab(new StartPage(this), QStringLiteral("¿ªÊ¼"));
}

