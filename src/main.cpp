/**
 * Sheets
 * A tool to quickly organize, browse, and search for your datasheets.
 *
 * @author Nathan Campos <nathanpc@dreamintech.net>
 */

#include <iostream>
#include <vector> // REMOVE
#include <string> // REMOVE

#include "dir_parse.h"
#include "db.h"
#include "color.h"
using namespace std;

int main(int argc, char *argv[]) {
	// TODO: Parse command-line stuff.
	// TODO: Store the database inside the config dir at ~

	// Setup the directories stuff.
	Dir_Parse dir(argv[1]);
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

	return 0;
}
