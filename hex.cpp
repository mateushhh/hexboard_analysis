#include <iostream>
#include <string>

#define MAX_SIZE 11

int columnCounter(std::string line) {
	int columnCounter = 0;
	for (int i = 0; i < line.length(); i++)
		if (line[i] == '>')
			columnCounter += 1;
	return columnCounter;
}

void readBoard(char(*board)[MAX_SIZE], int& boardsize, int& pawnsnumber) {
	std::string line;
	int cursori, cursorj;
	int width = 0, tempj = 1;
	bool upperpart = true;
	bool read = true;
	pawnsnumber = 0;

	for (int i = 0; i < MAX_SIZE; i++) {
		for (int j = 0; j < MAX_SIZE; j++)
			board[i][j] = ' ';
	}

	std::getline(std::cin, line);
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
			else if (line[i] == 'r' || line[i] == 'b') {
				board[cursori][cursorj] = line[i];
				pawnsnumber += 1;
			}
			else if (line[i] == '>') {
				cursori--;
				cursorj++;
			}
		}
	}
	boardsize = width;
}

void drawBoard(char(*board)[MAX_SIZE]) {
	for (int i = 0; i < MAX_SIZE; i++) {
		for (int j = 0; j < MAX_SIZE; j++)
			std::cout << board[i][j] << ',';
		std::cout << '\n';
	}
}

int main() {
	char board[MAX_SIZE][MAX_SIZE];
	int boardsize, pawnsnumber;
	std::string command;

	//readBoard(board, boardsize, pawnsnumber);
	//drawBoard(board);

	while (std::getline(std::cin, command)) {
		command.erase(std::remove_if(command.begin(), command.end(), ::isspace), command.end());
		if (command == "---")
			readBoard(board, boardsize, pawnsnumber);
		else if (command == "BOARD_SIZE")
			std::cout << boardsize << '\n';
		else if (command == "PAWNS_NUMBER")
			std::cout << pawnsnumber << '\n';
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
	 --< b >-<   >--
	<   >-< b >-<   >
	 --<   >-< r >--
		--< r >--
		   ---
	*/

