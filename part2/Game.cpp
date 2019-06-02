#include "Game.hpp"

using namespace utils;
/*--------------------------------------------------------------------------------
				    C'tor, D'tor and Accessor functions
--------------------------------------------------------------------------------*/
Game::Game(game_params gp) { // TODO: complete.
	vector<string> lines;
	lines = read_lines(gp.filename);

	vector<string> cells_per_line_str;

	for (const string &line : lines) {
		cells_per_line_str = split(line, ' ');
		vector<int> cells_per_line_int;

		for (const string &cell_str : cells_per_line_str) {
			int cell_int;
			cell_int = atoi(cell_str.c_str());
			cells_per_line_int.push_back(cell_int);
		}
		field.push_back(cells_per_line_int);
	}
	field_height = field.size();
	field_width = field[0].size();

	m_gen_num = gp.n_gen;
	m_thread_num = gp.n_thread;
	interactive_on = gp.interactive_on;
	print_on = gp.print_on;

	// TODO: need to initialize synchronization stuff here
}

Game::~Game() {} // TODO
const vector<double> Game::gen_hist() const {} // Returns the generation timing histogram // TODO
const vector<tile_record> Game::tile_hist() const {} // Returns the tile timing histogram // TODO
uint Game::thread_num() const {} //Returns the effective number of running threads = min(thread_num, field_height) // TODO

/*--------------------------------------------------------------------------------
					Main Logic Functions
--------------------------------------------------------------------------------*/
void Game::run() {

	_init_game(); // Starts the threads and all other variables you need // TODO
	print_board("Initial Board"); // TODO
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

	// Create game fields - Consider using utils:read_file, utils::split
	// Create & Start threads
	// Testing of your implementation will presume all threads are started here
}

void Game::_step(uint curr_gen) { // TODO
	// Push jobs to queue
	// Wait for the workers to finish calculating 
	// Swap pointers between current and next field 
	// NOTE: Threads must not be started here - doing so will lead to a heavy penalty in your grade 
}

void Game::_destroy_game(){ // TODO
	// Destroys board and frees all threads and resources 
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



