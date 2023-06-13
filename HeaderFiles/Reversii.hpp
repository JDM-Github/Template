#pragma once
#include "JDM/JDM.hpp"

static int numOfMoves = 0;

// WHITE IS ALWAYS FIRST
class ReversiiMoveGenerator {
public:
    static const void printBoard(std::vector<std::vector<char>> position) {
        for (int r = 0; r < 8; r++) {
            std::cout << '|';
            for (int c = 0; c < 8; c++) std::cout << ' ' << position[r][c] << " |";
            std::cout << '\n';
        }
    }
    static const bool isTileNotOutOfBounds(int row, int col) { return ((8 > col && col >= 0) && (8 > row && row >= 0)); }
	static const bool isTileFree(const std::vector<std::vector<char>> &position, int row, int col) {
        return (ReversiiMoveGenerator::isTileNotOutOfBounds(row, col) && (position[row][col] == ' '));
    }
	static const bool isTileDifferentColor(const std::vector<std::vector<char>> &position, int row, int col) {
        return (ReversiiMoveGenerator::isTileNotOutOfBounds(row, col) && position[row][col] != ' ' &&
			position[row][col] == ((numOfMoves % 2 == 0) ? 'B' : 'W'));
    }
    static const void moveContinously(
		std::vector<std::vector<char>> &position, int row, int col,
        std::vector<std::pair<int, int>> &allPossibleMoves,int max, bool isDiagonal) {
		bool fourWay[] = {false, false, false, false};
        auto checkBoard = [&](int c, int r, int i) {
            if (ReversiiMoveGenerator::isTileFree(position, r, c) && i >= 2) { allPossibleMoves.push_back(std::make_pair(r, c)); return false; }
            else if (ReversiiMoveGenerator::isTileDifferentColor(position, r, c)) return true;
            else return false;
        };
        for (int i = 1; i <= max; i++) { 
			if (!fourWay[0] && !checkBoard(col+i, row+ (isDiagonal ? i : 0), i))                       fourWay[0] = true;
			if (!fourWay[1] && !checkBoard(col-i, row+ (isDiagonal ? i : 0), i))                       fourWay[1] = true;
			if (!fourWay[2] && !checkBoard(col+ (isDiagonal ? i : 0), row + (isDiagonal ? -i : i), i)) fourWay[2] = true;
			if (!fourWay[3] && !checkBoard(col+ (isDiagonal ? -i : 0), row-i, i))                      fourWay[3] = true;
		}
	}
};

class Reversii {
public:
    static const std::string WindowTitle;
    static const JDM::ColorRGB backGround;
    static const double WIDTH;
    static const double HEIGHT;

    bool moving = false;
    const float blockSize = ((490 - (7 * 5)) / 8);
    std::string position = "///   WB/   BW////";

private:
    std::shared_ptr<JDM::Layout::GridLayout> board = std::make_shared<JDM::Layout::GridLayout>(150, 50, 500, 500, 8, 8, 5, 5, 5);
    std::shared_ptr<JDM::Layout::FloatLayout> allCircle = std::make_shared<JDM::Layout::FloatLayout>();
    std::vector<std::vector<char>> stringPosition;
    std::vector<std::pair<int, int>> allPossibleMoves;

    class Circle : public JDM::Comp::Image {
    public:
        int row, col;
        char colorCircle = ' ';
        Circle(Reversii *reversi, int r, int c, char color)
        : colorCircle(color), JDM::Comp::Image(
            CircleImage, 155+(reversi->blockSize*c)+(6*c), 55+(reversi->blockSize*r)+(6*r),
                              reversi->blockSize, reversi->blockSize,
                (color == 'W') ? JDM::getColorFromHexA("dddddd") : JDM::getColorFromHexA("111111")) {
            this->row = r;
            this->col = c;
        }
    };

    class Tile: public JDM::Canvas::Rectangle {
    public:
        int row, col;
        Reversii *reversii = nullptr;
        std::shared_ptr<Circle> circle;
        Tile(int r, int c, Reversii *reversi)
        : reversii(reversi), JDM::Canvas::Rectangle(0, 0, 0, 0, ((r + c) % 2)
                ? JDM::getColorFromHexA("008000")
                : JDM::getColorFromHexA("009b00")) {
            this->row = r;
            this->col = c;

            this->setmouseDownFunction(std::bind([](Tile *tile, Reversii *reversi) {
                if (tile->circle == nullptr && reversi->isPairInVector(reversi->allPossibleMoves, tile->row, tile->col)) {
                    reversi->moving = true;
                    auto circ = std::make_shared<Circle>(reversi, tile->row, tile->col, (numOfMoves % 2 == 0) ? 'W' : 'B');
                    tile->circle = circ;
                    reversi->allCircle->addChildren(circ);

                    std::vector<std::pair<int, int>> allColorThatWillBeTurned[8];

                    auto setAllRGBColor = [&](int row, int col) {
                        uint8_t target = (numOfMoves % 2 == 0) ? 0xdd : 0x11;
                        JDM::Window::addStartAnimation(std::make_shared<JDM::Animation<uint8_t>>(
                            reversi->allTileInVector[row][col]->circle->getPointerRImage(), target, 0.3, true,
                            std::bind([](std::shared_ptr<Circle> circle) {
                                circle->setWillUpdateImageColor(true);
                            }, reversi->allTileInVector[row][col]->circle)));
                        JDM::Window::addStartAnimation(std::make_shared<JDM::Animation<uint8_t>>(
                            reversi->allTileInVector[row][col]->circle->getPointerGImage(), target, 0.3, true,
                            std::bind([](std::shared_ptr<Circle> circle) {
                                circle->setWillUpdateImageColor(true);
                            }, reversi->allTileInVector[row][col]->circle)));
                        JDM::Window::addStartAnimation(std::make_shared<JDM::Animation<uint8_t>>(
                            reversi->allTileInVector[row][col]->circle->getPointerBImage(), target, 0.3, true,
                            std::bind([](std::shared_ptr<Circle> circle) {
                                circle->setWillUpdateImageColor(true);
                            }, reversi->allTileInVector[row][col]->circle)));
                        reversi->allTileInVector[row][col]->circle->colorCircle = (numOfMoves % 2 == 0) ? 'W' : 'B';
                    };
                    auto checkIfWillBeTurned = [&](int row, int col, int i) {
                        if (ReversiiMoveGenerator::isTileDifferentColor(reversi->stringPosition, row, col)) {
                            allColorThatWillBeTurned[i].push_back(std::make_pair(row, col)); return true;
                        } else if (ReversiiMoveGenerator::isTileFree(reversi->stringPosition, row, col)) {
                            allColorThatWillBeTurned[i].clear(); return false;
                        } return false;
                    };
                    bool allDirection[] = {true, true, true, true, true, true, true, true};
                    for (int i = 1; i < 8; i++) {
                        if (allDirection[0] && !checkIfWillBeTurned(tile->row-i, tile->col  , 0)) allDirection[0] = false;
                        if (allDirection[1] && !checkIfWillBeTurned(tile->row+i, tile->col  , 1)) allDirection[1] = false;
                        if (allDirection[2] && !checkIfWillBeTurned(tile->row-i, tile->col-i, 2)) allDirection[2] = false;
                        if (allDirection[3] && !checkIfWillBeTurned(tile->row-i, tile->col+i, 3)) allDirection[3] = false;
                        if (allDirection[4] && !checkIfWillBeTurned(tile->row+i, tile->col-i, 4)) allDirection[4] = false;
                        if (allDirection[5] && !checkIfWillBeTurned(tile->row+i, tile->col+i, 5)) allDirection[5] = false;
                        if (allDirection[6] && !checkIfWillBeTurned(tile->row, tile->col-i  , 6)) allDirection[6] = false;
                        if (allDirection[7] && !checkIfWillBeTurned(tile->row, tile->col+i  , 7)) allDirection[7] = false;
                    }
                    for (int i = 0; i < 8; i++) {
                    for (const auto &pair: allColorThatWillBeTurned[i])
                        setAllRGBColor(pair.first, pair.second);
                    }
                    JDM::Window::addStartClock(std::make_shared<JDM::Clock>(0.31, true,
                        std::bind([](Reversii *reversi) {
                            numOfMoves++;
                            reversi->moving = false;
                            reversi->positionToString();
                            reversi->generateAllPossibleMove();
                        }, reversi)
                    ));
                }
            }, this, this->reversii));
        }
    };
    std::vector<std::vector<std::shared_ptr<Tile>>> allTileInVector;

    const bool isPairInVector(const std::vector<std::pair<int, int>>& vec, int first, int second) {
        for (const auto& pair : vec)  if (pair.first == first && pair.second == second) return true;
        return false;
    }
    const void stringToPosition() {
        int row = 0, col = 0; 
        auto addCircle = [&](int r, int c, char color) {
            auto circ = std::make_shared<Circle>(this, r, c, color);
            allTileInVector[r][c]->circle = circ;
            allCircle->addChildren(circ);
        };
        for (const auto &ch: position) {
            switch (ch) {
                case 'W': if (col < 8) addCircle(row, col, 'W'); col++; break;
                case 'B': if (col < 8) addCircle(row, col, 'B'); col++; break;
                case '/': row++; col = 0; break;
                default: col++;
            }; if (col > 8) { row++; col = 0; }}
    }
    const void positionToString() {
        stringPosition.clear();
        for (int r = 0; r < 8; r++) {
            std::vector<char> vecChar;
            for (int c = 0; c < 8; c++) {
                if (allTileInVector[r][c]->circle != nullptr) vecChar.push_back(allTileInVector[r][c]->circle->colorCircle);
                else vecChar.push_back(' ');
            } stringPosition.push_back(vecChar);
        } ReversiiMoveGenerator::printBoard(stringPosition);
    }
    const void generateAllPossibleMove() {
        static bool already = true;
        this->allPossibleMoves.clear();
        for (const auto &tiles: allTileInVector) {
            for (const auto &tile: tiles) {
                if (tile->circle != nullptr && tile->circle->colorCircle == ((numOfMoves % 2 == 0) ? 'W' : 'B')) {
                    ReversiiMoveGenerator::moveContinously(stringPosition, tile->row, tile->col, allPossibleMoves, 8, false);
                    ReversiiMoveGenerator::moveContinously(stringPosition, tile->row, tile->col, allPossibleMoves, 8, true);
                }
            }
        }
        if (!already) { /* This block of code still incomplete, this will handle TIE */ moving = false; return; }
        if (allPossibleMoves.size() <= 0) { /* Skips Turn if no possible move */ already = false; numOfMoves++; this->generateAllPossibleMove(); }
    }
protected:
    const void initAllObjects() {
        for (int r = 0; r < 8; r++) {
        std::vector<std::shared_ptr<Tile>> tiles;
        for (int c = 0; c < 8; c++) {
            auto tile = std::make_shared<Tile>(7-r, 7-c, this);
            tiles.insert(tiles.begin(), tile);
            board->addChildren(tile);
        } allTileInVector.insert(allTileInVector.begin(), tiles); }

        this->stringToPosition();
        this->positionToString();
        this->generateAllPossibleMove();
        JDM::Window::addComponents(std::make_shared<JDM::Canvas::Rectangle>(
            150, 50, 500, 500, JDM::getColorFromHexA("004c00")));
        JDM::Window::addComponents(board);
        JDM::Window::addComponents(allCircle);
    }
    const void update() { }
};
const std::string Reversii::WindowTitle = "Reversii";
const JDM::ColorRGB Reversii::backGround = JDM::getColorFromHex(JDM::Color::DARK_GREEN);
const double Reversii::WIDTH = 800; 
const double Reversii::HEIGHT = 700;
