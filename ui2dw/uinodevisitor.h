/*
  Copyright (C) 2013-2014 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Kevin Krammer, kevin.krammer@kdab.com
  Author: Tobias Koenig, tobias.koenig@kdab.com

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
*/

#ifndef UINODEVISITOR_H
#define UINODEVISITOR_H

#include <QMap>
#include <QHash>
#include <QSet>
#include <QSharedPointer>

class UiActionNode;
class UiAddActionNode;
class UiLayoutNode;
class UiItemNode;
class UiNode;
class UiPropertyNode;
class UiObjectNode;
class UiSpacerNode;
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
    virtual void visit(UiItemNode *itemNode);
    virtual void visit(UiNode *node);
    virtual void visit(UiLayoutNode *layoutNode);
    virtual void visit(UiPropertyNode *propertyNode);
    virtual void visit(UiObjectNode *objectNode);
    virtual void visit(UiSpacerNode *spacerNode);
    virtual void visit(UiTopNode*topNode);
    virtual void visit(UiWidgetNode *widgetNode);

  protected:
    SharedVisitationContext m_sharedContext;
};

#endif // UINODEVISITOR_H
