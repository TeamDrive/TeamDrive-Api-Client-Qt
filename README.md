TeamDrive Api Client for Qt
===========================

TeamDrive Api Client is a small demo app written in C++ using the Qt framework to jump start an application that uses the HTTP API of TeamDrive.

API Documentation
-----------------

The full TeamDrive Api documentation is available at [docs.teamdrive.net][documentation].

Requirements
------------

In order to run the demo, you will need the these requirements:

* TeamDrive Desktop Client or TeamDrive Agent
* TeamDrive [Python module and Command line interface][pythonInterface]
* Qt 5
* C++11
* *Python 3* in your PATH variable.
* Recommended: *docopt* for Python 3.

Getting Started
---------------

The TeamDrive Client API can be activated by entering the following text under the ```[Settings]``` section in the ```teamdrive.settings``` file.

On Linux and Mac, this file is located in your user directory ```/$HOME/.teamdrive/``` and on Windows in your ```%APPDATA%\TeamDrive3``` directory.

```
http-api-port=127.0.0.1:45454
```

Now, clone the repository and compile the demo:

```
git clone https://github.com/TeamDrive/TeamDrive-Api-Client-Qt
cd TeamDrive-Api-Client-Qt
qmake
make
```

You can now run the demo app:
```
./TeamDriveApiClientQt <TeamDrive-Installation-Path>/TeamDriveApi.py <Your-TeamDrive-Username> <Your-TeamDrive-Password> "127.0.0.1:45454"
```

[documentation]: http://docs.teamdrive.net/Agent/4.1/html/TeamDrive_Http_Api.html "docs.teamdrive.net"
[pythonInterface]: http://docs.teamdrive.net/Agent/4.1/html/TeamDrive_Http_Api.html#requirements "Python module and Command line interface"


