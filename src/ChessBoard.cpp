#include "ChessBoard.h"
#include <QPainter>
#include <QColor>


ChessBoard::ChessBoard(QWidget* parent)
        :QWidget(parent)
        {
            QSizePolicy sp (QSizePolicy::Preferred, QSizePolicy::Preferred);
            sp.setHeightForWidth(true);
            setSizePolicy(sp);
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
            painter.fillRect(col * squareSize, row * squareSize, squareSize , squareSize , color);
        }
    }
}

void ChessBoard::drawPieces(QPainter& painter){
    QPixmap WhiteKing(":/src/assets/WhiteKing.png");

    if(WhiteKing.isNull())
        return;
    
    int squareSize = width() / 8;

    QPixmap scaled = WhiteKing.scaled(
        squareSize,
        squareSize,
        Qt::KeepAspectRatio,
        Qt::SmoothTransformation
    );

    painter.drawPixmap(
        4 * squareSize,
        7 * squareSize,
        scaled
    );
}