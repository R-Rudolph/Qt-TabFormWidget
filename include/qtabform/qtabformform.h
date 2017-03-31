#ifndef SEARCHABLESETTINGSTAB_H
#define SEARCHABLESETTINGSTAB_H

#include <QWidget>
#include <QList>

#include "qtabformelement.h"

class QGridLayout;
class QString;
class QLabel;

class QTabFormWidgetForm : public QTabFormElement
{
  Q_OBJECT
  struct WidgetContainer
  {
    QString label;
    LabelPolicy labelPolicy;
    QWidget* widget;
    QLabel* widgetLabel;
  };
  QWidget* alignmentWidget;
  QGridLayout* layout;
  QList<WidgetContainer> itemList;
  void addContainerToLayout(WidgetContainer& container);
  WidgetContainer* containerByLabel(const QString& label);
public:
  explicit QTabFormWidgetForm(QWidget *parent = 0);
  virtual QWidget* addWidget(const QStringList& label, QWidget* widget, LabelPolicy labelPolicy, int labelDepth=0);
  virtual QWidget* getWidget(const QStringList& label, int labelDepth);
  virtual bool filter(const QString& filterString);
signals:

public slots:
};

#endif // SEARCHABLESETTINGSTAB_H
