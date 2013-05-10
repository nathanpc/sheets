/**
 * Sheets
 * A tool to quickly organize, browse, and search for your datasheets.
 *
 * @author Nathan Campos <nathanpc@dreamintech.net>
 */

#include <iostream>
#include <boost/filesystem.hpp>

#include "dir_parse.h"

using namespace std;
namespace fs = boost::filesystem;

int main(int argc, char *argv[]) {
	Dir_Parse dir(argv[1]);
	dir.iterate();

	return 0;
}
