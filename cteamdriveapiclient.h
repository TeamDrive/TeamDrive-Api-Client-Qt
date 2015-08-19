/**************************************************
**
** Copyright (c) 2015 TeamDrive Systems GmbH
**
** See the file LICENSE for copying permission.
**
***************************************************/

#ifndef CTEAMDRIVEAPICLIENT_H
#define CTEAMDRIVEAPICLIENT_H

#include <QObject>
#include <QJsonDocument>

class CTeamDriveApiClient : public QObject
{
	Q_OBJECT

public:
	CTeamDriveApiClient(const QString& pythonApi, const QString& username, const QString& password, const QString& server, QObject *parent = 0);
	CTeamDriveApiClient(const QString& username, const QString& password, const QString& server, QObject *parent = 0);
	QJsonDocument exec(const QStringList& args);

	void serverSideEvents();

	QJsonDocument getSpaceIds();
	QJsonDocument getSpace(int id);

	// TODO:
	// QJsonDocument createFolder(int spaceId, const QString filePath, bool thrashed);
	// QJsonDocument login(const QString& username, const QString& password);
	// etc. pp.

signals:
	void newEvent(QJsonDocument event);

private:
	QString m_PythonApi;
	QString m_Username;
	QString m_Password;
	QString m_Server;
};

#endif // CTEAMDRIVEAPICLIENT_H

