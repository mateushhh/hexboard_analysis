#include <iostream>
#include <string>
#include <algorithm>

#define MAX_SIZE 11
#define RED 1
#define BLUE 2

class Board {
public:
	char board[MAX_SIZE][MAX_SIZE];
	int size;
	int bpawns;
	int rpawns;

	Board() {
		size = 1;
		bpawns = 0;
		rpawns = 0;
		for (int i = 0; i < MAX_SIZE; i++) {
			for (int j = 0; j < MAX_SIZE; j++)
				board[i][j] = ' ';
		}
	}

	int columnCounter(std::string line) {
		int columnCounter = 0;
		for (int i = 0; i < line.length(); i++)
			if (line[i] == '>')
				columnCounter += 1;
		return columnCounter;
	}

	void read() {
		std::string line;
		int cursori, cursorj;
		int width = 0, tempj = 1;
		bool upperpart = true;
		bool read = true;
		rpawns = 0;
		bpawns = 0;

		for (int i = 0; i < MAX_SIZE; i++) {
			for (int j = 0; j < MAX_SIZE; j++)
				board[i][j] = ' ';
		}

		while (read) {
			std::getline(std::cin, line);
			if (width < columnCounter(line)) {
				width = columnCounter(line);
			}
			else {
				upperpart = false;
			}

			if (upperpart) {
				cursori = width - 1;
				cursorj = 0;
			}
			else {
				cursori = width - 1;
				cursorj = tempj++;
			}

			for (int i = 0; i < line.length(); i++) {
				if (line[i] == '-' && line[i - 1] == '-' && line[i - 2] == '-') {
					read = false;
					break;
				}
				else if (line[i] == 'r') {
					board[cursori][cursorj] = 'r';
					rpawns += 1;
				}
				else if (line[i] == 'b') {
					board[cursori][cursorj] = 'b';
					bpawns += 1;
				}
				else if (line[i] == '>') {
					cursori--;
					cursorj++;
				}
			}
		}
		size = width;
	}

	void draw() {
		for (int i = 0; i < MAX_SIZE; i++) {
			for (int j = 0; j < MAX_SIZE; j++)
				std::cout << board[i][j] << ',';
			std::cout << '\n';
		}
	}

	int pawnsNumber() {
		return (bpawns + rpawns);
	}

	int boardSize() {
		return size;
	}

	int emptyNumber() {
		int empty_spots = 0;
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if (board[i][j] == ' ')
					empty_spots++;
			}
		}
		return empty_spots;
	}

	bool isBoardCorrect() {
		return ((rpawns - 1 == bpawns) || (rpawns == bpawns));
	}

	bool lookForPath(char color, int i, int j, int(*checkedPosBoard)[MAX_SIZE]) {
		checkedPosBoard[i][j] = 1;

		//end checks
		if (board[i][j] != color)
			return false;
		else if (j == size - 1 && color == 'r')
			return true;
		else if (i == size - 1 && color == 'b')
			return true;

		//check for all neighbours
		if (i - 1 >= 0 && j - 1 >= 0 && checkedPosBoard[i - 1][j - 1] == 0) {
			if (lookForPath(color, i - 1, j - 1, checkedPosBoard)) { return true; }
		}
		if (i - 1 >= 0 && j >= 0 && checkedPosBoard[i - 1][j] == 0) {
			if (lookForPath(color, i - 1, j, checkedPosBoard)) { return true; }
		}
		if (i >= 0 && j - 1 >= 0 && checkedPosBoard[i][j - 1] == 0) {
			if (lookForPath(color, i, j - 1, checkedPosBoard)) { return true; }
		}
		if (i >= 0 && j + 1 < size && checkedPosBoard[i][j + 1] == 0) {
			if (lookForPath(color, i, j + 1, checkedPosBoard)) { return true; }
		}
		if (i + 1 < size && j >= 0 && checkedPosBoard[i + 1][j] == 0) {
			if (lookForPath(color, i + 1, j, checkedPosBoard)) { return true; }
		}
		if (i + 1 < size && j + 1 < size && checkedPosBoard[i + 1][j + 1] == 0) {
			if (lookForPath(color, i + 1, j + 1, checkedPosBoard)) { return true; }
		}
		return false;
	}

	int checkWin() {
		int checkedPosBoard[MAX_SIZE][MAX_SIZE];

		//check for red
		for (int i = 0; i < MAX_SIZE; i++) {
			for (int j = 0; j < MAX_SIZE; j++)
				checkedPosBoard[i][j] = 0;
		}

		for (int i = 0; i < size; i++) {
			if (board[i][0] == 'r') {
				if (this->lookForPath('r', i, 0, checkedPosBoard))
					return RED;
			}
		}

		//check for blue
		for (int i = 0; i < MAX_SIZE; i++) {
			for (int j = 0; j < MAX_SIZE; j++)
				checkedPosBoard[i][j] = 0;
		}

		for (int j = 0; j < size; j++) {
			if (board[0][j] == 'b') {
				if (this->lookForPath('b', 0, j, checkedPosBoard))
					return BLUE;
			}
		}

		return 0;
	}

	int isGameOver() {
		if (!isBoardCorrect())
			return 0;

		return checkWin();
	}

	bool isBoardPossible() {
		if (!isBoardCorrect())
			return false;
		if (!isGameOver()) {
			return true;
		}
		if (isGameOver() == RED) {
			if (rpawns - 1 != bpawns)
				return false;
			for (int i = 0; i < MAX_SIZE; i++) {
				for (int j = 0; j < MAX_SIZE; j++) {
					if (board[i][j] == 'r') {
						board[i][j] = ' ';
						if (!isGameOver()) {
							board[i][j] = 'r';
							return true;
						}
						board[i][j] = 'r';
					}
				}
			}
		}
		if (isGameOver() == BLUE) {
			if (rpawns != bpawns)
				return false;
			for (int i = 0; i < MAX_SIZE; i++) {
				for (int j = 0; j < MAX_SIZE; j++) {
					if (board[i][j] == 'b') {
						board[i][j] = ' ';
						if (!isGameOver()) {
							board[i][j] = 'b';
							return true;
						}
						board[i][j] = 'b';
					}
				}
			}
		}
		return false;
	}
	
	int whose_turn() {
		if (rpawns == bpawns)
			return RED;
		else if (rpawns - 1 == bpawns)
			return BLUE;
		return 0;
	}

	bool winNaive(int color, int n) {

		if (!isBoardPossible())
			return false;
		else if (isGameOver())
			return false;

		if (whose_turn() != color && emptyNumber() == 1)
			return false;

		char pawn;
		int moves = 1;
		if (color == RED)
			pawn = 'r';
		else
			pawn = 'b';

		if (whose_turn() == color && n == 1)
			moves = 1;
		else if (whose_turn() != color && n == 1)
			moves = 2;
		else if (whose_turn() == color && n == 2)
			moves = 3;
		else if (whose_turn() != color && n == 2)
			moves = 4;

		if (moves > emptyNumber())
			return false;

		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if (board[i][j] == ' ') {
					board[i][j] = pawn;
					moves -= 2;
					if (checkWin() == color) {
						board[i][j] = ' ';
						if (n == 1)
							return true;
					}
					else if (n == 2 && emptyNumber() - 1 >= moves) {
						for (int x = 0; x < size; x++) {
							for (int y = 0; y < size; y++) {
								if (board[x][y] == ' ') {
									board[x][y] = pawn;
									if (checkWin() == color) {
										board[i][j] = ' ';
										board[x][y] = ' ';
										return true;
									}
									board[x][y] = ' ';
								}
							}
						}
					}
					board[i][j] = ' ';
				}
			}
		}
		return false;
	}
};

 
int main() {
	Board board;
	std::string command;

	while (std::getline(std::cin, command)) {
		command.erase(std::remove_if(command.begin(), command.end(), ::isspace), command.end());
		if (command == "---")
			board.read();
		else if (command == "DRAW")
			board.draw();

		else if (command == "BOARD_SIZE") {
			std::cout << board.boardSize() << '\n';
		}
		else if (command == "PAWNS_NUMBER") {
			std::cout << board.pawnsNumber() << '\n';
		}
		else if (command == "IS_BOARD_CORRECT") {
			if (board.isBoardCorrect())
				std::cout << "YES\n";
			else
				std::cout << "NO\n";
		}
		else if (command == "IS_GAME_OVER") {
			if (board.isGameOver())
				if (board.isGameOver() == RED)
					std::cout << "YES RED\n";
				else
					std::cout << "YES BLUE\n";
			else
				std::cout << "NO\n";
		}
		else if (command == "IS_BOARD_POSSIBLE") {
			if (board.isBoardPossible())
				std::cout << "YES\n";
			else
				std::cout << "NO\n";
		}
		else if (command == "CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT") {
			if(board.winNaive(RED, 1 ))
				std::cout << "YES\n";
			else
				std::cout << "NO\n";
		}
		else if (command == "CAN_BLUE_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT") {
			if (board.winNaive(BLUE, 1))
				std::cout << "YES\n";
			else
				std::cout << "NO\n";
		}
		else if (command == "CAN_RED_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT") {
			if (board.winNaive(RED, 2))
				std::cout << "YES\n";
			else
				std::cout << "NO\n";
		}
		else if (command == "CAN_BLUE_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT") {
			if (board.winNaive(BLUE, 2))
				std::cout << "YES\n";
			else
				std::cout << "NO\n";
		}
	}
	return 0;
}


/*
TODO List:
(20 %)	IS_BOARD_POSSIBLE - (test 5)
(20 %)	CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT - (test 6)
		CAN_BLUE_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT
		CAN_RED_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT
		CAN_BLUE_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT
(16 %)	CAN_RED_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT
		CAN_BLUE_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT
		CAN_RED_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT
		CAN_BLUE_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT

	   ---
	--< r >--
 --< b >-< b >--
<   >-< r >-<   >
 --< r >-< r >--
	--< b >--
	   ---
*/
