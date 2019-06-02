#include <utility>

#include "Game.hpp"

using namespace utils;

template <typename T>
void swap_pointers(T* field_a , T* field_b);

/*--------------------------------------------------------------------------------
				    C'tor, D'tor and Accessor functions
--------------------------------------------------------------------------------*/
Game::Game(game_params gp) : gp(std::move(gp)) {
}

Game::~Game() {} // TODO

const vector<double> Game::gen_hist() const {
	return this->m_gen_hist;
}

const vector<tile_record> Game::tile_hist() const {
	return this->m_tile_hist;
}

uint Game::thread_num() const {
	return this->m_thread_num;
}

/*--------------------------------------------------------------------------------
					Main Logic Functions
--------------------------------------------------------------------------------*/
void Game::run() {

	_init_game(); // Starts the threads and all other variables you need // TODO
	print_board("Initial Board");
	for (uint i = 0; i < m_gen_num; ++i) {
		auto gen_start = std::chrono::system_clock::now();
		_step(i); // Iterates a single generation // TODO
		auto gen_end = std::chrono::system_clock::now();
		m_gen_hist.push_back((double)std::chrono::duration_cast<std::chrono::microseconds>(gen_end - gen_start).count());
		print_board(nullptr);
	} // generation loop
	print_board("Final Board");
	_destroy_game(); // TODO
}

void Game::_init_game() { // TODO
	m_gen_num = gp.n_gen;
	m_thread_num = gp.n_thread;
	interactive_on = gp.interactive_on;
	print_on = gp.print_on;

	// Create game fields - Consider using utils:read_file, utils::split
	vector<string> lines;
	lines = read_lines(gp.filename);

	vector<string> cells_per_line_str;
	vector<int> cells_per_line_int;
	vector<vector<int>> field;

	for (const string &line : lines) {
		cells_per_line_str = split(line, ' ');
		cells_per_line_int.clear();

		for (const string &cell_str : cells_per_line_str) {
			int cell_int;
			cell_int = atoi(cell_str.c_str());
			cells_per_line_int.push_back(cell_int);
		}
		field.push_back(cells_per_line_int);
	}
	field_height = field.size();
	field_width = field[0].size();

	curr_field = new vector<vector<int>>(field);
	next_field = new vector<vector<int>>(field);

	// Create & Start threads
	// Testing of your implementation will presume all threads are started here
}

void Game::_step(uint curr_gen) { // TODO
	// Push jobs to queue
	// Wait for the workers to finish calculating
	for (int i = 0; i < field_height; i++) {
		for (int j = 0; j < field_width; j++) {
			int live_neighbors = calc_live_neighbors(i, j);

			if ((live_neighbors == 3) ||
				(live_neighbors == 2 && (*curr_field)[i][j] == 1)) {
				(*next_field)[i][j] = 1;
			} else {
				(*next_field)[i][j] = 0;
			}
		}
	}
	// Swap pointers between current and next field
	swap(curr_field, next_field); // TODO: make sure it works
	// NOTE: Threads must not be started here - doing so will lead to a heavy penalty in your grade 
}

void Game::_destroy_game(){ // TODO
	// Destroys board and frees all threads and resources
	delete curr_field;
	delete next_field;
	// TODO: threads
	// Not implemented in the Game's destructor for testing purposes. 
	// All threads must be joined here
	for (uint i = 0; i < m_thread_num; ++i) {
        m_threadpool[i]->join();
    }
}

/*--------------------------------------------------------------------------------
					Auxiliary functions
--------------------------------------------------------------------------------*/
inline void Game::print_board(const char* header) {

	if(print_on){ 

		// Clear the screen, to create a running animation 
		if(interactive_on)
			system("clear");

		// Print small header if needed
		if (header != nullptr)
			cout << "<------------" << header << "------------>" << endl;

		vector<vector<int>> &field = *curr_field;
		// TODO: Print the board
		cout << u8"╔" << string(u8"═") * field_width << u8"╗" << endl;
		for (uint i = 0; i < field_height; ++i) {
			cout << u8"║";
			for (uint j = 0; j < field_width; ++j) {
				cout << (field[i][j] ? u8"█" : u8"░");
			}
			cout << u8"║" << endl;
		}
		cout << u8"╚" << string(u8"═") * field_width << u8"╝" << endl;

		// Display for GEN_SLEEP_USEC micro-seconds on screen 
		if(interactive_on)
			usleep(GEN_SLEEP_USEC);
	}
}

int Game::calc_live_neighbors(int row, int col) {

	int live_neighbors_counter = 0;

	for (int i = row - 1; i <= row + 1; i++) {
		for (int j = col - 1; j <= col +1; j++) {
			if (i >= 0 && i < field_height && j >= 0 && j < field_width) {
				live_neighbors_counter += (*curr_field)[i][j];
			}
		}
	}
	return live_neighbors_counter - (*curr_field)[row][col];
}

