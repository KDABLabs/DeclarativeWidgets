Introduction
============
The KDAB DeclarativeWidgets software provides a library and tools for
creating QtWidget User Interfaces with QML.

Dependencies
============
DeclarativeWidgets requires Qt 5.11.0 or above.

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
There are three example applications that show how to use the DeclarativeWidgets QML module:
`bookstore`, `config-editor` and `text-editor`.

In addition, there are a number of example QML files in the `examples` directory. Run these by
passing the full path to one of the example files as the command line arguments to the `runner`
target in Qt Creator.

Contact
=======
* See our official KDAB page: https://www.kdab.com/declarative-widgets
* Visit us on GitHub: https://github.com/KDAB/DeclarativeWidgets
* Email info@kdab.com for questions about copyright, licensing or commercial support.

Get Involved
============
KDAB will happily accept external contributions, but substantial contributions require
a signed [Copyright Assignment Agreement](doc/DeclarativeWidgets-CopyrightAssignmentForm.docx)

Contact info@kdab.com for more information about the Copyright Assignment Agreement.

Please submit your contributions or issue reports from our GitHub space at
https://github.com/KDAB/DeclarativeWidgets

License
=======
The DeclarativeWidgets Library is (C) 2012-2021 Klarälvdalens Datakonsult AB (KDAB),
and is available under the terms of:

* the [GPL](LICENSE.GPL.txt)
* the KDAB commercial license, provided that you buy a license.
  please contact info@kdab.com if you are interested in buying commercial licenses.

Commercial licensing terms are available in the included file [LICENSE.txt](LICENSE.txt).

About KDAB
==========
The DeclarativeWidgets Library is supported and maintained by
Klarälvdalens Datakonsult AB (KDAB).

The KDAB Group is the global No.1 software consultancy for Qt, C++ and
OpenGL applications across desktop, embedded and mobile platforms.

The KDAB Group provides consulting and mentoring for developing Qt applications
from scratch and in porting from all popular and legacy frameworks to Qt.
We continue to help develop parts of Qt and are one of the major contributors
to the Qt Project. We can give advanced or standard trainings anywhere
around the globe on Qt as well as C++, OpenGL, 3D and more.

Please visit https://www.kdab.com to meet the people who write code like this.
