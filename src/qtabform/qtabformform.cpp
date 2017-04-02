#include "qtabform/qtabformform.h"

#include <QGridLayout>
#include <QString>
#include <QLabel>
#include <QDebug>

void QTabFormWidgetForm::addContainerToLayout(QTabFormWidgetForm::WidgetContainer &container)
{
  const int row = layout->rowCount()-1; //last row before placeholder for alignment
  switch(container.labelPolicy)
  {
    case LabelPolicy::Empty:
      container.widgetLabel->hide();
      layout->addWidget(container.widget,row,1,1,1);
      //layout->addRow("",container.widget);
      break;
    case LabelPolicy::None:
      container.widgetLabel->hide();
      layout->addWidget(container.widget,row,0,1,2);
      //layout->addRow(container.widget);
      break;
    case LabelPolicy::Show:
      layout->addWidget(container.widgetLabel,row,0,1,1);
      layout->addWidget(container.widget,row,1,1,1);
      //layout->addRow(container.label,container.widget);
      break;
    case LabelPolicy::NewLine:
      layout->addWidget(container.widgetLabel,row,0,1,2);
      layout->addWidget(container.widget,row+1,0,1,2);
      break;
  }
  layout->addWidget(alignmentWidget,layout->rowCount(),0,1,2);
}

QTabFormWidgetForm::WidgetContainer* QTabFormWidgetForm::containerByLabel(const QString &label)
{
  for(auto i = itemList.begin();i!=itemList.end();i++)
  {
    if(i->label==label)
      return &*i;
  }
  return nullptr;
}

QTabFormWidgetForm::QTabFormWidgetForm(QWidget *parent) : QTabFormElement(parent)
{
  layout = new QGridLayout(this);
  alignmentWidget = new QWidget();
  alignmentWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
  layout->addWidget(alignmentWidget,layout->rowCount(),0,1,2);
}

QWidget *QTabFormWidgetForm::addWidget(const QStringList &label, QWidget *widget, LabelPolicy labelPolicy, int labelDepth)
{
  if(labelDepth != label.size()-1)
    return nullptr;
  QLabel* newLabel = new QLabel(label[labelDepth]+":",this);
  WidgetContainer container{label[labelDepth],labelPolicy,widget,newLabel};
  itemList.push_back(container);
  addContainerToLayout(container);
  return widget;
}

QWidget *QTabFormWidgetForm::getWidget(const QStringList &label, int labelDepth)
{
  if(labelDepth!=label.size()-1)
    return nullptr;
  else
    return containerByLabel(label[labelDepth])->widget;
}

bool QTabFormWidgetForm::filter(const QString &filterString)
{
  bool empty = true;
  for(auto i=itemList.begin();i!=itemList.end();i++)
  {
    if(i->label.contains(filterString,Qt::CaseInsensitive))
    {
      i->widget->show();
      if(i->labelPolicy==LabelPolicy::NewLine || i->labelPolicy==LabelPolicy::Show)
        i->widgetLabel->show();
      empty = false;
    }
    else
    {
      i->widget->hide();
      i->widgetLabel->hide();
    }
  }
  return !empty;
}
