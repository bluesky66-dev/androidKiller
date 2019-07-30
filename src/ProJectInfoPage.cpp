#include "ProJectInfoPage.h"
#include <src/core/project/Project.h>
#include <QVBoxLayout>


ProjectInfoPage::ProjectInfoPage(Project* pProject, QWidget* parent /*= Q_NULLPTR*/)
	:m_pProject(pProject), QFrame(parent)
{
	connect(m_pProject, &Project::finished, this, &ProjectInfoPage::projectLoadDone);
	QVBoxLayout* pLayout = new QVBoxLayout(this);
	setLayout(pLayout);
	m_pFileModel = new QFileSystemModel(this);
	m_pTreeView = new QTreeView(this);
	m_pTreeView->setModel(m_pFileModel);
	m_pTreeView->setColumnHidden(1, true);
	m_pTreeView->setColumnHidden(2, true);
	m_pTreeView->setColumnHidden(3, true);
	layout()->addWidget(m_pTreeView);
	connect(m_pTreeView, &QTreeView::doubleClicked, this, &ProjectInfoPage::showFileItem);
}

void ProjectInfoPage::projectLoadDone()
{
	m_pTreeView->setRootIndex(m_pFileModel->setRootPath(m_pProject->smaliPath()));
}

void ProjectInfoPage::showFileItem(const QModelIndex &index)
{
	if (m_pFileModel->isDir(index))
		return;
	QFileInfo fileInfo = m_pFileModel->fileInfo(index);
	QRegExp regexp(".+(\\.smali)$");
	if (regexp.exactMatch(fileInfo.fileName()))
	{
		showSmaliFile(fileInfo.filePath());
		return;
	}
}

