#include "QMiniZip.h"
#include "unzip.h"
#include <winnt.h>

QMiniZip::QMiniZip(QObject* parent /*= Q_NULLPTR*/)
{
	unz_file_info64 FileInfo;
	unzFile zFile = unzOpen64("d:/biji.zip");
	if (NULL == zFile)
		qDebug() << "zero!";
	else
		qDebug() << "haha";

	unz_global_info64 gi;

	if (unzGetGlobalInfo64(zFile, &gi) != UNZ_OK)
	{
		qDebug() << "ho no";
	}

	int result;
	for (int i = 0; i < gi.number_entry; ++i)
	{
		char file[256] = { 0 };
		char ext[256] = { 0 };

		char com[1024] = { 0 };
		if (unzGetCurrentFileInfo64(zFile, &FileInfo, file, sizeof(file), ext, 256, com, 1024) != UNZ_OK)
			qDebug() << "error";
		qDebug() << file << ":" << ext << ":" << com;



		if (!(FileInfo.external_fa & FILE_ATTRIBUTE_DIRECTORY)) //文件，否则为目录

		//打开文件
			result = unzOpenCurrentFile(zFile);/* 无密码 */
		result = unzOpenCurrentFilePassword(zFile, "szPassword"); /* 有密码 */

		char data[1024] = { 0 };
		int size;
		//读取内容

		QString path = QString("d:/zip/") + file;
		QFile f(path);
		f.open(QFile::WriteOnly);
		while (true) {
			size = unzReadCurrentFile(zFile, data, sizeof(data));
			if (size <= 0)
				break;

			//            QString str;
			//            str = QString::fromLocal8Bit(data, size);
			f.write(data, size);
		}
		f.close();

		//关闭当前文件
		unzCloseCurrentFile(zFile);

		//出错
		if (i < gi.number_entry - 1 && unzGoToNextFile(zFile) != UNZ_OK)
			qDebug() << "error2";
	}
	unzClose(zFile);
}

