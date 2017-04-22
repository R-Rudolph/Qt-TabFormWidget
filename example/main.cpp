#include <QApplication>
#include <QLineEdit>
#include <QCheckBox>
#include <QDebug>
#include <QComboBox>

#include <QTabFormWidget>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QTabFormWidget* settingsWidget = new QTabFormWidget(0);
  settingsWidget->addWidget("Menu A\\/B/A/Field A1",new QComboBox(),LabelPolicy::Empty);
  settingsWidget->addWidget("Menu A\\/B/B/Field B1",new QLineEdit(),LabelPolicy::Show);
  settingsWidget->addWidget("Menu A\\/B/B/Field B2",new QCheckBox("Field B2"),LabelPolicy::Empty);
  settingsWidget->addWidget("Menu C/Field C1",new QLineEdit(),LabelPolicy::None);
  settingsWidget->addWidget("Menu C/Field C2",new QLineEdit(),LabelPolicy::Show);
  settingsWidget->addWidget("Menu C/Field C3",new QLineEdit(),LabelPolicy::NewLine);
  settingsWidget->show();

  qDebug() << settingsWidget->getWidget<QLineEdit>("Menu C/Field C3");
  return a.exec();
}
