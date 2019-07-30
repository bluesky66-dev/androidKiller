#include "QMiniZip.h"
#include "./zlibMiniZip/unzip.h"
#include <QFile>
#include <QDir>


QMiniZip::QMiniZip(QObject* parent /*= Q_NULLPTR*/)
	:QObject(parent)
{

}

QStringList QMiniZip::extractFiles(QString zipFileName, QRegExp& regExp, QString outPutPath)
{
	unzFile zFile = unzOpen64(zipFileName.toStdString().c_str());
	unz_global_info64 gi;
	QStringList retFileList;
	if (unzGetGlobalInfo64(zFile, &gi) != UNZ_OK)
	{
		return retFileList;
	}
	for (int i = 0; i < gi.number_entry; ++i)
	{
		unz_file_info64 FileInfo;
		char file[256] = "";
		unzGetCurrentFileInfo64(zFile, &FileInfo, file, sizeof(file), NULL, 0, NULL, 0);
		if (isDir(file))
		{
			unzGoToNextFile(zFile);
			continue;
		}

		if (!regExp.exactMatch(file))
		{
			unzGoToNextFile(zFile);
			continue;
		}
		unzOpenCurrentFile(zFile);

		char data[1024] = { 0 };
		int size;
		QString path;
		if (isDir(outPutPath))
		{
			path = outPutPath + file;
		}
		else
		{
			path = outPutPath + "/" + file;
		}
		QFile f(path);
		f.open(QFile::WriteOnly);
		while (true)
		{
			size = unzReadCurrentFile(zFile, data, sizeof(data));
			if (size <= 0)
				break;
			f.write(data, size);
		}
		f.close();
		retFileList << file;
		unzCloseCurrentFile(zFile);
		unzGoToNextFile(zFile);
	}
	unzClose(zFile);
	return retFileList;
}

bool QMiniZip::isDir(QString fileName)
{
	if (fileName.isEmpty())
		return false;
	return fileName.back() == '/' || fileName.back() == '\\';
}

