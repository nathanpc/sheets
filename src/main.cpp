/**
 * Sheets
 * A tool to quickly organize, browse, and search for your datasheets.
 *
 * @author Nathan Campos <nathanpc@dreamintech.net>
 */

#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <boost/filesystem.hpp>

#include "dir_parse.h"
#include "db.h"
#include "color.h"

using namespace std;
namespace fs = boost::filesystem;

void usage() {
	cout << BOLDWHITE << "Usage: " << RESET << "sheets [-i|-s] directory|term" << endl << endl;

	cout << BOLDWHITE << "Commands:" << RESET << endl;
	cout << "    -i(index)\t  Indexes a directory" << endl;
	cout << "    -s(search)\t  Search for a datasheet using a term" << endl;
}

void index(const char *directory) {
	// Setup the directories stuff.
	Dir_Parse dir(directory);
	dir.iterate();

	// Setup the database stuff.
	DB db("datasheets.db");
	db.query("DROP TABLE IF EXISTS datasheets;");
	db.query("CREATE TABLE datasheets(id integer primary key, path text, tags text);");

	// Index everything.
	for (size_t i = 0; i < dir.datasheets.size(); ++i) {
		vector<string> datasheet = dir.datasheets[i];

		string qry = "INSERT INTO datasheets VALUES(NULL, \"" + datasheet[0] + "\", \"" + datasheet[1] + "\");";
		db.query(qry.c_str());

		cout << BOLDGREEN << "Indexed: " << RESET << dir.trim_path(datasheet[0]) << endl;
	}

	cout << endl << BOLDBLUE << "Successfully indexed " << dir.datasheets.size() << " datasheets." << RESET << endl;
}

int main(int argc, char *argv[]) {
	// TODO: Store the database inside the config dir at ~

	// Check if there's at least one argument.
	if (argc == 1) {
		usage();
		return 1;
	}

	// Check if the user just typed the directory with no commands.
	if (argv[1][0] != '-' && strcmp(argv[1], "index") != 0 && strcmp(argv[1], "search") != 0) {
		if (fs::is_directory(argv[1])) {
			index(argv[1]);
		}
	}

	// The usual argument parsing stuff.
	if (strcmp(argv[1], "-i") == 0 || strcmp(argv[1], "index") == 0) {
		index(argv[1]);
	} else if (strcmp(argv[1], "-s") == 0 || strcmp(argv[1], "search") == 0) {
		cout << "Search for: " << argv[1] << endl;
	} else {
		usage();
		return 1;
	}

	return 0;
}
