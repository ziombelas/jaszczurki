#include "Settings.h"

Settings::Settings() {
}

Settings::~Settings() {
	for (int unsigned i = 0; i < grajacy.size(); i++)
		delete grajacy[i];
}
