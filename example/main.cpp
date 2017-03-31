#include <QApplication>
#include <QLineEdit>
#include <QCheckBox>
#include "qtabform/qtabformwidget.h"
#include <QDebug>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QTabFormWidget* settingsWidget = new QTabFormWidget(0);
  settingsWidget->addWidget("Menu A\\/B/B/Field B1",new QLineEdit(),LabelPolicy::Show);
  settingsWidget->addWidget("Menu A\\/B/B/Field B2",new QCheckBox("Field B2"),LabelPolicy::Empty);
  settingsWidget->addWidget("Menu C/Field C1",new QLineEdit(),LabelPolicy::None);
  settingsWidget->addWidget("Menu C/Field C2",new QLineEdit(),LabelPolicy::Show);
  settingsWidget->addWidget("Menu C/Field B3",new QLineEdit(),LabelPolicy::NewLine);
  settingsWidget->show();


  qDebug() << settingsWidget->getWidget<QLineEdit>("Menu C/Field B3");
  return a.exec();
}
