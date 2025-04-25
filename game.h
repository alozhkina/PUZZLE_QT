#ifndef GAME_H
#define GAME_H

#include <QList>
#include <QWidget>
#include <vector>
#include <QPushButton >


class QGridLayout;
class QPoint;
class QPushButton;
class QGraphicsRectItem;


class Game : public QWidget
{
    Q_OBJECT

public:
    Game(QWidget* parent = 0);
    void createButton(QPushButton*, int, int, int);
    void loadImage(const QString &path);

private:
    QList<QPushButton*> buttons;
    QList<int> numbers;
    QGridLayout* grid;
    QPoint path;
    QImage* px[15];
    QGraphicsRectItem* m_selection          {nullptr};
    void checkGameOver();
  QImage puzzleImage;
  QVector<QImage> m_pieces_image;

public slots:
    void move();
    void openImage();
    void setupPuzzle();
};

#endif

