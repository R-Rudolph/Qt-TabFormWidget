#ifndef SEARCHABLESETTINGSCONTAINER_H
#define SEARCHABLESETTINGSCONTAINER_H

#include <QWidget>
#include "qtabformelement.h"
#include <QMap>

class QStackedLayout;
class QTabWidget;
class QStringList;


class QTabFormContainer : public QTabFormElement
{
  Q_OBJECT
  struct TabContainer
  {
    QString label;
    QTabFormElement* widget;
  };
  QStackedLayout* layout;
  QTabWidget* mainWidget;
  QList<TabContainer> tabs;
  TabContainer* getContainer(const QString& label);
  void addTab(const QStringList& tabLabel, int labelDepth);
public:
  explicit QTabFormContainer(QWidget *parent = 0);
  virtual QWidget* addWidget(const QStringList& label, QWidget* widget, LabelPolicy labelPolicy, int labelDepth=0);
  virtual QWidget* getWidget(const QStringList& label, int labelDepth=0);
  virtual bool filter(const QString& filterString);
signals:

public slots:
private slots:
};

#endif // SEARCHABLESETTINGSCONTAINER_H
