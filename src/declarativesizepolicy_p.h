/*
  declarativesizepolicy_p.h

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

#ifndef DECLARATIVESIZEPOLICY_P_H
#define DECLARATIVESIZEPOLICY_P_H

#include <QObject>

class DeclarativeSizePolicy : public QObject
{
    Q_OBJECT

    Q_PROPERTY(ControlType controlType READ controlType WRITE setControlType NOTIFY controlTypeChanged)

    Q_PROPERTY(Policy horizontalPolicy READ horizontalPolicy WRITE setHorizontalPolicy NOTIFY horizontalPolicyChanged)
    Q_PROPERTY(Policy verticalPolicy READ verticalPolicy WRITE setVerticalPolicy NOTIFY verticalPolicyChanged)

    Q_PROPERTY(Qt::Orientations expandingDirections READ expandingDirections STORED false NOTIFY expandingDirectionsChanged)

    Q_PROPERTY(bool hasHeightForWidth READ hasHeightForWidth WRITE setHeightForWidth NOTIFY hasHeightForWidthChanged)
    Q_PROPERTY(bool hasWidthForHeight READ hasWidthForHeight WRITE setWidthForHeight NOTIFY hasWidthForHeightChanged)

    Q_PROPERTY(int horizontalStretch READ horizontalStretch WRITE setHorizontalStretch NOTIFY horizontalStretchChanged)
    Q_PROPERTY(int verticalStretch READ verticalStretch WRITE setVerticalStretch NOTIFY verticalStretchChanged)

    Q_PROPERTY(bool retainSizeWhenHidden READ retainSizeWhenHidden WRITE setRetainSizeWhenHidden NOTIFY retainSizeWhenHiddenChanged)

public:
    enum PolicyFlag {
        GrowFlag = 1,
        ExpandFlag = 2,
        ShrinkFlag = 4,
        IgnoreFlag = 8
    };

    enum Policy {
        Fixed = 0,
        Minimum = GrowFlag,
        Maximum = ShrinkFlag,
        Preferred = GrowFlag | ShrinkFlag,
        MinimumExpanding = GrowFlag | ExpandFlag,
        Expanding = GrowFlag | ShrinkFlag | ExpandFlag,
        Ignored = ShrinkFlag | GrowFlag | IgnoreFlag
    };
    Q_ENUM(Policy)

    enum ControlType {
        DefaultType      = 0x00000001,
        ButtonBox        = 0x00000002,
        CheckBox         = 0x00000004,
        ComboBox         = 0x00000008,
        Frame            = 0x00000010,
        GroupBox         = 0x00000020,
        Label            = 0x00000040,
        Line             = 0x00000080,
        LineEdit         = 0x00000100,
        PushButton       = 0x00000200,
        RadioButton      = 0x00000400,
        Slider           = 0x00000800,
        SpinBox          = 0x00001000,
        TabWidget        = 0x00002000,
        ToolButton       = 0x00004000
    };
    Q_ENUM(ControlType)
    Q_DECLARE_FLAGS(ControlTypes, ControlType)
    Q_FLAG(ControlTypes)

    explicit DeclarativeSizePolicy(QWidget* extendedWidget, QObject* parent);

    ControlType controlType() const;
    Policy horizontalPolicy() const;
    Policy verticalPolicy() const;
    Qt::Orientations expandingDirections() const;
    bool hasHeightForWidth() const;
    bool hasWidthForHeight() const;
    int horizontalStretch() const;
    int verticalStretch() const;
    bool retainSizeWhenHidden() const;

public slots:
    void setControlType(ControlType controlType);
    void setHorizontalPolicy(Policy horizontalPolicy);
    void setVerticalPolicy(Policy verticalPolicy);
    void setHeightForWidth(bool heightForWidth);
    void setWidthForHeight(bool widthForHeight);
    void setHorizontalStretch(int horizontalStretch);
    void setVerticalStretch(int verticalStretch);
    void setRetainSizeWhenHidden(bool retainSizeWhenHidden);

signals:
    void controlTypeChanged(ControlType controlType);
    void horizontalPolicyChanged(Policy horizontalPolicy);
    void verticalPolicyChanged(Policy verticalPolicy);
    void expandingDirectionsChanged(Qt::Orientations expandingDirections);
    void hasHeightForWidthChanged(bool hasHeightForWidth);
    void hasWidthForHeightChanged(bool hasWidthForHeight);
    void horizontalStretchChanged(int horizontalStretch);
    void verticalStretchChanged(int verticalStretch);
    void retainSizeWhenHiddenChanged(bool retainSizeWhenHidden);

private:
    QWidget* m_extendedWidget;
};

#endif // DECLARATIVESIZEPOLICY_P_H
