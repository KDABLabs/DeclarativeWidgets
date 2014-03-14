/*
  Copyright (C) 2014 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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

#ifndef UICONNECTIONNODE_H
#define UICONNECTIONNODE_H

#include "uinode.h"

#include <QStringList>

class Parser;

class UiConnectionNode : public UiNode
{
  public:
    UiConnectionNode();

    static UiNode *parse(Parser *parser);

    void accept(UiNodeVisitor *visitor);

    void setSender(const QString &id);
    QString sender() const;
    void setReceiver(const QString &id);
    QString receiver() const;

    QString signalSignature() const;
    QString slotSignature() const;

    void setSignalHandler(const QString &signalHandler);
    QString signalHandler() const;

    void setSlotName(const QString &slotName);
    QString slotName() const;

    void setArgumentTypes(const QStringList &argumentTypes);
    QStringList argumentTypes() const;

  protected:
    QString m_sender;
    QString m_receiver;
    QString m_signalSignature;
    QString m_slotSignature;

    QString m_signalHandler;
    QString m_slotName;
    QStringList m_argumentTypes;
};

#endif // UICONNECTIONNODE_H
