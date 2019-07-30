#include <QFrame>
#include <QPlainTextEdit>
class QTextEdit;
class Project;
class QsciScintilla;
class ProjectPage :public QFrame
{
	Q_OBJECT
public:
	ProjectPage(QString fileName, QWidget* parent = Q_NULLPTR);
	void start();
public slots:
	void logOutPut(const QString& strlog);
	void showSmaliFile(QString smaliFilePath);
private:
	QTextEdit* m_pLogWindow = Q_NULLPTR;
	Project* m_pProject = Q_NULLPTR;
	QsciScintilla* m_pFileWindow = Q_NULLPTR;
};