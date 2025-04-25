#include "QMessageBox"
#include "form.h"
#include "ui_form.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap bkgnd("://1679013732_bogatyr-club-p-zelenii-pazl-foni-pinterest-2.jpg");
      bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
      QPalette p = palette();
      p.setBrush(QPalette::Background, bkgnd);
      setPalette(p);
      setWindowTitle(tr("Puzzle"));
      setWindowIcon(QIcon(":/ic/vVup3CWCXww.jpg"));



}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::exiT() // Выход.
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Exit", "Do you really want to leave the game?", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        close();
    }
}

void MainWindow::starT() // Старт.
{
    Form* f = new Form();
    f->show();
    this->close();
}

void MainWindow::on_pushButton_clicked()
{
    starT();
}

void MainWindow::on_pushButton_2_clicked()
{
    exiT();
}
