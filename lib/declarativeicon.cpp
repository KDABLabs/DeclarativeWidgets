#include "declarativeicon_p.h"

DeclarativeIconAttached::DeclarativeIconAttached(QObject *parent)
  : QObject(parent)
{
}

QString DeclarativeIconAttached::themeName() const
{
  return QIcon::themeName();
}

void DeclarativeIconAttached::setThemeName(const QString &name)
{
  if (name == QIcon::themeName())
    return;

  QIcon::setThemeName(name);
  emit themeNameChanged(name);
}

QStringList DeclarativeIconAttached::themeSearchPaths() const
{
  return QIcon::themeSearchPaths();
}

void DeclarativeIconAttached::setThemeSearchPaths(const QStringList &paths)
{
  if (paths == QIcon::themeSearchPaths())
    return;

  QIcon::setThemeSearchPaths(paths);
  emit themeSearchPathsChanged(paths);
}

QIcon DeclarativeIconAttached::fromTheme(const QString &name)
{
  return QIcon::fromTheme(name);
}

QIcon DeclarativeIconAttached::fromFileName(const QString &fileName)
{
  return QIcon(fileName);
}

class DeclarativeIcon::Private
{
  public:
    QIcon icon;
};

DeclarativeIcon::DeclarativeIcon(QObject *parent)
  : QObject(parent)
  , d(new Private)
{
}

DeclarativeIcon::~DeclarativeIcon()
{
  delete d;
}

QIcon DeclarativeIcon::icon() const
{
  return d->icon;
}

void DeclarativeIcon::setIcon(const QIcon &icon)
{
  if (icon.cacheKey() == d->icon.cacheKey())
    return;

  const QString oldName = d->icon.name();
  const bool oldIsNull = d->icon.isNull();

  d->icon = icon;
  emit iconChanged(icon);

  if (oldName != d->icon.name())
    emit nameChanged(d->icon.name());

  if (oldIsNull == d->icon.isNull())
    emit isNullChanged(d->icon.isNull());
}

QString DeclarativeIcon::name() const
{
  return d->icon.name();
}

bool DeclarativeIcon::isNull() const
{
  return d->icon.isNull();
}

DeclarativeIconAttached *DeclarativeIcon::qmlAttachedProperties(QObject *parent)
{
  return new DeclarativeIconAttached(parent);
}
