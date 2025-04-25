#include "form.h"
#include "ui_form.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHBoxLayout>
#include <QPushButton>
#include <QVBoxLayout>

Form::Form(QWidget* parent) : game(NULL),
QWidget(parent),
ui(new Ui::Form)
{
    ui->setupUi(this);

    layout = new QVBoxLayout(this);
    settingsLayout = new QHBoxLayout;
    setWindowTitle(tr("Puzzle"));
    setWindowIcon(QIcon(":/ic/vVup3CWCXww.jpg"));


    QPushButton* newgame = new QPushButton("choose a picture");
    QPushButton* exitgame = new QPushButton("come back");
    setStyleSheet("QPushButton {background-color: #EFEFF1; font-size: 20px; font-family: Trebuchet MS;}");


    newgame->setIconSize(QSize(304, 70));
    exitgame->setIconSize(QSize(304, 70));

    connect(newgame, SIGNAL(clicked()), this, SLOT(newGame()));
    connect(exitgame, SIGNAL(clicked()), this, SLOT(exitGame()));

    settingsLayout->addWidget(newgame);
    settingsLayout->addWidget(exitgame);


    layout->addLayout(settingsLayout);
    newGame();

        setLayout(layout);

}

Form::~Form()
{
    delete ui;
}

void Form::newGame()
{
    if (game) //удаляем старое поле
    {
        layout->removeWidget(game);
        delete game;
    }

    game = new Game(/*4, */this); //рисуем новое поле
    layout->addWidget(game);

    layout->update();

    game->hide();
    game->show();

    resize(sizeHint());
}

void Form::exitGame()
{
       MainWindow* f = new MainWindow();
       f->show();
       this->close();
}


