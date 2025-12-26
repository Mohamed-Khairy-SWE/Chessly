#pragma once 

#include <QWidget>
#include <QPixmap>
#include <map>
#include <string>
#include <optional>
#include "GameLogic.h"

class ChessBoard : public QWidget {
    Q_OBJECT
public:
    explicit ChessBoard(QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    int heightForWidth(int w) const override {return w;}
    QSize sizeHint() const override { return QSize(600,600);}
    
private:
    GameLogic m_game;
    std::optional<Pos> m_selectedPos;

    QPixmap getPiecePixmap(const Piece& p);
    void drawBoard(QPainter& painter);
    void drawPieces(QPainter& painter);
};