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

#ifndef DECLARATIVESPACERITEM_P_H
#define DECLARATIVESPACERITEM_P_H

#include <QObject>
#include <QSize>
#include <QSizePolicy>

class QSpacerItem;

class DeclarativeSpacerItem : public QObject
{
  Q_OBJECT
  Q_PROPERTY(int width READ width NOTIFY widthChanged)
  Q_PROPERTY(int height READ height NOTIFY heightChanged)
  Q_PROPERTY(QSize sizeHint READ sizeHint WRITE setSizeHint NOTIFY sizeHintChanged)
  Q_PROPERTY(SizePolicy horizontalSizePolicy READ horizontalPolicy WRITE setHorizontalPolicy NOTIFY horizontalPolicyChanged)
  Q_PROPERTY(SizePolicy verticalSizePolicy READ verticalPolicy WRITE setVerticalPolicy NOTIFY verticalPolicyChanged)
  Q_ENUMS(SizePolicy)

  public:
    enum SizePolicy {
      Fixed = QSizePolicy::Fixed,
      Minimum = QSizePolicy::Minimum,
      Maximum = QSizePolicy::Maximum,
      Preferred = QSizePolicy::Preferred,
      Expanding = QSizePolicy::Expanding,
      MinimumExpanding = QSizePolicy::MinimumExpanding,
      Ignored = QSizePolicy::Ignored
    };

    explicit DeclarativeSpacerItem(QObject *parent = 0);
    ~DeclarativeSpacerItem();

    QSpacerItem *spacer() const;

    int width() const;

    int height() const;

    void setSizeHint(const QSize &sizeHint);
    QSize sizeHint() const;

    void setHorizontalPolicy(SizePolicy policy);
    SizePolicy horizontalPolicy() const;

    void setVerticalPolicy(SizePolicy policy);
    SizePolicy verticalPolicy() const;

  Q_SIGNALS:
    void widthChanged(int width);
    void heightChanged(int height);
    void sizeHintChanged();
    void horizontalPolicyChanged();
    void verticalPolicyChanged();

  private:
    class Private;
    Private *d;
};

#endif // DECLARATIVESPACERITEM_P_H
