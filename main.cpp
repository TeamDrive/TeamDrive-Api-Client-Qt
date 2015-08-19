/**************************************************
**
** Copyright (c) 2015 TeamDrive Systems GmbH
**
** See the file LICENSE for copying permission.
**
***************************************************/

#include <QCoreApplication>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonArray>

#include "cteamdriveapiclient.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	if (a.arguments().size() != 5) {
		qDebug() << QString("Usage: %1 <path-to-TeamDriveApi.py> <username> <password> <server>").arg(a.arguments().first());
		return 1;
	}

	CTeamDriveApiClient api(a.arguments()[1], a.arguments()[2], a.arguments()[3], a.arguments()[4]);
	QJsonArray spaceIds = api.getSpaceIds().array();
	if (!spaceIds.isEmpty()) {
		qDebug() << spaceIds;
		qDebug() << api.getSpace(spaceIds.first().toInt());
	}


	QObject::connect(&api, &CTeamDriveApiClient::newEvent, [](QJsonDocument event){
		qDebug() << "new event: " << event;
	});
	api.serverSideEvents();

	return a.exec();
}
