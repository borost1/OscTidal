#pragma once
# ifndef _OSCMANAGER
# define _OSCMANAGER

#include "ofMain.h"
#include "Grid.h"

class oscManager
{
public:
	void receiveParams(map<string, string> params);
	int matchParam(map<string, string> m, string paramName, int defVal);
	float matchParamf(map<string, string> m, string paramName, float defVal);
	string matchParam(map<string, string> m, string paramName, string defVal);

	vector<Grid> *grids = reinterpret_cast<vector<Grid>*>(ofGetAppPtr());
	
	map<string, int> defaultValues{
		{"x", -1},
		{"y", -1},
		{"x2", -1},
		{"y2", -1},
		{"rad", 0},
		{"rad2", 0},
		{"mode", 0},
		{"target", 0}
	};
};

# endif