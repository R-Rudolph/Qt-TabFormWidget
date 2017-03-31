#ifndef SEARCHABLESETTINGSELEMENT_H
#define SEARCHABLESETTINGSELEMENT_H

#include <QWidget>

enum class LabelPolicy
{
  Show,
  Empty,
  None,
  NewLine
};

class QTabFormElement : public QWidget
{
  Q_OBJECT
public:
  explicit QTabFormElement(QWidget *parent = 0);
  virtual QWidget* addWidget(const QStringList& label, QWidget* widget, LabelPolicy labelPolicy, int labelDepth=0) = 0;
  virtual QWidget* getWidget(const QStringList& label, int labelDepth=0) = 0;
  virtual bool filter(const QString& filterString) = 0;
signals:

public slots:
};

#endif // SEARCHABLESETTINGSELEMENT_H
