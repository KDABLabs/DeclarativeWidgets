#ifndef DECLARATIVEPALETTE_P_H
#define DECLARATIVEPALETTE_P_H

#include <QObject>
#include <QPalette>

class DeclarativePalette : public QObject
{
  Q_OBJECT

  Q_ENUMS(ColorRole)

  public:
    enum ColorRole {
      WindowText = QPalette::WindowText,
      Button = QPalette::Button,
      Light = QPalette::Light,
      Midlight = QPalette::Midlight,
      Dark = QPalette::Dark,
      Mid = QPalette::Mid,
      Text = QPalette::Text,
      BrightText = QPalette::BrightText,
      ButtonText = QPalette::ButtonText,
      Base = QPalette::Base,
      Window = QPalette::Window,
      Shadow = QPalette::Shadow,
      Highlight = QPalette::Highlight,
      HighlightedText = QPalette::HighlightedText,
      Link = QPalette::Link,
      LinkVisited = QPalette::LinkVisited,
      AlternateBase = QPalette::AlternateBase,
      NoRole = QPalette::NoRole,
      ToolTipBase = QPalette::ToolTipBase,
      ToolTipText = QPalette::ToolTipText,
      NColorRoles = QPalette::NColorRoles,
      Foreground = QPalette::Foreground,
      Background = QPalette::Background
    };
};

#endif // DECLARATIVEPALETTE_P_H
