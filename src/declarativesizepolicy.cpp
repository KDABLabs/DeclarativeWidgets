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
