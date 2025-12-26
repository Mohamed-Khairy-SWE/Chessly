#pragma once 

#include <array>
#include <optional>

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

struct Piece {
    PieceType type {PieceType::None};
    PieceColor color {PieceColor::None};

    [[nodiscard]]
    constexpr bool isEmpty() const noexcept{
        return type == PieceType::None;
    }
};

struct Pos {
    int row {};
    int col {};

    [[nodiscard]]
    constexpr bool operator==(const Pos&) const noexcept = default;
};

class GameLogic {
public:
    static constexpr int boardSize = 8;

    using Board = std::array<std::array<Piece, boardSize>, boardSize>;
    GameLogic();

    // game state
    [[nodiscard]]
    Piece getPiece(Pos pos) const;

    [[nodiscard]]
    PieceColor currentTurn() const noexcept{
        return m_turn;
    }

    // game logic
    [[nodiscard]]
    bool movePiece(Pos from , Pos to);

    [[nodiscard]]
    bool isLegalMove(Pos from, Pos to) const;


    //initialization
    void resetBoard();

private:
    Board m_board {};
    PieceColor m_turn {PieceColor::White};

    [[nodiscard]]
    static constexpr bool isValid(Pos pos) noexcept{
        return pos.row >= 0 && pos.row < boardSize
             && pos.col >= 0 && pos.col < boardSize;
    } 
};