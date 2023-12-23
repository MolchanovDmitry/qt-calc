#include "mainwindow.h"
#include "ext.cpp" // Почему-то получаю "undefined reference" при подключении заголовочника.
#include "ui_mainwindow.h"
#include <QDebug>
#include <QObject>
#include <QPushButton>
#include <QRegExp>
#include <QRegExpValidator>

void initClickListenersForNumberButtons(QGridLayout *gridLayout,
                                        CalcViewModel *viewModel) {
    auto gridLength = gridLayout->count();
    for (int i = 0; i < gridLength; i++) {
        auto child = gridLayout->itemAt(i);
        auto pushButton = qobject_cast<QPushButton *>(child->widget());
        auto isPushButton = pushButton != nullptr;

        if (isPushButton) {
            auto title = pushButton->text();
            bool isNumber;
            auto number = title.toInt(&isNumber);

            if (isNumber) {
                QObject::connect(pushButton, &QPushButton::clicked,
                                 [number, viewModel] {
                    qDebug() << "Нажата кнопка: " << number;
                    viewModel->concatenateNumber(number);
                });
            }
        }
    }
}

MainWindow::MainWindow(QWidget *parent, CalcViewModel *viewModel)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    auto lineEdit = ui->lineEdit;

    setLineEditNumberOnly(lineEdit);
    initClickListenersForNumberButtons(ui->gridLayout, viewModel);

    connect(lineEdit, &QLineEdit::textChanged, viewModel, &CalcViewModel::onTextChanged);
    connect(viewModel, &CalcViewModel::onDisplayTextChanged, lineEdit, &QLineEdit::setText);

    connect(ui->cleanBtn, &QPushButton::clicked, viewModel, &CalcViewModel::clean);
    connect(ui->equalsBtn, &QPushButton::clicked, viewModel, &CalcViewModel::equals);

    connect(ui->plusBtn, &QPushButton::clicked, viewModel, &CalcViewModel::plus);
    connect(ui->minusBtn, &QPushButton::clicked, viewModel, &CalcViewModel::minus);
    connect(ui->multBtn, &QPushButton::clicked, viewModel, &CalcViewModel::multiplication);
    connect(ui->divBtn, &QPushButton::clicked, viewModel, &CalcViewModel::division);
}

MainWindow::~MainWindow() {
    delete ui;
}
