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

#include "declarativeline_p.h"

#include <QDebug>

DeclarativeLine::DeclarativeLine(QWidget *parent)
  : QFrame(parent)
{
  setFrameShape(QFrame::HLine);
}

void DeclarativeLine::setOrientation(Qt::Orientation orient)
{
  if (orientation() == orient) {
    return;
  }

  setFrameShape(orient == Qt::Vertical ? QFrame::VLine : QFrame::HLine);

  emit orientationChanged();
}

Qt::Orientation DeclarativeLine::orientation() const
{
  if (frameShape() == QFrame::VLine) {
    return Qt::Vertical;
  }
  if (frameShape() != QFrame::HLine) {
    qWarning() << Q_FUNC_INFO << objectName() << "has frame shape other than VLine or HLine.";
  }

  return Qt::Horizontal;
}
