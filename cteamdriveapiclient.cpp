/**************************************************
**
** Copyright (c) 2015 TeamDrive Systems GmbH
**
** See the file LICENSE for copying permission.
**
***************************************************/

#include "cteamdriveapiclient.h"

#include <QProcess>
#include <QDebug>
#include <QThread>

CTeamDriveApiClient::CTeamDriveApiClient(const QString& pythonApi, const QString& username, const QString& password, const QString& server, QObject *parent) :
	QObject(parent),
	m_PythonApi(pythonApi),
	m_Username(username),
	m_Password(password),
	m_Server(server)
{
}

CTeamDriveApiClient::CTeamDriveApiClient(const QString& username, const QString& password, const QString& server, QObject *parent) :
	QObject(parent),
	m_PythonApi("TeamDriveApi.py"),
	m_Username(username),
	m_Password(password),
	m_Server(server)
{
}

QJsonDocument CTeamDriveApiClient::exec(const QStringList& args)
{
	QProcess p;
	QStringList arguments = QStringList() << m_PythonApi << m_Server << "--user" << m_Username << "--pass" << m_Password << args;

	p.start("python3", arguments);
	p.waitForFinished();

	QByteArray stdout = p.readAllStandardOutput().trimmed();
	QByteArray stderr = p.readAllStandardError();
	if (!stderr.isEmpty())
		qDebug() << stderr;

	QJsonParseError e;
	QJsonDocument d = QJsonDocument::fromJson(stdout, &e);
	if (e.error != QJsonParseError::NoError)
		qDebug() << e.errorString();
	return d;
}

QJsonDocument CTeamDriveApiClient::getSpaceIds()
{
	return exec(QStringList() << "getSpaceIds");
}

QJsonDocument CTeamDriveApiClient::getSpace(int id)
{
	return exec(QStringList() << "getSpace" << QString::number(id));
}

void CTeamDriveApiClient::serverSideEvents()
{
	QProcess *p = new QProcess(this);

	p->setReadChannel(QProcess::StandardOutput);
	connect(p, &QProcess::readyRead, [this, p](){
		if (p->canReadLine()) {
			QString line = p->readLine();
			if (!line.isEmpty() && line.startsWith("data: ")) {
				QJsonParseError e;
				QJsonDocument d = QJsonDocument::fromJson(line.mid(6).toUtf8(), &e);
				if (e.error != QJsonParseError::NoError)
					qDebug() << e.errorString();
				emit newEvent(d);
			}
		}
	});
	connect(p, &QProcess::readyReadStandardError, [this, p](){
		qDebug() << "/sse error:" << p->readAllStandardError();
	});

	QStringList arguments = QStringList() << m_PythonApi << m_Server << "--user" << m_Username << "--pass" << m_Password << "sse";
	p->start("python3", arguments);
}
