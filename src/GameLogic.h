#pragma once

#include<array>

enum class PieceType{
    None,
    Pawn,
    Rook,
    Knight,
    Bishop,
    Queen,
    King
};

enum class PieceColor{
    None,
    White,
    Black
};

struct Piece{
    PieceType type {PieceType::None};
    PieceColor color {PieceColor::None};

    bool isEmpty()const {return type == PieceType::None;}
};

struct Pos {
    int row{};
    int col{};

    bool operator==(const Pos& pos)const {return row == pos.row && col == pos.col; }
};

class GameLogic {
public:
    static constexpr int boardSize {8};
    using Board = std::array<std::array<Piece, boardSize>, boardSize>;

    GameLogic();

    //initialization
    void resetBoard();

    //board state
    Piece getPiece(Pos pos)const;
    PieceColor currentTurn()const{return m_turn;}

    //Logic
    bool isLegalMove(Pos from , Pos to)const;
    bool movePiece(Pos from , Pos to);



private:
    Board m_board;
    PieceColor m_turn;

    static constexpr bool isValid(Pos pos){
        return pos.row >= 0 && pos.row < boardSize
             && pos.col >= 0 && pos.col < boardSize;
    } 
};