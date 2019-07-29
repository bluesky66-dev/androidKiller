#include <QDialog>
#include <ui_WorkSpaceSetting.h>


class WorkSpaceSetting :public QDialog
{
	Q_OBJECT
public:
	WorkSpaceSetting(QWidget* parent = Q_NULLPTR);
public slots:
	void selectDir();
	virtual void accept() override;
private:
	Ui_WorkSpaceSetting m_Ui;
};