#include <QTabWidget>

class ToolPage;


class ToolBar :public QTabWidget
{
public:
	ToolBar(QWidget* parent = Q_NULLPTR);
private:
	ToolPage* m_pHomePage = Q_NULLPTR;
	ToolPage* m_pToolPage = Q_NULLPTR;
	ToolPage* m_pAndroidPage = Q_NULLPTR;
};