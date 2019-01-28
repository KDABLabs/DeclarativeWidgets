/*
  main.cpp

  This file is part of DeclarativeWidgets, library and tools for creating QtWidget UIs with QML.

  Copyright (C) 2013-2019 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Kevin Krammer <kevin.krammer@kdab.com>

  Licensees holding valid commercial KDAB DeclarativeWidgets licenses may use this file in
  accordance with DeclarativeWidgets Commercial License Agreement provided with the Software.

  Contact info@kdab.com if any conditions of this licensing are not clear to you.

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "parser.h"

#include <QFile>
#include <QString>

#include <cstdio>
#include <iostream>

#include "buddyvisitor.h"
#include "connectionnodevisitor.h"
#include "elementnamevisitor.h"
#include "fontproperyvisitor.h"
#include "idvisitor.h"
#include "itemvisitor.h"
#include "layoutvisitor.h"
#include "qmlwriter.h"
#include "tabstopsnodevisitor.h"
#include "uitopnode.h"

using namespace std;

void printUsage()
{
  cout << "Usage: ui2dw [ -o <outputfile> ] inputfile" << endl;
}

int main(int argc, char *argv[])
{
  if (argc < 2) {
    cerr << "Too few arguments" << endl;
    printUsage();
    return 1;
  }

  if (argc > 4) {
    cerr << "Too many arguments" << endl;
    printUsage();
    return 1;
  }

  QString inputFileName;
  QString outputFileName;
  if (argc == 2) {
    inputFileName = QString::fromLocal8Bit(argv[1]);
  } else {
    if (qstrncmp(argv[1], "-o", 2) == 0) {
      inputFileName = QString::fromLocal8Bit(argv[3]);
      outputFileName = QString::fromLocal8Bit(argv[2]);
    } else if (qstrncmp(argv[2], "-o", 2) == 0) {
      inputFileName = QString::fromLocal8Bit(argv[1]);
      outputFileName = QString::fromLocal8Bit(argv[3]);
    } else {
      cerr << "Invalid usage" << endl;
      printUsage();
      return 2;
    }
  }

  QFile inputFile(inputFileName);
  if (!inputFile.open(QIODevice::ReadOnly)) {
    cerr << "Cannot read input file " << inputFileName.toLocal8Bit().constData() << endl;
    return 3;
  }

  QFile outputFile;
  if (!outputFileName.isEmpty()) {
    outputFile.setFileName(outputFileName);
    if (!outputFile.open(QIODevice::WriteOnly)) {
      cerr << "Cannot write to output file" << outputFileName.toLocal8Bit().constData() << endl;
      return 4;
    }
  } else {
    outputFile.open(stdout, QIODevice::WriteOnly);
  }

  Parser parser(&inputFile);

  const QSharedPointer<UiTopNode> topNode = parser.parse();
  if (!parser.errorString().isEmpty()) {
    cerr << "Failed to parse input file" << inputFileName.toLocal8Bit().constData() << endl;
    cerr << "Error: " << parser.errorString().toLocal8Bit().constData() << endl;
    return 5;
  }

  SharedVisitationContext sharedVisitationContext(new VisitationContext);

  // set element "id" from objectName
  IdVisitor idVisitor(sharedVisitationContext);
  topNode->accept(&idVisitor);

  // handle layout items
  ItemVisitor itemVisitor(sharedVisitationContext);
  topNode->accept(&itemVisitor);

  // handle layout adjustments
  LayoutVisitor layoutVisitor(sharedVisitationContext);
  topNode->accept(&layoutVisitor);

  // adjust class names
  ElementNameVisitor classVisitor(sharedVisitationContext);
  topNode->accept(&classVisitor);

  // adjust font properties
  FontProperyVisitor fontPropertiesVisitor(sharedVisitationContext);
  topNode->accept(&fontPropertiesVisitor);

  // handle label buddies
  BuddyVisitor buddyVisitor(sharedVisitationContext);
  topNode->accept(&buddyVisitor);

  // handle connections
  ConnectionNodeVisitor connectionVisitor(sharedVisitationContext);
  topNode->accept(&connectionVisitor);

  // handle tab stops
  TabStopsNodeVisitor tabStopsVisitor(sharedVisitationContext);
  topNode->accept(&tabStopsVisitor);

  QmlWriter writer(&outputFile, sharedVisitationContext);
  writer.write(topNode);

  return 0;
}
