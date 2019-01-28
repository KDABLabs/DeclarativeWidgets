/*
  uinodevisitor.h

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

#ifndef UINODEVISITOR_H
#define UINODEVISITOR_H

#include <QMap>
#include <QHash>
#include <QSet>
#include <QSharedPointer>

class UiActionNode;
class UiAddActionNode;
class UiConnectionNode;
class UiLayoutNode;
class UiLayoutItemNode;
class UiNode;
class UiPropertyNode;
class UiObjectNode;
class UiSpacerNode;
class UiTabStopsNode;
class UiTopNode;
class UiWidgetNode;

class VisitationContext
{
  public:
    VisitationContext();

    QString registerImport(const QString &module, const QString &version);

    QStringList generateImportLines() const;

    void insertIdForObjectName(const QString &objectName, const QString &id);
    QString idForObjectName(const QString &objectName) const;

  private:
    typedef QMap<QString, QString> VersionMap;
    typedef QMap<QString, VersionMap> ModuleMap;
    ModuleMap m_imports;

    QSet<QString> m_aliases;

    QHash<QString, QString> m_idsByObjectName;
};

typedef QSharedPointer<VisitationContext> SharedVisitationContext;

class UiNodeVisitor
{
  public:
    explicit UiNodeVisitor(const SharedVisitationContext &sharedContext);
    virtual ~UiNodeVisitor();

    virtual void visit(UiActionNode *actionNode);
    virtual void visit(UiAddActionNode *addActionNode);
    virtual void visit(UiConnectionNode *connectionNode);
    virtual void visit(UiLayoutItemNode *itemNode);
    virtual void visit(UiNode *node);
    virtual void visit(UiLayoutNode *layoutNode);
    virtual void visit(UiPropertyNode *propertyNode);
    virtual void visit(UiObjectNode *objectNode);
    virtual void visit(UiSpacerNode *spacerNode);
    virtual void visit(UiTabStopsNode *tabStopsNode);
    virtual void visit(UiTopNode*topNode);
    virtual void visit(UiWidgetNode *widgetNode);

  protected:
    SharedVisitationContext m_sharedContext;
};

#endif // UINODEVISITOR_H
