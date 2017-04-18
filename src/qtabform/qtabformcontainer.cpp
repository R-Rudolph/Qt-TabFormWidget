#include "qtabformcontainer.h"

#include <QStackedLayout>
#include <QTabWidget>
#include "qtabformform.h"

QTabFormContainer::TabContainer *QTabFormContainer::getContainer(const QString &label)
{
  for(auto tab = tabs.begin();tab!=tabs.end();tab++)
  {
    if(tab->label==label)
      return &*tab;
  }
  return nullptr;
}

void QTabFormContainer::addTab(const QStringList &tabLabel, int labelDepth)
{
  QTabFormElement* newTab;
  const int depthOffset = tabLabel.size()-1-labelDepth;
  if(depthOffset==1)
  {
    newTab = new QTabFormWidgetForm(this);
  }
  else if (depthOffset>1)
  {
    newTab = new QTabFormContainer(this);
  }
  else
  {
    return;
  }
  TabContainer newContainer{tabLabel[labelDepth],newTab};
  tabs.append(newContainer);
  mainWidget->addTab(newTab,tabLabel[labelDepth]);
}

QTabFormContainer::QTabFormContainer(QWidget *parent) : QTabFormElement(parent)
{
  layout = new QStackedLayout(this);
  mainWidget = new QTabWidget(this);
  layout->addWidget(mainWidget);
}

QWidget *QTabFormContainer::addWidget(const QStringList &label, QWidget *widget, LabelPolicy labelPolicy, int labelDepth)
{
  if(label.size()<=labelDepth+1)
    return nullptr;
  TabContainer* container = getContainer(label[labelDepth]);
  if(container==nullptr)
  {
    addTab(label,labelDepth);
    container = getContainer(label[labelDepth]);
  }
  return container->widget->addWidget(label,widget,labelPolicy,labelDepth+1);
}

QWidget *QTabFormContainer::getWidget(const QStringList &label, int labelDepth)
{
  if(label.size()<=labelDepth)
    return nullptr;
  TabContainer* container = getContainer(label[labelDepth]);
  if(container==nullptr)
    return nullptr;
  return container->widget->getWidget(label,labelDepth+1);
}

bool QTabFormContainer::filter(const QString &filterString)
{
  bool empty = true;
  QWidget* currentWidget = mainWidget->currentWidget();
  mainWidget->clear();
  for(auto tab = tabs.begin();tab!=tabs.end();tab++)
  {
    const int index = mainWidget->indexOf(tab->widget);
    if(tab->widget->filter(filterString))
    {
      empty = false;
      if(index<0)
      {
        tab->widget->show();
        mainWidget->addTab(tab->widget,tab->label);
      }
    }
    else
    {
      if(index>=0)
      {
        tab->widget->hide();
        mainWidget->removeTab(index);
      }
    }
  }
  mainWidget->setCurrentWidget(currentWidget);
  return !empty;
}
