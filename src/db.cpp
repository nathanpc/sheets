/**
 * db.cpp
 * Interacts with the database.
 *
 * @author Nathan Campos <nathanpc@dreamintech.net>
 */

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <sqlite3.h>

#include "db.h"

using namespace std;

/**
 * Empty constructor.
 */
DB::DB() {
}

/**
 * Default constructor.
 *
 * @param db_name A SQLite filename.
 */
DB::DB(const char *db_name) {
	set_db_name(db_name);
}

/**
 * Destructor. Closes the database.
 */
DB::~DB() {
	if (db) {
		sqlite3_close(db);
	}
}

/**
 * Sets the database file and opens it.
 *
 * @param db_name a SQLite filename.
 */
void DB::set_db_name(const char *db_name) {
	if (sqlite3_open(db_name, &db)) {
		cout << "Can't open database" << endl;
		exit(EXIT_FAILURE);
	}
}

/**
 * Query something from the database.
 *
 * @param qry A SQL query string.
 * @return A vector of string vectors with the results.
 */
vector<vector<string> > DB::query(const char *qry) {
	sqlite3_stmt *statement;
	vector<vector<string> > results;

	// Check if the query was successful.
	if (sqlite3_prepare_v2(db, qry, -1, &statement, 0) == SQLITE_OK) {
		// Get the amount of columns.
		int cols = sqlite3_column_count(statement);

		while (true) {
			// Check if there's a row.
			if (sqlite3_step(statement) == SQLITE_ROW) {
				vector<string> values;

				// Iterate over each column.
				for (unsigned int col = 0; col < cols; ++col) {
					string value;
					char *cval = (char *)sqlite3_column_text(statement, col);

					// Prevents storing NULL into a std::string, which causes a crash.
					if (cval) {
						value = cval;
					}

					values.push_back(value);
				}

				results.push_back(values);
			} else {
				break;
			}
		}

		// Finalize the query to prevent memory leaks.
		sqlite3_finalize(statement);
	}

	string error = sqlite3_errmsg(db);
	if (error != "not an error") {
		cout << "Error at \"" << qry << "\": " << error << endl;
		exit(EXIT_FAILURE);
	}

	return results;
}
