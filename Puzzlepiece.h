#ifndef PIECE_H
#define PIECE_H
#include "form.h"
#include "ui_form.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vector>
#include <QString>


enum DIRECTIONS { RIGHT = 0, LEFT, UP, DOWN, BLOCKED };

class PuzzlePiece{
public:
    PuzzlePiece(int x = 0, int y = 0, int value = 0, int dir = BLOCKED);
    int m_pos_x;
    int m_pos_y;
    int m_value;
    int m_movable_dir;
    void operator=(PuzzlePiece*);
};

typedef std::vector<PuzzlePiece> Board;
typedef std::vector<PuzzlePiece>::const_iterator Board_Const_Iter;
typedef std::vector<PuzzlePiece>::iterator Board_Iter;

class PuzzleBoard
{
public:
    PuzzleBoard(int board_size = 3);
    ~PuzzleBoard();

    PuzzlePiece* piece(int x, int y);
    void update_board();
    void move_piece(int x, int y);
    int check_piece_mov(int x, int y);
    std::vector<PuzzlePiece*> get_movable_pieces();
    int get_size();
    const Board* get_board();
    void set_board(PuzzleBoard*);
    bool compare_boards(PuzzleBoard*);
    void scramble_board_with_moves(int num_moves = 100);
    void calculate_unique_id();
    QString* get_unique_id();
private:

    int m_board_size;
    Board m_board;
    QString m_unique_id;
};

class BoardWidget : public QWidget

{
    Q_OBJECT
public:
    explicit BoardWidget(PuzzleBoard *board,bool locked = false, int img =  0, QWidget *parent = 0);
    void set_curr_board(PuzzleBoard*);
    ~BoardWidget();

signals:
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
public slots:
    void change_image(int img);
    void lock_board(bool lock);
signals:
    void piece_moved();
private:
    void load_images();
    PuzzleBoard *m_board;
    QPainter *m_painter;
    QVector<QImage> m_pieces_image;
    int m_pieces_size;
    int m_img_index;
    bool m_locked;
};

#endif // PIECE_H
