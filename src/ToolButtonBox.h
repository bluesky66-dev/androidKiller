#include <QFrame>
#include <ui_ToolButtonBox.h>
class ToolButtonBox :public QFrame
{
public:
	ToolButtonBox(QWidget* parent = Q_NULLPTR);
	void setText(QString strText);
private:
	Ui_ToolButtonBox m_Ui;
};