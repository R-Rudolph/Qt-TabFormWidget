# Qt-TabFormWidget

Qt-TabFormWidget is a Qt Widget with a simple interface for ordering Widgets in a Form Layout-like manner within (nested) Tab Widgets.

When adding a widget, a label which describes where to put the widget must be provided. For example, the label
```
"Tab/Subtab/Widget 1"
```
will place the widget in Tab->Subtab, and give it the labeling "Widget 1".

Additionally, a style of labeling handling can be provided.
```
LabelPolicy::Show   : Shows the label on the left side, like QFormLayout does. This is the default.
LabelPolicy::Empty  : Will show no label, but the widget will be limted the the right side.
LabelPolicy::None   : No label is displayed, the widget will fill the Tab Form Widget horizontally
LabelPolicy::NewLine: The label is displayed above the widget.
```

Further, a filtering mechanism is given, which filters shown widgets by their widget label (but not tab). Empty tabs will be ommited.

## Usage

For usage with qmake, include the provided pri-file in your pro-file. The widget can be included with
```
#include "qtabform/qtabformwidget.h"
```
