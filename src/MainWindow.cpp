#include "MainWindow.h"
#include <src/ContentBar.h>
#include <src/ToolBar.h>
#include <QDragEnterEvent>
#include <QDebug>
#include <QMimeData>
#include <QFileInfo>
#include "ProjectPage.h"
#include <src/core/project/Project.h>

MainWindow::MainWindow()
{
	m_Ui.setupUi(this);
	m_pContentBar = new ContentBar(this);
	m_pToolBar = new ToolBar(this);
	QWidget* pWidget = centralWidget();
	pWidget->layout()->addWidget(m_pToolBar);
	pWidget->layout()->addWidget(m_pContentBar);
	setAcceptDrops(true);
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
	if (event->mimeData()->hasFormat("text/uri-list"))
	{
		QList<QUrl> urls = event->mimeData()->urls();
		if (urls.isEmpty())
			return;
		foreach(QUrl url, urls) 
		{
			QString file_name = url.toLocalFile();
			QFileInfo fi(file_name);
			if (fi.suffix() != "apk")
				return;
		}
		event->acceptProposedAction();
	}
		
}

void MainWindow::dropEvent(QDropEvent *event)
{
	QList<QUrl> urls = event->mimeData()->urls();
	if (urls.isEmpty())
		return;
	foreach(QUrl url, urls)
	{
		QString file_name = url.toLocalFile();
		QFileInfo fi(file_name);
		ProjectPage* pProjectPage = new ProjectPage(this);
		m_pContentBar->addTab(pProjectPage, fi.fileName());
		m_pContentBar->setCurrentIndex(m_pContentBar->count() - 1);
		Project* pProject = new Project(file_name, pProjectPage);
		connect(pProject, &Project::logOutPut, pProjectPage, &ProjectPage::logOutPut);
		pProject->start();
	}
}

