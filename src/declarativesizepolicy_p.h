#ifndef DECLARATIVESIZEPOLICYEXTENSION_H
#define DECLARATIVESIZEPOLICYEXTENSION_H

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

#endif // DECLARATIVESIZEPOLICYEXTENSION_H
