/**
 * dir_parse.cpp
 * Parse the directory.
 *
 * @author Nathan Campos <nathanpc@dreamintech.net>
 */

#include <iostream>
#include <string>
#include <cstdlib>
#include <boost/filesystem.hpp>

#include "dir_parse.h"

using namespace std;
namespace fs = boost::filesystem;


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
