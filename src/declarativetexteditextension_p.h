/*
  declarativetexteditextension_p.h

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

#ifndef DECLARATIVETEXTEDITEXTENSION_P_H
#define DECLARATIVETEXTEDITEXTENSION_P_H

#include <QtGlobal>
#include "declarativewidgetextension.h"

QT_BEGIN_NAMESPACE
class QTextDocument;
class QTextEdit;
QT_END_NAMESPACE

class DeclarativeTextEditExtension : public DeclarativeWidgetExtension
{
  Q_OBJECT

  // TODO
  // ideally QTextDocument's property declaration for modified would include the modificationChanged signal
  // as its NOTIFY, this and setDocument could then be removed
  Q_PROPERTY(bool modified READ modified NOTIFY modifiedChanged)
  Q_PROPERTY(QTextDocument* document READ document WRITE setDocument NOTIFY documentChanged)

  // repeat property declarations, qmlRegisterExtendedType doesn't see the ones from base class
  Q_PROPERTY(QQmlListProperty<QObject> data READ data DESIGNABLE false CONSTANT)

  Q_CLASSINFO("DefaultProperty", "data")

  public:
    explicit DeclarativeTextEditExtension(QObject *parent = 0);

    void setDocument(QTextDocument *document);
    QTextDocument *document() const;

  Q_SIGNALS:
    void modifiedChanged();
    void documentChanged();

  private:
    bool modified() const;
    QTextEdit *textEdit() const;
};

#endif
