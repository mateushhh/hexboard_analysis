﻿#include <iostream>
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

	int isGameOver() {
		if (!isBoardCorrect())
			return 0;

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
		else if (command == "BOARD_SIZE")
			std::cout << board.boardSize() << '\n';
		else if (command == "PAWNS_NUMBER")
			std::cout << board.pawnsNumber() << '\n';
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
	}
	return 0;
}

/*
TODO List:
(8 %)	BOARD_SIZE - (test 1)
(8 %)	PAWNS_NUMBER - (test 2)
(8 %)	IS_BOARD_CORRECT - (test 3)
(20 %)	IS_GAME_OVER - (test 4)
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
