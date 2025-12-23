#pragma once 

#include <QWidget>
#include <QPixmap>
#include <map>
#include <string>

class ChessBoard : public QWidget {
    Q_OBJECT
public:
    explicit ChessBoard(QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent* event) override;
    int heightForWidth(int w) const override {return w;}
    QSize sizeHint() const override { return QSize(600,600);}
    
private:
    void drawBoard(QPainter& painter);
    void drawPieces(QPainter& painter);
};