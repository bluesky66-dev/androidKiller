#include <QMainWindow>
#include <ui_MainWindow.h>

class ContentBar;
class ToolBar;

class MainWindow :public QMainWindow
{
public:
	MainWindow();
protected:
	void dragEnterEvent(QDragEnterEvent *event) override;
	void dropEvent(QDropEvent *event) override;
private:
	Ui_MainWindow m_Ui;
	ContentBar* m_pContentBar = Q_NULLPTR;
	ToolBar* m_pToolBar = Q_NULLPTR;
};