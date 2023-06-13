#pragma once
#include "JDM/JDM.hpp"


static int numOfMoves = 0;
static const int gridNumber = 8;
static const float animationSpeed = 0.2;

enum ChessColor { BLACK, WHITE };
enum ChessEnum {
    ROOK = 0,
    BISHOP = 1,
    QUEEN = 2,
    KING = 3,
    KNIGHT = 4,
    PON = 5
};

class ChessMoveGenerator {
public:

    inline static const void printPosition(const std::vector<std::vector<char>> &position) {
        for (int r = gridNumber-1; r >= 0; r--) {
            std::cout << '|'; for (int c = gridNumber-1; c >= 0; c--)
            std::cout << ' ' << position[r][c] << " |"; std::cout << '\n';
        } std::cout << "\n----------------------------------\n";
    }
    inline static const bool isTileNotOutOfBounds(int row, int col) { return ((gridNumber > col && col >= 0) && (gridNumber > row && row >= 0)); }
	inline static const bool isTileFree(const std::vector<std::vector<char>> &position, int row, int col) {
        return (ChessMoveGenerator::isTileNotOutOfBounds(row, col) && (position[gridNumber-1-row][gridNumber-1-col] == ' '));
    }
	inline static const bool isTileDifferentColor(const std::vector<std::vector<char>> &position, int row, int col) {
        return (ChessMoveGenerator::isTileNotOutOfBounds(row, col) && position[gridNumber-1-row][gridNumber-1-col] != ' ' &&
			((numOfMoves % 2 == 0) ? std::islower(position[gridNumber-1-row][gridNumber-1-col])
				                :   !std::islower(position[gridNumber-1-row][gridNumber-1-col])));
    }
	inline static const bool isTileInKing(const std::vector<std::vector<char>> &position, int row, int col, int currentTurn) {
        return (isTileNotOutOfBounds(row, col) && ((currentTurn % 2 == 0) ?
              position[gridNumber-1-row][gridNumber-1-col] == 'k'
            : position[gridNumber-1-row][gridNumber-1-col] == 'K'));
    }
    inline static const char pieceToString(ChessEnum piece, ChessColor color) {
        switch (piece) {
            case ROOK:    return (color) ? 'R' : 'r';
            case KNIGHT:  return (color) ? 'N' : 'n';
            case BISHOP:  return (color) ? 'B' : 'b';
            case QUEEN:   return (color) ? 'Q' : 'q';
            case KING:    return (color) ? 'K' : 'k';
            case PON:     return (color) ? 'P' : 'p';
        } return ' ';
    }
    inline static const void getMoveFromPosition(
        bool isMoved, ChessEnum piece, int r, int c,
        std::vector<std::pair<int, int>> &allPossibleMoves,
        std::vector<std::vector<char>> &position) {
        allPossibleMoves.clear();
        switch (piece) {
            case KNIGHT : ChessMoveGenerator::getKnightMove   ( position, r, c, allPossibleMoves                    ); return;
            case BISHOP : ChessMoveGenerator::moveContinously ( position, r, c, allPossibleMoves, gridNumber, true  ); return;
            case ROOK   : ChessMoveGenerator::moveContinously ( position, r, c, allPossibleMoves, gridNumber, false ); return;
            case QUEEN  : ChessMoveGenerator::moveContinously ( position, r, c, allPossibleMoves, gridNumber, true  );
                          ChessMoveGenerator::moveContinously ( position, r, c, allPossibleMoves, gridNumber, false ); return;
            case KING   : ChessMoveGenerator::getKingMove     ( position, r, c, allPossibleMoves, isMoved           ); return;
            case PON    : ChessMoveGenerator::getPonMove      ( position, r, c, allPossibleMoves, isMoved           ); return;
        }
    }
    inline static const void moveContinously(
		std::vector<std::vector<char>> &position, int row, int col,
        std::vector<std::pair<int, int>> &allPossibleMoves,int max, bool isDiagonal) {
		bool fourWay[] = {false, false, false, false};
        auto checkBoard = [&](int c, int r) {
            if (ChessMoveGenerator::isTileFree(position, r, c)) { allPossibleMoves.push_back(std::make_pair(r, c)); return true; }
            else if (ChessMoveGenerator::isTileDifferentColor(position, r, c)) allPossibleMoves.push_back(std::make_pair(r, c)); return false;
        };
        for (int i = 1; i <= max; i++) { 
			if (!fourWay[0] && !checkBoard(col+i, row+ (isDiagonal ? i : 0)))                       fourWay[0] = true;
			if (!fourWay[1] && !checkBoard(col-i, row+ (isDiagonal ? i : 0)))                       fourWay[1] = true;
			if (!fourWay[2] && !checkBoard(col+ (isDiagonal ? i : 0), row + (isDiagonal ? -i : i))) fourWay[2] = true;
			if (!fourWay[3] && !checkBoard(col+ (isDiagonal ? -i : 0), row-i))                      fourWay[3] = true;
		}
	}
    inline static const bool moveContinouslyKingEaten(
		std::vector<std::vector<char>> &position,
		int row, int col, int max, bool isDiagonal) {
		bool fourWay[] = {true, true, true, true};
		for (int i = 1; i <= max; i++) {
			if (fourWay[0] && ChessMoveGenerator::isTileInKing(position, row+ (isDiagonal ? i : 0), col+i,                      numOfMoves+1)) return true;
			else if (!ChessMoveGenerator::isTileFree(position, row+ (isDiagonal ? i : 0), col+i))                                       fourWay[0] = false;
            if (fourWay[1] && ChessMoveGenerator::isTileInKing(position, row+ (isDiagonal ? i : 0), col-i,                      numOfMoves+1)) return true;
			else if (!ChessMoveGenerator::isTileFree(position, row+ (isDiagonal ? i : 0), col-i))                                       fourWay[1] = false;
			if (fourWay[2] && ChessMoveGenerator::isTileInKing(position, row+ (isDiagonal ? -i : i), col+ (isDiagonal ? i : 0), numOfMoves+1)) return true;
			else if (!ChessMoveGenerator::isTileFree(position, row+ (isDiagonal ? -i : i), col+ (isDiagonal ? i : 0)))                  fourWay[2] = false;
			if (fourWay[3] && ChessMoveGenerator::isTileInKing(position, row-i, col+ (isDiagonal ? -i : 0),                     numOfMoves+1)) return true;
			else if (!ChessMoveGenerator::isTileFree(position, row-i, col+ (isDiagonal ? -i : 0)))                                      fourWay[3] = false;
		} return false;
	}
    inline static const void getKingMove(std::vector<std::vector<char>> &position, int r, int c, std::vector<std::pair<int, int>> &allPossibleMoves, bool isMoved) {
        ChessMoveGenerator::moveContinously(position, r, c, allPossibleMoves, 1, true );
        ChessMoveGenerator::moveContinously(position, r, c, allPossibleMoves, 1, false);
        if (!isMoved) {
            bool checkTwo[] = {true, true};
            for (int i = 1; i < gridNumber; i++) {
                if (checkTwo[0] && !ChessMoveGenerator::isTileFree(position, r, c+i))
                    if (i >= 3 && position[gridNumber-1-r][gridNumber-1-(c+i)] == ((numOfMoves % 2 == 0) ?  'R' : 'r')) { allPossibleMoves.push_back(std::make_pair(r, std::min(c+i, c+2))); checkTwo[0] = false; }
                    else checkTwo[0] = false;

                if (checkTwo[1] && !ChessMoveGenerator::isTileFree(position, r, c-i)) 
                    if (i >= 3 && position[gridNumber-1-r][gridNumber-1-(c-i)] == ((numOfMoves % 2 == 0) ?  'R' : 'r')) { allPossibleMoves.push_back(std::make_pair(r, std::max(c-i, c-2))); checkTwo[1] = false; }
                    else checkTwo[1] = false;
        }}
    }
    inline static const void getPonMove(std::vector<std::vector<char>> &position, int r, int c, std::vector<std::pair<int, int>> &allPossibleMoves, bool isMoved) {
        int newRow  = ((numOfMoves % 2 == 0) ? r-1 : r+1);
		int newRow2 = ((numOfMoves % 2 == 0) ? r-2 : r+2);
		if (ChessMoveGenerator::isTileDifferentColor(position, newRow, c+1))  allPossibleMoves.push_back(std::make_pair(newRow, c+1));
		if (ChessMoveGenerator::isTileDifferentColor(position, newRow, c-1))  allPossibleMoves.push_back(std::make_pair(newRow, c-1));
		if (ChessMoveGenerator::isTileFree(position, newRow, c))              allPossibleMoves.push_back(std::make_pair(newRow,   c));
		if (!isMoved && ChessMoveGenerator::isTileFree(position, newRow2, c)) allPossibleMoves.push_back(std::make_pair(newRow2,  c));
    }
    inline static const void getKnightMove(std::vector<std::vector<char>> &position, int r, int c, std::vector<std::pair<int, int>> &allPossibleMoves) {
        if (ChessMoveGenerator::isTileFree(position, r-1, c-2)
         || ChessMoveGenerator::isTileDifferentColor(position, r-1, c-2))
			allPossibleMoves.push_back(std::make_pair(r-1, c-2));
		if (ChessMoveGenerator::isTileFree(position, r+1, c-2)
         || ChessMoveGenerator::isTileDifferentColor(position, r+1, c-2))
			allPossibleMoves.push_back(std::make_pair(r+1, c-2));
		if (ChessMoveGenerator::isTileFree(position, r-1, c+2)
         || ChessMoveGenerator::isTileDifferentColor(position, r-1, c+2))
			allPossibleMoves.push_back(std::make_pair(r-1, c+2));
		if (ChessMoveGenerator::isTileFree(position, r+1, c+2)
         || ChessMoveGenerator::isTileDifferentColor(position, r+1, c+2))
			allPossibleMoves.push_back(std::make_pair(r+1, c+2));
		if (ChessMoveGenerator::isTileFree(position, r-2, c-1)
         || ChessMoveGenerator::isTileDifferentColor(position, r-2, c-1))
			allPossibleMoves.push_back(std::make_pair(r-2, c-1));
		if (ChessMoveGenerator::isTileFree(position, r+2, c-1)
         || ChessMoveGenerator::isTileDifferentColor(position, r+2, c-1))
			allPossibleMoves.push_back(std::make_pair(r+2, c-1));
		if (ChessMoveGenerator::isTileFree(position, r-2, c+1)
         || ChessMoveGenerator::isTileDifferentColor(position, r-2, c+1))
			allPossibleMoves.push_back(std::make_pair(r-2, c+1));
		if (ChessMoveGenerator::isTileFree(position, r+2, c+1)
         || ChessMoveGenerator::isTileDifferentColor(position, r+2, c+1))
			allPossibleMoves.push_back(std::make_pair(r+2, c+1));
    }
    inline static const bool isKnightEatKing(std::vector<std::vector<char>> &position, int r, int c) {
        return ((ChessMoveGenerator::isTileInKing(position, r-1, c-2, numOfMoves+1))
		     || (ChessMoveGenerator::isTileInKing(position, r+1, c-2, numOfMoves+1))
		     || (ChessMoveGenerator::isTileInKing(position, r-1, c+2, numOfMoves+1))
		     || (ChessMoveGenerator::isTileInKing(position, r+1, c+2, numOfMoves+1))
		     || (ChessMoveGenerator::isTileInKing(position, r-2, c-1, numOfMoves+1))
		     || (ChessMoveGenerator::isTileInKing(position, r+2, c-1, numOfMoves+1))
		     || (ChessMoveGenerator::isTileInKing(position, r-2, c+1, numOfMoves+1))
		     || (ChessMoveGenerator::isTileInKing(position, r+2, c+1, numOfMoves+1)));
    }
    inline static const bool isBishopEatKing(std::vector<std::vector<char>> &position, int r, int c) { return  ChessMoveGenerator::moveContinouslyKingEaten(position, r, c, gridNumber, true); }
    inline static const bool isRookEatKing  (std::vector<std::vector<char>> &position, int r, int c) { return  ChessMoveGenerator::moveContinouslyKingEaten(position, r, c, gridNumber, false); }
    inline static const bool isQueenEatKing (std::vector<std::vector<char>> &position, int r, int c) { return ((ChessMoveGenerator::moveContinouslyKingEaten(position, r, c, gridNumber, true )) || (ChessMoveGenerator::moveContinouslyKingEaten(position, r, c, gridNumber, false)) ); }
    inline static const bool iskingEatKing  (std::vector<std::vector<char>> &position, int r, int c) { return ((ChessMoveGenerator::moveContinouslyKingEaten(position, r, c, 1, true )) || (ChessMoveGenerator::moveContinouslyKingEaten(position, r, c, 1, false)) ); }
    inline static const bool isPonEatKing   (std::vector<std::vector<char>> &position, int r, int c) {
        int newRow = (((numOfMoves+1) % 2 == 0) ? r-1 : r+1);
		return ((ChessMoveGenerator::isTileInKing(position, newRow, c+1, numOfMoves+1)) || (ChessMoveGenerator::isTileInKing(position, newRow, c-1, numOfMoves+1)) );
    }
};

class Chess {
public:
    const static std::string WindowTitle;
    const static JDM::ColorRGB backGround;
    const static double WIDTH;
    const static double HEIGHT;

private:
    const double blockSize = 600 / gridNumber;
    const double startX = 300;
    const double startY = 60;
    bool moving = false;

    std::vector<std::vector<char>> boardStringPosition;
    std::vector<std::vector<char>> oldStringPosition;
    std::string chessPosition = "rnbqkbnr/pppppppp/////PPPPPPPP/RNBQKBNR";

private: // Components
    std::shared_ptr<JDM::Layout::GridLayout> gridLayout = std::make_shared<JDM::Layout::GridLayout>(startX, startY, 600, 600, gridNumber, gridNumber);
    std::shared_ptr<JDM::Layout::FloatLayout> allChessPiece = std::make_shared<JDM::Layout::FloatLayout>();
    
    class ChessPiece : public JDM::Comp::Image {
    public:
        bool isMoved = false;
        int row, col;
        ChessColor chessColor;
        ChessEnum  chessPiece;
        std::vector<std::pair<int, int>> allPossibleMoves;
        ChessPiece(Chess *chess, int r, int c, ChessColor color, ChessEnum piece)
            : JDM::Comp::Image("Assets/chess.png", chess->startX, chess->startY, chess->blockSize, chess->blockSize) {
            this->chessColor = color;
            this->chessPiece = piece;
            this->setImageRegion({(300*piece)+10, (color ? 400 : 0), 300, 400});
            updatePosition(r, c, chess);
        }
    public:
        const void updatePosition(int r, int c, Chess *chess) {
            this->row = gridNumber - 1 - r;
            this->col = gridNumber - 1 - c;
            this->setX(chess->startX  + (chess->blockSize * this->col));
            this->setY(chess->startY  + (chess->blockSize * this->row));
        }
    };
    std::shared_ptr<ChessPiece> currentSelected = nullptr;
    class Tile : public JDM::Canvas::Rectangle {
    public:
        int row, col;
        std::shared_ptr<JDM::Layout::GridLayout> parent;
        std::shared_ptr<ChessPiece> Piece = nullptr;

        bool selected = false;
        Chess *chess = nullptr;
        Tile(Chess *chess, int r, int c, const std::shared_ptr<JDM::Layout::GridLayout> &parentGrid)
        : chess(chess), parent(parentGrid), JDM::Canvas::Rectangle(0, 0, 0, 0, ((r + c) % 2 == 0)
            ? JDM::getColorFromHexA(JDM::Color::SKY_BLUE) : JDM::getColorFromHexA(JDM::Color::GHOST_WHITE)) {
            this->row = gridNumber - 1 - r;
            this->col = gridNumber - 1 - c;

            this->setmouseDownFunction(std::bind([](SDL_MouseButtonEvent &mouse, Tile *rect) {
                if ( rect->chess->moving) return;
                if ((rect->Piece == nullptr
                || ( numOfMoves % 2 == 0 && !rect->Piece->chessColor)
                || ( numOfMoves % 2 == 1 &&  rect->Piece->chessColor)
                )) {
                    bool foundMove = false;
                    for (auto &tiles : rect->parent->getAllChildren()) {
                        auto tile = dynamic_cast<Tile *>(&(*tiles));
                        if (tile->selected && tile != rect) {
                            if (rect->chess->currentSelected != nullptr && rect->chess->isPairInVector(
                                rect->chess->currentSelected->allPossibleMoves, rect->row, rect->col
                            )) { foundMove = true; tile->setPiece(nullptr); }
                            tile->setInterpolatedFactor(0);
                            tile->selected = false;
                        }
                    }
                    if (foundMove) {
                        rect->chess->moving = true;
                        rect->chess->allChessPiece->removeChildren(rect->chess->currentSelected);
                        rect->chess->allChessPiece->addChildren(rect->chess->currentSelected);
                        if (rect->Piece != nullptr) rect->chess->allChessPiece->removeChildren(rect->Piece);

                        JDM::Window::addStartAnimation(std::make_shared<JDM::Animation<double>>(rect->chess->currentSelected->getPointerX(),
                            rect->chess->startX + (rect->chess->blockSize * rect->col), animationSpeed, true));
                        JDM::Window::addStartAnimation(std::make_shared<JDM::Animation<double>>(rect->chess->currentSelected->getPointerY(),
                            rect->chess->startY + (rect->chess->blockSize * rect->row), animationSpeed, true));

                        if (       (rect->chess->currentSelected->chessPiece == KING)
                        && std::abs(rect->chess->currentSelected->col - rect->col) > 1) {
                            std::shared_ptr<Tile> tileTarget = nullptr;
                            std::shared_ptr<Tile> destination = rect->chess->allTileInVector[gridNumber-1-rect->row][gridNumber-1-(
                                                            ((  rect->chess->currentSelected->col - rect->col) < 0) ? (rect->col-1) : (rect->col+1))];

                            for (int i = 1; i < gridNumber-1; i++) {
                                auto tile = rect->chess->allTileInVector[gridNumber-1-rect->row][gridNumber-1-(
                                        ((  rect->chess->currentSelected->col - rect->col) < 0) ? (rect->col+i) : (rect->col-i))];
                                if (tile->Piece != nullptr) { tileTarget = tile; break; }
                            }
                            JDM::Window::addStartAnimation(std::make_shared<JDM::Animation<double>>(tileTarget->Piece->getPointerX(),
                                rect->chess->startX + (rect->chess->blockSize * destination->col), animationSpeed, true));

                            destination->setPiece(tileTarget->Piece);
                            tileTarget->Piece->isMoved = true;
                            tileTarget->Piece->row = destination->row;
                            tileTarget->Piece->col = destination->col;
                            tileTarget->setPiece(nullptr);
                        }

                        JDM::Window::addStartClock(std::make_shared<JDM::Clock>(animationSpeed+0.01, true, (std::bind([](Tile *rect) {
                            rect->setPiece(rect->chess->currentSelected);
                            rect->Piece->isMoved = true;
                            rect->Piece->row = rect->row;
                            rect->Piece->col = rect->col;
                            rect->chess->currentSelected = nullptr;

                            numOfMoves++;
                            rect->chess->getAllPieceMoves();
                            rect->chess->moving = false;
                        }, rect))));
                        return;
                    } 
                    rect->setInterpolatedColorAndFactor(JDM::getColorFromHexA(JDM::Color::RED), 0.5);
                    return;
                }
                for (auto tiles : rect->parent->getAllChildren()) {
                    auto tile = dynamic_cast<Tile *>(&(*tiles));
                    tile->setInterpolatedFactor(0);
                    tile->selected = false;
                }
                rect->selected = true;
                rect->setInterpolatedColorAndFactor(JDM::getColorFromHexA(JDM::Color::YELLOW), 0.5);
                rect->chess->currentSelected = rect->Piece;
            }, std::placeholders::_1, this));
        }
        inline void setPiece(const std::shared_ptr<ChessPiece> &piece) { this->Piece = piece; }
    };
    std::vector<std::vector<std::shared_ptr<Tile>>> allTileInVector;

    inline bool isPairInVector(const std::vector<std::pair<int, int>>& vec, int first, int second) {
        // Check if the pair is within the vec pair
        for (const auto& pair : vec)  if (pair.first == first && pair.second == second) return true;
        return false;
    }

    inline const void getAllPieceMoves() {
        this->transformPositonToString();  // Convert the current position to a string representation
        ChessMoveGenerator::printPosition(boardStringPosition);  // Print the board position (for debugging purposes)

        // Iterate over all chess pieces
        for (auto& piece : allChessPiece->getAllChildren()) {
            auto childPiece = dynamic_cast<ChessPiece*>(&(*piece));

            // Check if it's the current player's turn to move the piece
            if ((numOfMoves % 2 == 0 && childPiece->chessColor) || (numOfMoves % 2 && !childPiece->chessColor)) {

                // Get possible moves for the piece
                ChessMoveGenerator::getMoveFromPosition(
                    childPiece->isMoved,  // Boolean indicating if the piece has been moved before
                    childPiece->chessPiece,  // Type of chess piece (KING, QUEEN, ROOK, etc.)
                    childPiece->row,  // Piece's current row
                    childPiece->col,  // Piece's current column
                    childPiece->allPossibleMoves,  // Vector to store possible moves (passed by reference)
                    this->boardStringPosition  // Current board position as a string
                );

                // Filter the valid moves for the piece
                if (childPiece->allPossibleMoves.size()) {
                    this->filterValidMove(childPiece);
                }
            }
        }
    }

    inline const void filterValidMove(ChessPiece *piece) {
        // Vector to store the filtered valid moves
        std::vector<std::pair<int, int>> newPair;

        // Check if castling is possible and filter moves accordingly
        if (piece->chessPiece == KING) this->filterIfCastlingPossible(piece);

        // Iterate over all possible moves for the piece
        for (const auto &move : piece->allPossibleMoves) {
            bool validMove = true;

            // Temporarily update the board position to simulate the move
            char pieceRPos   = boardStringPosition[gridNumber-1-piece->row][gridNumber-1-piece->col];
            char pieceEPos   = boardStringPosition[gridNumber-1-move.first][gridNumber-1-move.second];
            boardStringPosition[gridNumber-1-piece->row][gridNumber-1-piece->col]    = ' ';
            boardStringPosition[gridNumber-1-move.first][gridNumber-1-move.second]   = pieceRPos;

            for (auto &currPiece : allChessPiece->getAllChildren()) {
                auto childPiece = dynamic_cast<ChessPiece *>(&(*currPiece));
                // Skip the current piece being moved
                if (childPiece->row == move.first && childPiece->col == move.second) continue;
                // Check if it's the opponent's piece
                if (((numOfMoves+1) % 2 == 0 &&  childPiece->chessColor)
                ||  ((numOfMoves+1) % 2      && !childPiece->chessColor)) {
                // Check if the move would result in the king being attacked
                switch (childPiece->chessPiece) {
                    case KNIGHT: if (ChessMoveGenerator::isKnightEatKing(boardStringPosition, childPiece->row, childPiece->col)) validMove = false; break;
                    case BISHOP: if (ChessMoveGenerator::isBishopEatKing(boardStringPosition, childPiece->row, childPiece->col)) validMove = false; break;
                    case ROOK  : if (ChessMoveGenerator::isRookEatKing  (boardStringPosition, childPiece->row, childPiece->col)) validMove = false; break;
                    case QUEEN : if (ChessMoveGenerator::isQueenEatKing (boardStringPosition, childPiece->row, childPiece->col)) validMove = false; break;
                    case KING  : if (ChessMoveGenerator::iskingEatKing  (boardStringPosition, childPiece->row, childPiece->col)) validMove = false; break;
                    case PON   : if (ChessMoveGenerator::isPonEatKing   (boardStringPosition, childPiece->row, childPiece->col)) validMove = false; break;
                }
            }}
            // If the move is valid, add it to the new pair of valid moves
            if (validMove) { newPair.push_back(move); }
            // Restore the original board position
            boardStringPosition[gridNumber-1-piece->row][gridNumber-1-piece->col]   = pieceRPos;
            boardStringPosition[gridNumber-1-move.first][gridNumber-1-move.second]  = pieceEPos;
        }
        // Store all filtered move to piece all possible move
        piece->allPossibleMoves.clear();
        piece->allPossibleMoves = newPair;
    }

    inline const void filterIfCastlingPossible(ChessPiece *piece) {
        // Check if castling to the right is possible
        if (isPairInVector(piece->allPossibleMoves, piece->row, piece->col+2)) {
            for (int i = 3; i < gridNumber-1; i++) {
                // Check if piece is not nullptr or piece is rook
                if (allTileInVector[gridNumber-1-piece->row][gridNumber-1-(piece->col+i)]->Piece != nullptr) {
                if (allTileInVector[gridNumber-1-piece->row][gridNumber-1-(piece->col+i)]->Piece->isMoved) {
                    // If the piece (ROOK specifically) has been moved, remove the castling move from the possible moves
                    piece->allPossibleMoves.erase(
                        std::find(piece->allPossibleMoves.begin(), piece->allPossibleMoves.end(),
                        std::make_pair(piece->row, piece->col+2)),
                        piece->allPossibleMoves.end());
                } break;
            }}}
        // Check if castling to the left is possible
        if (isPairInVector(piece->allPossibleMoves, piece->row, piece->col-2)) {
            for (int i = 3; i < gridNumber-1; i++) {
                // Check if piece is not nullptr or piece is rook
                if (allTileInVector[gridNumber-1-piece->row][gridNumber-1-(piece->col-i)]->Piece != nullptr) {
                if (allTileInVector[gridNumber-1-piece->row][gridNumber-1-(piece->col-i)]->Piece->isMoved) {
                    // If the piece (ROOK specifically) has been moved, remove the castling move from the possible moves
                    piece->allPossibleMoves.erase(
                        std::find(piece->allPossibleMoves.begin(), piece->allPossibleMoves.end(),
                        std::make_pair(piece->row, piece->col-2)),
                        piece->allPossibleMoves.end());
                } break;
            }}}
    }

private:
    inline const void stringToPosition() {
        int c = 0, r = gridNumber-1;
        auto addChild = [&](int row, int col, ChessColor color, ChessEnum piece) {
            auto pieces = std::make_shared<ChessPiece>(this, row, gridNumber-1-col, color, piece);
            this->allTileInVector[r][gridNumber-1-c]->setPiece(pieces);
            this->allChessPiece->addChildren(pieces);
        };
        for (auto ch : this->chessPosition) {
            switch(ch) {
                case 'R': if (c >= gridNumber) break; addChild(r, c, WHITE, ROOK); c++; break;
                case 'N': if (c >= gridNumber) break; addChild(r, c, WHITE, KNIGHT); c++; break;
                case 'B': if (c >= gridNumber) break; addChild(r, c, WHITE, BISHOP); c++; break;
                case 'Q': if (c >= gridNumber) break; addChild(r, c, WHITE, QUEEN); c++; break;
                case 'K': if (c >= gridNumber) break; addChild(r, c, WHITE, KING); c++; break;
                case 'P': if (c >= gridNumber) break; addChild(r, c, WHITE, PON); c++; break;
                case 'r': if (c >= gridNumber) break; addChild(r, c, BLACK, ROOK); c++; break;
                case 'n': if (c >= gridNumber) break; addChild(r, c, BLACK, KNIGHT); c++; break;
                case 'b': if (c >= gridNumber) break; addChild(r, c, BLACK, BISHOP); c++; break;
                case 'q': if (c >= gridNumber) break; addChild(r, c, BLACK, QUEEN); c++; break;
                case 'k': if (c >= gridNumber) break; addChild(r, c, BLACK, KING); c++; break;
                case 'p': if (c >= gridNumber) break; addChild(r, c, BLACK, PON); c++; break;
                case '/': r--; c = 0; break;
                default: c++;
            };
        }
    }

    // Transform the position to string representation for faster move generation
    inline const void transformPositonToString() {

        // Clear the current board string position
        this->boardStringPosition.clear();
        for (int r = 0; r < gridNumber; r++) {
            std::vector<char> position;
            for (int c = 0; c < gridNumber; c++){
                // tile piece is not empty or nullptr, add a piece character representation to the board string position
                if (this->allTileInVector[r][c]->Piece != nullptr)
                    position.push_back(ChessMoveGenerator::pieceToString(
                        this->allTileInVector[r][c]->Piece->chessPiece,
                        this->allTileInVector[r][c]->Piece->chessColor));
                // otherwise add space
                else position.push_back(' ');
            }
            this->boardStringPosition.push_back(position);
        }
    }

protected:
    // Initiliaze all objects
    inline const void initAllObjects() {

        // Initialize the Grid Tile
        for (int r = 0; r < gridNumber; r++) {
            std::vector<std::shared_ptr<Tile>> vect;
            for (int c = 0; c < gridNumber; c++) {
                auto tile = std::make_shared<Tile>(this, r, c, gridLayout);
                vect.push_back(tile); gridLayout->addChildren(tile);
            } this->allTileInVector.push_back(vect);
        }
        // Get the position, fill the grid tile
        this->stringToPosition();
        // Add Rectangle to act as a border
        JDM::Window::addComponents( std::make_shared<JDM::Canvas::Rectangle>(
            startX-10, startY-10, 620, 620, JDM::getColorFromHexA(JDM::Color::DEEP_SKY_BLUE)));
        // Add all components
        JDM::Window::addComponents(gridLayout);
        JDM::Window::addComponents(allChessPiece);

        // Will call after the first frame is done
        this->allChessPiece->setFunctionAfterHandle(std::bind([](Chess *chess) { chess->getAllPieceMoves(); }, this ));
    }

    // Update all objects (will be called every frame)
    inline const void update() {}

private:
};

const std::string Chess::WindowTitle = "Chess";
const JDM::ColorRGB Chess::backGround = JDM::getColorFromHex(JDM::Color::SKY_BLUE);
const double Chess::WIDTH = 1200;
const double Chess::HEIGHT = 720;

