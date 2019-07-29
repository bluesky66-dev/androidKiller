#include <QFrame>
#include <ui_ToolPage.h>

class ToolPage :public QFrame
{
public:
	ToolPage(QWidget* parent = Q_NULLPTR);
public:
	void addWidget(QWidget* pWidget);
private:
	Ui_ToolPage m_Ui;
};