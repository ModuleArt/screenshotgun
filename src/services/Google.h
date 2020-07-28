#pragma once

#include "../Settings.h"
#include "ServiceHelper.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>

class App;

class Google : public QObject {
    Q_OBJECT

public:
    explicit Google(App&);
    void setToken(QString);
    void upload(const QByteArray&);
    void getFolder();

signals:
    void uploadSuccess(QString);
    void uploadError(QString);
    void refreshToken(UploadService);

private slots:
    void uploadReply(QNetworkReply*);
    void shareReply(QNetworkReply*);
    void getFolderReply(QNetworkReply*);
    void createFolderReply(QNetworkReply*);
    void reupload();

private:
    void createFolder();
    App& app_;
    QString token_;
    QNetworkAccessManager manager_;
    QString filename_;
    ServiceHelper helper_;
    QString uploadLink_;
    QByteArray image_;
    bool needReupload_;
};
