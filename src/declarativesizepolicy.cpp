/*
  declarativesizepolicy.cpp

  This file is part of DeclarativeWidgets, library and tools for creating QtWidget UIs with QML.

  Copyright (C) 2018-2019 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Nathan Collins <nathan.collins@kdab.com>

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
#include "declarativesizepolicy_p.h"

#include <QWidget>

DeclarativeSizePolicy::DeclarativeSizePolicy(QWidget *extendedWidget, QObject *parent)
    : QObject(parent)
    , m_extendedWidget(extendedWidget)
{
    Q_ASSERT(m_extendedWidget);
}

DeclarativeSizePolicy::ControlType DeclarativeSizePolicy::controlType() const
{
    Q_ASSERT(m_extendedWidget);

    return static_cast<DeclarativeSizePolicy::ControlType>(m_extendedWidget->sizePolicy().controlType());
}

DeclarativeSizePolicy::Policy DeclarativeSizePolicy::horizontalPolicy() const
{
    Q_ASSERT(m_extendedWidget);

    return static_cast<DeclarativeSizePolicy::Policy>(m_extendedWidget->sizePolicy().horizontalPolicy());
}

DeclarativeSizePolicy::Policy DeclarativeSizePolicy::verticalPolicy() const
{
    Q_ASSERT(m_extendedWidget);

    return static_cast<DeclarativeSizePolicy::Policy>(m_extendedWidget->sizePolicy().verticalPolicy());
}

Qt::Orientations DeclarativeSizePolicy::expandingDirections() const
{
    Q_ASSERT(m_extendedWidget);

    return m_extendedWidget->sizePolicy().expandingDirections();
}

bool DeclarativeSizePolicy::hasHeightForWidth() const
{
    Q_ASSERT(m_extendedWidget);

    return m_extendedWidget->sizePolicy().hasHeightForWidth();
}

bool DeclarativeSizePolicy::hasWidthForHeight() const
{
    Q_ASSERT(m_extendedWidget);

    return m_extendedWidget->sizePolicy().hasWidthForHeight();
}

int DeclarativeSizePolicy::horizontalStretch() const
{
    Q_ASSERT(m_extendedWidget);

    return m_extendedWidget->sizePolicy().horizontalStretch();
}

int DeclarativeSizePolicy::verticalStretch() const
{

    Q_ASSERT(m_extendedWidget);

    return m_extendedWidget->sizePolicy().verticalStretch();
}

bool DeclarativeSizePolicy::retainSizeWhenHidden() const
{
    Q_ASSERT(m_extendedWidget);

    return m_extendedWidget->sizePolicy().retainSizeWhenHidden();
}

void DeclarativeSizePolicy::setControlType(DeclarativeSizePolicy::ControlType controlType)
{
    Q_ASSERT(m_extendedWidget);

    QSizePolicy policy = m_extendedWidget->sizePolicy();
    if (policy.controlType() == static_cast<QSizePolicy::ControlType>(controlType))
        return;
    policy.setControlType(static_cast<QSizePolicy::ControlType>(controlType));
    m_extendedWidget->setSizePolicy(policy);
    emit controlTypeChanged(controlType);
}

void DeclarativeSizePolicy::setHorizontalPolicy(DeclarativeSizePolicy::Policy horizontalPolicy)
{
    Q_ASSERT(m_extendedWidget);

    QSizePolicy policy = m_extendedWidget->sizePolicy();
    if (policy.horizontalPolicy() == static_cast<QSizePolicy::Policy>(horizontalPolicy))
        return;

    const Qt::Orientations oldExpandingDirections = policy.expandingDirections();
    policy.setHorizontalPolicy(static_cast<QSizePolicy::Policy>(horizontalPolicy));
    const Qt::Orientations newExpandingDirections = policy.expandingDirections();
    m_extendedWidget->setSizePolicy(policy);

    emit horizontalPolicyChanged(horizontalPolicy);
    if (newExpandingDirections != oldExpandingDirections)
        emit expandingDirectionsChanged(newExpandingDirections);
}

void DeclarativeSizePolicy::setVerticalPolicy(DeclarativeSizePolicy::Policy verticalPolicy)
{
    Q_ASSERT(m_extendedWidget);

    QSizePolicy policy = m_extendedWidget->sizePolicy();
    if (policy.verticalPolicy() == static_cast<QSizePolicy::Policy>(verticalPolicy))
        return;

    const Qt::Orientations oldExpandingDirections = policy.expandingDirections();
    policy.setVerticalPolicy(static_cast<QSizePolicy::Policy>(verticalPolicy));
    const Qt::Orientations newExpandingDirections = policy.expandingDirections();
    m_extendedWidget->setSizePolicy(policy);

    emit verticalPolicyChanged(verticalPolicy);
    if (newExpandingDirections != oldExpandingDirections)
        emit expandingDirectionsChanged(newExpandingDirections);
}

void DeclarativeSizePolicy::setHeightForWidth(bool heightForWidth)
{
    Q_ASSERT(m_extendedWidget);

    QSizePolicy policy = m_extendedWidget->sizePolicy();
    if (policy.hasHeightForWidth() == heightForWidth)
        return;
    policy.setHeightForWidth(heightForWidth);
    m_extendedWidget->setSizePolicy(policy);
    emit hasHeightForWidthChanged(heightForWidth);
}

void DeclarativeSizePolicy::setWidthForHeight(bool widthForHeight)
{
    Q_ASSERT(m_extendedWidget);

    QSizePolicy policy = m_extendedWidget->sizePolicy();
    if (policy.hasWidthForHeight() == widthForHeight)
        return;
    policy.setWidthForHeight(widthForHeight);
    m_extendedWidget->setSizePolicy(policy);
    emit hasWidthForHeightChanged(widthForHeight);
}

void DeclarativeSizePolicy::setHorizontalStretch(int horizontalStretch)
{
    Q_ASSERT(m_extendedWidget);

    QSizePolicy policy = m_extendedWidget->sizePolicy();
    if (policy.horizontalStretch() == horizontalStretch)
        return;
    policy.setHorizontalStretch(horizontalStretch);
    m_extendedWidget->setSizePolicy(policy);
    emit horizontalStretchChanged(horizontalStretch);
}

void DeclarativeSizePolicy::setVerticalStretch(int verticalStretch)
{
    Q_ASSERT(m_extendedWidget);

    QSizePolicy policy = m_extendedWidget->sizePolicy();
    if (policy.verticalStretch() == verticalStretch)
        return;
    policy.setVerticalStretch(verticalStretch);
    m_extendedWidget->setSizePolicy(policy);
    emit verticalStretchChanged(verticalStretch);
}

void DeclarativeSizePolicy::setRetainSizeWhenHidden(bool retainSizeWhenHidden)
{
    Q_ASSERT(m_extendedWidget);

    QSizePolicy policy = m_extendedWidget->sizePolicy();
    if (policy.retainSizeWhenHidden() == retainSizeWhenHidden)
        return;
    policy.setRetainSizeWhenHidden(retainSizeWhenHidden);
    m_extendedWidget->setSizePolicy(policy);
    emit retainSizeWhenHiddenChanged(retainSizeWhenHidden);
}
