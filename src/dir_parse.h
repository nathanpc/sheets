/**
 * dir_parse.h
 * Parse the directory.
 *
 * @author Nathan Campos <nathanpc@dreamintech.net>
 */

#ifndef SHEETS_DIR_PARSE_H_
#define SHEETS_DIR_PARSE_H_

#include <string>
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;


class Dir_Parse {
	private:
		fs::path root;

	public:
		Dir_Parse(const char *dir);
};

#endif
