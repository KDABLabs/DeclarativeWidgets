Introduction
============
The KDAB DeclarativeWidgets software provides a library and tools for
creating QtWidget User Interfaces with QML.

Dependencies
============
DeclarativeWidgets depends features currently in the dev branch. To use
DeclarativeWidgets you will need to build [qtbase][1] and [qtdeclarative][2]
from the dev branch. If you wish to use [Qt WebEngine Widgets][3] you will need
to build [qtwebengine][4] and its dependencies as well.

[1]: https://codereview.qt-project.org/#/admin/projects/qt/qtbase
[2]: https://codereview.qt-project.org/#/admin/projects/qt/qtdeclarative
[3]: http://doc.qt.io/qt-5/qtwebenginewidgets-index.html
[4]: https://codereview.qt-project.org/#/admin/projects/qt/qtwebengine

Building and running
====================
Build:

    $ mkdir build
    $ cd build
    $ qmake -r ../declarativewidgets.pro
    $ make or nmake (or jom)

Install:

    $ make install #into your Qt5 installation. you may need to use sudo

How to Use
==========
Look at the sample QML under the examples subdirectory.

Contributing
============
KDAB will happily accept external contributions, but substantial
contributions will require a signed Copyright Assignment Agreement.
Contact info@kdab.com for more information.

Licensing
=========
The DeclarativeWidgets Library is (C) 2012-2020 Klarälvdalens Datakonsult AB (KDAB),
and is available under the terms of the GPL version 2 (or any later version,
at your option).  See LICENSE.GPL.txt for license details.

Commercial use is also permitted as described in ReadMe-commercial.txt.

About KDAB
==========
This DeclarativeWidgets Library is supported and maintained by
Klarälvdalens Datakonsult AB (KDAB).

KDAB, the Qt experts, provide consulting and mentoring for developing
Qt applications from scratch and in porting from all popular and legacy
frameworks to Qt. We continue to help develop parts of Qt and are one
of the major contributors to the Qt Project. We can give advanced or
standard trainings anywhere around the globe.

Please visit http://www.kdab.com to meet the people who write code like this.
