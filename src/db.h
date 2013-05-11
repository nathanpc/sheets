/**
 * db.h
 * Interacts with the database.
 *
 * @author Nathan Campos <nathanpc@dreamintech.net>
 */

#ifndef SHEETS_DB_H_
#define SHEETS_DB_H_

#include <string>
#include <vector>
#include <sqlite3.h>

class DB {
	private:
		sqlite3 *db;

	public:
		// Constructors
		DB();
		DB(const char *db_name);

		// Destructor
		~DB();

		// Setters
		void set_db_name(const char *db_name);

		// DB Operations.
		std::vector<std::vector<std::string> > query(const char *qry);
};

#endif
