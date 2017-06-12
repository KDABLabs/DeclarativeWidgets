/*
  Copyright (C) 2012-2013 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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

#ifndef DECLARATIVECONTEXT_P_H
#define DECLARATIVECONTEXT_P_H

#include "declarativeobjectproxy_p.h"

#include "objectadaptors_p.h"

class DeclarativeQmlContext : public DeclarativeObjectProxy<DeclarativeContext>
{
  DECLARATIVE_OBJECT

  public:
    explicit DeclarativeQmlContext(QObject *parent = 0);

  protected:
    void createProxiedObject() const;

    void dataAppend(QObject *object);
};

#endif
