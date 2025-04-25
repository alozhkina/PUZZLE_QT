#include "game.h"
#include "mainwindow.h"
#include <QGridLayout>
#include <QPushButton>
#include "QMessageBox"
#include <QtWidgets>
#include "form.h"
#include "ui_form.h"
#include <QImage>
#include <QPixmap>

#define SQUARE_SIZE 150
Game::Game(QWidget*)
{
    grid = new QGridLayout(this);
    grid->setHorizontalSpacing(1);
    grid->setVerticalSpacing(1);
    grid->setContentsMargins(2, 2, 2, 2);

    QTime midnight(0, 0, 0);
    srand(midnight.secsTo(QTime::currentTime()));
    openImage();
    for (int i = 0; i < 15; i++) {
           px[i] = new QImage(m_pieces_image[i]);
       }


     //
   int n=0;

     do
     {
         numbers.clear();

         for (int i = 0; i < 15; i++)
         { // случайные числа
             do n = rand() % 15 + 1;
             while (numbers.contains(n));
             numbers << n;
         }

         n = 0;

         for (int i = 2; i <= 15; i++)
             for (int j = 0; j < numbers.indexOf(i); j++)
             {
                 if (numbers[j] < i)
                 {
                     ++n;
                 }
             }


     }
    while (n % 2 == 1);

     do path.setY(rand() % 4);
     while (n % 2 != path.y() % 2);

     path.setX(rand() % 4);

     n = 0;

     for (int y = 0; y < 4; ++y) // строка
         for (int x = 0; x < 4; ++x) // столбец
         {
             if (path.x() == x && path.y() == y)
                 continue;

             createButton(NULL, numbers[n++], x, y);
         }
     setLayout(grid);

};



void Game::move()
{
    int x, y, rs, cs;
    QPushButton* clickedBtn = static_cast<QPushButton*>(sender());
    grid->getItemPosition(grid->indexOf(clickedBtn), &y, &x, &rs, &cs);

  /*  if ((path.x() == x && (path.y() == y + 1 || path.y() == y - 1))
        || (path.y() == y && (path.x() == x + 1 || path.x() == x - 1)))*/ // Можно ли двигать кнопку?
    {
        // удаляем кнопку со старого места
        grid->removeWidget(clickedBtn);
        // и добавляем на свободную ячейку
        createButton(clickedBtn, 0, path.x(), path.y());
        // и обновляем координаиы свободной ячейки
        path = QPoint(x, y);
        checkGameOver(); // проверка на конец игры
    }
}

void Game::checkGameOver()
{
    Q_ASSERT(grid->count() == numbers.size());

    int i = 1, n = 0;

    for (int y = 0; y < grid->rowCount(); ++y) // строка
        for (int x = 0; x < grid->columnCount(); ++x) // столбец
        {
            if (grid->itemAtPosition(y, x) == 0)
                continue;
            n = numbers.indexOf(i++);
            if (buttons[n] != (QPushButton*)grid->itemAtPosition(y, x)->widget())
                return;
        }

    // проверка, свободна ли последняя ячейка
    if (path.y() == grid->rowCount() - 1 && path.x() == grid->columnCount() - 1)
    { // игра окончена
        // блокировка всех кнопок
        for (QList<QPushButton*>::const_iterator it = buttons.begin(); it != buttons.end(); ++it)
            (*it)->setDisabled(true);
        QMessageBox::information(this, "message", "YOU WIN!!!");
    }
}

void Game::createButton(QPushButton* b, int no, int x, int y) // Создание кнопки
{
    QPushButton* btn = b;
    if (!btn)
    {
        btn = new QPushButton();//(QString("%1").arg(no));
        buttons << btn;
        connect(btn, SIGNAL(clicked()), this, SLOT(move()));
        btn->setFixedSize(150, 150);

        QIcon ButtonIcon(QPixmap::fromImage(*px[no - 1]));
        btn->setIcon(ButtonIcon);
        btn->setIconSize(QSize(150, 150));

    }
    grid->addWidget(btn, y, x);
}

void Game::openImage()
{
    const QString directory =
        QStandardPaths::standardLocations(QStandardPaths::PicturesLocation).value(0, QDir::homePath());
    QFileDialog dialog(this, tr("Open Image"), directory);
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    dialog.setFileMode(QFileDialog::ExistingFile);
    QStringList mimeTypeFilters;
    for (const QByteArray &mimeTypeName : QImageReader::supportedMimeTypes())
        mimeTypeFilters.append(mimeTypeName);
    mimeTypeFilters.sort();
    dialog.setMimeTypeFilters(mimeTypeFilters);
    dialog.selectMimeTypeFilter("image/jpeg");
    if (dialog.exec() == QDialog::Accepted)
        loadImage(dialog.selectedFiles().constFirst());
}

void Game::loadImage(const QString &fileName)
{
    QImage newImage;
    if (!newImage.load(fileName)) {
        QMessageBox::warning(this, tr("Open Image"),
                             tr("The image file could not be loaded."),
                             QMessageBox::Close);
        return;
    }


 puzzleImage = newImage;
  setupPuzzle();
};


void Game::setupPuzzle()
{ m_pieces_image.clear();                     //board size
m_pieces_image.resize(4*4);
for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
         m_pieces_image[i + (4*j)] = puzzleImage.copy(QRect(i*SQUARE_SIZE,j*SQUARE_SIZE,SQUARE_SIZE,SQUARE_SIZE));
        }
   }
}

