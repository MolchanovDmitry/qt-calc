#ifndef CALCVIEWMODEL_H
#define CALCVIEWMODEL_H

#include <QDebug>
#include <QObject>

/** Типы возможны операций */
enum OperationType { None, Plus, Minus, Multiplication, Division };

/** Состояние модели представления */
struct State {

    /** Выбранная операция */
    OperationType selectedOperation;

    /** Операнд 1 */
    ulong operand1 = 0;

    /** Операнд 2 */
    ulong operand2 = 0;
};

/**
 * Модель представления экрана калькулятора.
 * Делегируем ему логику нажатия кнопок.
 */
class CalcViewModel : public QObject {
    Q_OBJECT

public:
    CalcViewModel(QObject *parent = nullptr);

signals:

    void onDisplayTextChanged(QString text);

private:
    State state = State();

    void updateDisplatText(int displatNumber) {
        auto displatText = QString::number(displatNumber);
        qDebug() << "Обновляем отображаемый текст числом: " << displatText;
        emit onDisplayTextChanged(displatText);
    }

    void initDefault() {
        state.operand1 = 0;
        state.operand2 = 0;
        state.selectedOperation = None;
    }

    void changeOperation(OperationType newOperation) {
        if (state.selectedOperation == newOperation) {
            equals();
        }
        state.selectedOperation = newOperation;
    }

public slots:

    void concatenateNumber(int number) {
        if (state.selectedOperation == None) {
            qDebug() << "Конкатенация операнда 1";
            state.operand1 = state.operand1 * 10 + number;
            updateDisplatText(state.operand1);
        } else {
            qDebug() << "Конкатенация операнда 2";
            state.operand2 = state.operand2 * 10 + number;
            updateDisplatText(state.operand2);
        }
    }

    void onTextChanged(QString text) {
        auto newNumber = text.toULong();
        if (state.selectedOperation == None) {
            state.operand1 = newNumber;
        } else {
            state.operand2 = newNumber;
        }
    }

    void clean() {
        qDebug() << "Чистим";
        initDefault();
        emit onDisplayTextChanged("");
    }

    void plus() {
        qDebug() << "Сложение";
        changeOperation(Plus);
    }

    void minus() {
        qDebug() << "Минус";
        changeOperation(Minus);
    }

    void multiplication() {
        qDebug() << "Умножение";
        changeOperation(Multiplication);
    }

    void division() {
        qDebug() << "Деление";
        changeOperation(Division);
    }

    void equals() {
        qDebug() << "Операнд 1: " << state.operand1
                 << " , операнд 2: " << state.operand2;
        ulong result;
        switch (state.selectedOperation) {
        case None:
            qDebug() << "Нет выбранной операции";
            return;
        case Plus:
            qDebug() << "Выполняем сложение";
            result = state.operand1 + state.operand2;
            break;
        case Minus:
            qDebug() << "Выполняем вычитание";
            result = state.operand1 - state.operand2;
            break;
        case Multiplication:
            qDebug() << "Выполняем умножение";
            result = state.operand1 * state.operand2;
            break;
        case Division:
            qDebug() << "Выполняем деление";
            if (state.operand2 == 0) {
                emit onDisplayTextChanged("На ноль делить нельзя");
                return;
            } else {
                result = state.operand1 / state.operand2;
            }
            break;
        }
        initDefault();
        state.operand1 = result;
        updateDisplatText(result);
    }
};

#endif // CALCVIEWMODEL_H
