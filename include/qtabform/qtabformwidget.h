#ifndef SEARCHABLESETTINGSWIDGET_H
#define SEARCHABLESETTINGSWIDGET_H

#include <QWidget>
#include <QString>
#include <QTabWidget>
#include <QStackedLayout>
#include <QMap>

#include "qtabformelement.h"

class QVBoxLayout;
class QHBoxLayout;
class QLabel;
class QLineEdit;
class QRegularExpression;

class QTabFormWidget : public QWidget
{
  Q_OBJECT
  QVBoxLayout* layout;
  QHBoxLayout* searchLayout;
  QTabFormElement* mainWidget;
  QLabel* searchLabel;
  QLineEdit* searchEdit;
  QWidget* spacerWidget;
  QStringList splitLabel(const QString& label);
  bool isInitialized;
  void initialize(bool container);
  QWidget* addWidgetInternal(const QString& label, QWidget* widget, LabelPolicy labelPolicy=LabelPolicy::Show);
public:
  explicit QTabFormWidget(QWidget *parent = 0, bool hideFilter = true);

  template<class T = QWidget>
  T* addWidget(const QString& label, QWidget* widget, LabelPolicy labelPolicy=LabelPolicy::Show)
  {
    return static_cast<T*>(addWidgetInternal(label,widget,labelPolicy));
  }

  template<class T>
  T* newWidget(const QString& label, LabelPolicy labelPolicy=LabelPolicy::Show)
  {
    return static_cast<T*>(addWidgetInternal(label,new T(),labelPolicy));
  }

  template<class T = QWidget> T* getWidget(const QString& label)
  {
    QStringList labelList = splitLabel(label);
    return static_cast<T*>(mainWidget->getWidget(labelList));
  }
signals:

public slots:
  void setFilterHidden(bool value);
  void filter(const QString& filterString);
private slots:
};

#endif // SEARCHABLESETTINGSWIDGET_H
