/**
 * dir_parse.cpp
 * Parse the directory.
 *
 * @author Nathan Campos <nathanpc@dreamintech.net>
 */

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <boost/filesystem.hpp>

#include "dir_parse.h"

using namespace std;
namespace fs = boost::filesystem;


/**
 * Empty constructor.
 */
Dir_Parse::Dir_Parse() {
}

/**
 * Default constructor.
 *
 * @param dir Root directory.
 */
Dir_Parse::Dir_Parse(const char *dir) {
	root = fs::path(dir);

	// Check existance.
	if (!fs::exists(root)) {
		cout << "Directory not found: " << root << endl;
		exit(EXIT_FAILURE);
	}

	// Check if the path leads to a file instead of a directory.
	if (fs::is_regular_file(root)) {
		// Why the hell are you pointing me to a file?!
		cout << "You should point me to a directory, not a file." << endl;
		exit(EXIT_FAILURE);
	}
}

/**
 * Sets the root directory.
 *
 * @param dir Root directory.
 */
void Dir_Parse::set_root(const char *dir) {
	root =  fs::path(dir);
}

/**
 * Iterate over a directory.
 *
 * @param dir Directory to iterate over.
 */
void Dir_Parse::iterate(fs::path dir) {
	fs::directory_iterator end_iter;
	vector<fs::path> dirs;

	#ifdef DEBUG
	cout << endl << "==== " << string(dir.relative_path().c_str()).substr(cut_path) << " ===="  << endl;
	#endif

	for (fs::directory_iterator dir_itr(dir); dir_itr != end_iter; ++dir_itr) {
		try {
			// Ignore hidden directories.
			if (dir_itr->path().filename().c_str()[0] != '.') {
				if (fs::is_directory(dir_itr->status())) {
					// Directory
					#ifdef DEBUG
					cout << dir_itr->path().filename() << " - Directory" << endl;
					#endif

					dirs.push_back(dir_itr->path());
				} else if (fs::is_regular_file(dir_itr->status())) {
					// File
					#ifdef DEBUG
					cout << dir_itr->path().filename() << " - File" << endl;
					#endif
				}
				#ifdef DEBUG
				else {
					// Other
					cout << dir_itr->path().filename() << ": WTF is this?!" << endl;
				}
				#endif
			}
		} catch (const exception &e) {
			cout << dir_itr->path().filename() << ": " << e.what() << endl;
		}
	}

	for (size_t i = 0; i < dirs.size(); ++i) {
		iterate(dirs[i]);
	}
}

/**
 * Iterate over the root directory.
 */
void Dir_Parse::iterate() {
	// Set the root path length to remove from the others to get just the tags.
	cut_path = string(root.relative_path().c_str()).length();
	iterate(root);
}
