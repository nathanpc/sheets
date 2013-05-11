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
#include <boost/algorithm/string.hpp>

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
					vector<string> datasheet;
					vector<string> tags = get_tags(dir_itr->path());

					datasheet.push_back("/" + string(dir_itr->path().c_str()));  // TODO: Check if this assumption (adding the "/") is correct.
					datasheet.push_back(boost::algorithm::join(tags, ","));

					datasheets.push_back(datasheet);

					#ifdef DEBUG
					cout << trim_path(dir_itr->path()) << endl;
					cout << dir_itr->path().filename() << " - File" << endl;

					for (size_t i = 0; i < tags.size(); ++i) {
						cout << tags[i];

						if (i < tags.size() - 1) {
							cout << ", ";
						} else {
							cout << endl << endl;
						}
					}
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
	// Clear the datasheets vector.
	datasheets.clear();

	// Set the root path length to remove from the others to get just the tags.
	cut_path = string(root.relative_path().c_str()).length();
	iterate(root);
}

/**
 * Get the tags based on the directory structure.
 *
 * @param path Path to a file.
 * @return A vector of tags.
 */
vector<string> Dir_Parse::get_tags(const fs::path path) {
	vector<string> tags;
	string str_path = trim_path(path);

	// Remove everything we don't want.
	boost::trim_if(str_path, boost::is_any_of("/"));
	str_path = str_path.substr(0, str_path.find(path.extension().c_str()));

	// Split and return.
	boost::split(tags, str_path, boost::is_any_of("/"));
	return tags;
}

/**
 * Removes the absolute path and keeps just the relative (to root) path.
 *
 * @param path A path.
 * @return Relative path.
 */
const char* Dir_Parse::trim_path(const fs::path path) {
	return string(path.c_str()).substr(cut_path).c_str();
}
