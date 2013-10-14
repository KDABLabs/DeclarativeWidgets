/*
  Copyright (C) 2013 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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

#ifndef UINODE_H
#define UINODE_H

class UiNodeVisitor;

#include <QList>
#include <QString>

class UiNode
{
  public:
    UiNode();
    virtual ~UiNode();

    virtual void accept(UiNodeVisitor *visitor) = 0;
    void acceptChildren(UiNodeVisitor *visitor);

    virtual void appendChild(UiNode *node);
    virtual void prependChild(UiNode *node);
    UiNode *childAt(int index);
    UiNode *takeChildAt(int index);
    int childCount() const;

    QString name() const;
    void setName(const QString &name);

  protected:
    QString m_name;
    QList<UiNode*> m_children;
};

#endif // UINODE_H
