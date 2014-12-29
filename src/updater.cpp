#include <QFileInfo>
#include <QDebug>
#include <QProcess>
#include <QApplication>
#include "updater.h"
#include "const.h"

Updater::Updater()
{
}

Updater::~Updater()
{
}

void Updater::update(const QByteArray &file)
{
    QFile tempFile(QApplication::applicationDirPath() + "/" + TMP_BIN_FILENAME);

    tempFile.open(QIODevice::WriteOnly);
    tempFile.write(file);
    tempFile.close();
    tempFile.setPermissions(QFile::ReadOwner|QFile::WriteOwner|QFile::ExeOwner|QFile::ReadGroup|QFile::ExeGroup|QFile::ReadOther|QFile::ExeOther);

    QStringList args;
    args.append("--update");
    args.append(QApplication::applicationFilePath());

    QProcess::startDetached(tempFile.fileName(), args);
    exit(12);
}

void Updater::copyNew(const QString& path)
{
    QFile currentFile(QApplication::applicationFilePath());
    QFile oldFile(path);
    oldFile.remove();

    if (!currentFile.copy(path)) {
        qDebug() << "Can't copy new version";
        exit(1);
    }

    QProcess::startDetached(path);
    exit(12);
}
