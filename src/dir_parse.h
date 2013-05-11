/**
 * dir_parse.h
 * Parse the directory.
 *
 * @author Nathan Campos <nathanpc@dreamintech.net>
 */

#ifndef SHEETS_DIR_PARSE_H_
#define SHEETS_DIR_PARSE_H_

#include <string>
#include <vector>
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;


class Dir_Parse {
	private:
		fs::path root;
		size_t cut_path;

	public:
		std::vector<std::vector<std::string> > datasheets;

		// Constructors
		Dir_Parse();
		Dir_Parse(const char *dir);

		// Setters
		void set_root(const char *dir);

		// Iteration
		void iterate(fs::path dir);
		void iterate();

		// Parsing
		std::vector<std::string> get_tags(const fs::path path);
		const char* trim_path(const fs::path path);
		const char* trim_path(const std::string path);
};

#endif
