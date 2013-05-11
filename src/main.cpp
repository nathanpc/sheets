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
using namespace std;

int main(int argc, char *argv[]) {
	Dir_Parse dir(argv[1]);
	dir.iterate();

	/*DB db("test.db");
	vector<vector<string> > result = db.query("SELECT * FROM parts");
	for (vector<vector<string> >::iterator it = result.begin(); it < result.end(); ++it) {
		vector<string> row = *it;
		cout << "ID: " << row[0] << endl
			<< "Path: " << row[1] << endl
			<< "Tags: " << row[2] << endl << endl;
	}*/

	return 0;
}
