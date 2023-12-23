#include "ext.h"
#include <QLineEdit>
#include <QRegExpValidator>
#include <QDebug>
#include <string>

/**
 * Ограничить возможность добавлять в виджет только числа
 */
void setLineEditNumberOnly(QLineEdit *lineEdit) {
  lineEdit->setValidator(new QRegExpValidator(QRegExp("[0-9]*"), lineEdit));
}
