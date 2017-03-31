#include "qtabform/qtabformwidget.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QStringList>
#include <QLineEdit>
#include <QRegularExpression>
#include "qtabform/qtabformcontainer.h"
#include "qtabform/qtabformform.h"

QStringList QTabFormWidget::splitLabel(const QString &label)
{
  QStringList result;
  QStringList split = label.split('/');
  QString temp;
  for(int i=0;i<split.size();i++)
  {
    temp.append(split[i]);
    if(!split[i].endsWith('\\'))
    {
      result.append(temp);
      temp.clear();
    }
    else
    {
      temp[temp.length()-1] = '/';
    }
  }
  if(!temp.isEmpty())
    result.append(temp);
  return result;
}

void QTabFormWidget::initialize(bool container)
{
  if(!isInitialized)
  {
    if(container)
      mainWidget = new QTabFormContainer(this);
    else
      mainWidget = new QTabFormWidgetForm(this);
    layout->addWidget(mainWidget);
    isInitialized = true;
  }
}

QTabFormWidget::QTabFormWidget(QWidget *parent, bool hideFilter) : QWidget(parent)
{
  isInitialized = false;
  layout = new QVBoxLayout(this);

  searchLayout = new QHBoxLayout();
  searchLabel = new QLabel("Filter:",this);
  searchEdit = new QLineEdit(this);
  spacerWidget = new QWidget(this);
  searchLayout->addWidget(spacerWidget,1);
  searchLayout->addWidget(searchLabel,0);
  searchLayout->addWidget(searchEdit,1);
  layout->addLayout(searchLayout);
  if(!hideFilter)
  {
    searchEdit->hide();
    searchLabel->hide();
  }

  connect(searchEdit,&QLineEdit::textChanged,this,&QTabFormWidget::filter);
}

void QTabFormWidget::setFilterHidden(bool value)
{
  if(value)
  {
    searchEdit->hide();
    searchLabel->hide();
  }
  else
  {
    searchEdit->show();
    searchLabel->show();
  }
}

QWidget* QTabFormWidget::addWidgetInternal(const QString &label, QWidget *widget, LabelPolicy labelPolicy)
{
  QStringList labelList = splitLabel(label);
  initialize(labelList.size()>1);
  return mainWidget->addWidget(labelList,widget,labelPolicy);
}

void QTabFormWidget::filter(const QString &filterString)
{
  if(!mainWidget->filter(filterString))
    searchEdit->setStyleSheet("background-color:#ff8080;");
  else
    searchEdit->setStyleSheet("");
}
