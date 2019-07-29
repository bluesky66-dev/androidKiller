#include "WorkSpaceSetting.h"
#include <QApplication>
#include <QFileDialog>
#include <QMessageBox>
#include <QCloseEvent>
#include "Common.h"

WorkSpaceSetting::WorkSpaceSetting(QWidget* parent /*= Q_NULLPTR*/)
	:QDialog(parent)
{
	m_Ui.setupUi(this);
	setModal(true);
	m_Ui.lineEdit->setText(qApp->applicationDirPath() + "/workspace");
	connect(m_Ui.pushButton, &QPushButton::clicked, this, &WorkSpaceSetting::selectDir);
}

void WorkSpaceSetting::selectDir()
{
	QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), qApp->applicationDirPath(),
		QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
	m_Ui.lineEdit->setText(dir);
	
}
void WorkSpaceSetting::accept()
{
	QString strWorkspace = m_Ui.lineEdit->text();
	if (strWorkspace.isEmpty())
	{
		QMessageBox::warning(this, "androidKiller", QStringLiteral("不能设置空的文件夹"));
		return;
	}
	setWorkSpacePath(strWorkspace);
	__super::accept();
}

