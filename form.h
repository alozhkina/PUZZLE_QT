#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include "game.h"
class QHBoxLayout;
class QLabel;
class QLCDNumber;
class QSpinBox;
class QVBoxLayout;

namespace Ui {
    class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget* parent = 0);
    ~Form();
public slots:
    void newGame();
    void exitGame();

private:
    Ui::Form* ui;
    Game* game;
    QHBoxLayout* settingsLayout;
    QVBoxLayout* layout;
    QSpinBox* cubesize;
    QTimer* timer;

};

#endif // FORM_H

