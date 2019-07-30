#include <QFrame>
#include <QFileSystemModel>
#include <QTreeView>
class Project;

class ProjectInfoPage :public QFrame
{
	Q_OBJECT
signals:
	void showSmaliFile(QString smaliFilePath);
public:
	ProjectInfoPage(Project* pProject, QWidget* parent = Q_NULLPTR);
public slots:
	void projectLoadDone();

	void showFileItem(const QModelIndex &index);
private:
	Project* m_pProject = Q_NULLPTR;
	QFileSystemModel* m_pFileModel = Q_NULLPTR;
	QTreeView* m_pTreeView = Q_NULLPTR;
};