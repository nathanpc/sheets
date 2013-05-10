/**
 * Sheets
 * A tool to quickly organize, browse, and search for your datasheets.
 *
 * @author Nathan Campos <nathanpc@dreamintech.net>
 */

#include <iostream>
#include <boost/filesystem.hpp>

using namespace std;
namespace fs = boost::filesystem;

int main(int argc, char *argv[]) {
	fs::path path(argv[1]);

	if (fs::exists(path)) {
		if (is_regular_file(path)) {
			cout << path << " is a file" << endl;
		} else if (is_directory(path)) {
			cout << path << " is a directory" << endl;
		} else {
			cerr << "WTF is this crap?!" << endl;
			return 1;
		}
	} else {
		cout << path << " doesn't exist" << endl;
		return 1;
	}

	return 0;
}
