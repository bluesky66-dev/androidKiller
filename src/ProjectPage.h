#include <QFrame>

class QTextEdit;

class ProjectPage :public QFrame
{
	Q_OBJECT
public:
	ProjectPage(QWidget* parent = Q_NULLPTR);
public slots:
	void logOutPut(const QString& strlog);
private:
	QTextEdit* m_pLogWindow = Q_NULLPTR;
};