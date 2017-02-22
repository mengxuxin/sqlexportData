#include <QCoreApplication>
#include <QFileInfoList>
#include <QFileInfo>
#include <QDir>
#include <QVariantMap>
#include "DBUtil.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


         QDir dir;
         dir.setPath(QDir::currentPath() + "/peoples");

         QFileInfoList filter = dir.entryInfoList(QDir::NoFilter, QDir::NoSort);
         for (QFileInfo& info : filter)
         {
             if (!info.suffix().isEmpty())
             {
                 QFile file(info.absoluteFilePath());
                 file.open(QIODevice::ReadOnly);
                 QByteArray ba = file.readAll();
                 QString strName = info.baseName();

                 file.close();

                 QVariantMap params;
                 params["name"] = strName;
                 params["picture"] = ba;
                 params["bLottery"]  = 0;
                 DBUtil::instance()->insert("INSERT INTO Users (username, picture, bLottery) VALUES (:name, :picture, :bLottery)", params);
             }
         }
		 qDebug() << "export ok;";

    return 0;
}
