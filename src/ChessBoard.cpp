#include "ChessBoard.h"
#include <QPainter>
#include <QColor>
#include <QMouseEvent>


ChessBoard::ChessBoard(QWidget* parent)
        :QWidget(parent)
        {
            QSizePolicy sp (QSizePolicy::Preferred, QSizePolicy::Preferred);
            sp.setHeightForWidth(true);
            setSizePolicy(sp);
        }
    
QPixmap ChessBoard::getPiecePixmap(const Piece& p) {
    if(p.isEmpty()) return QPixmap();

    QString name = (p.color == PieceColor::White) ? "White" : "Black";
    switch(p.type){
        case PieceType::Pawn:   name += "Pawn";   break;
        case PieceType::Rook:   name += "Rook";   break;
        case PieceType::Knight: name += "Knight"; break;
        case PieceType::Bishop: name += "Bishop"; break;
        case PieceType::Queen:  name += "Queen";  break;
        case PieceType::King:   name += "King";   break;
        default: return QPixmap();
      }

    return QPixmap(":/src/assets/" + name + ".png") ;
}

void ChessBoard::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    drawBoard(painter);
    drawPieces(painter);
}

void ChessBoard::drawBoard(QPainter& painter){
    int squareSize = width() / 8;
    QColor lightColor(235, 235, 208);
    QColor darkColor(119, 149, 86);
    for(int row {0}; row < 8; ++row){
        for(int col {0}; col < 8; ++col){
            QColor color((row + col) % 2 == 0 ? lightColor : darkColor);

            if(m_selectedPos && m_selectedPos->row == row && m_selectedPos->col == col){
                color = QColor(186, 202, 68);
            }

            painter.fillRect(col * squareSize, row * squareSize, squareSize , squareSize , color);
        }
    }
}

void ChessBoard::drawPieces(QPainter& painter){ 
    int squareSize = width() / 8;
    for(int row {0}; row < 8; ++row){
        for(int col {0}; col < 8; ++col){
            QPixmap pix = getPiecePixmap(m_game.getPiece(Pos{row, col}));

            if(!pix.isNull())
                painter.drawPixmap(col * squareSize, row * squareSize , squareSize , squareSize, pix);
        }
    }

}

void ChessBoard::mousePressEvent(QMouseEvent* event){
    int squareSize = width() / 8;
    int col = event->position().x() / squareSize;
    int row = event->position().y() / squareSize;

    if(m_selectedPos){
        if(m_game.movePiece(*m_selectedPos, {row , col})){
            m_selectedPos = std::nullopt;
        }else{
            m_selectedPos = Pos{row , col}; // if move fails treat this as a new select
        }
    }else{
        m_selectedPos = Pos(row , col);
    }

    update();

}