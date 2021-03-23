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
	
	
	map<string, int> defaultTriggerValues{
		{"x", -1},
		{"y", -1},
		{"x2", -1},
		{"y2", -1},
		{"rad", 0},
		{"rad2", 0}
	};

	map<string, int> defaultIntParams{
		{"mode", 0},
		{"red", -1},
		{"green", -1},
		{"blue", -1},
		{"primres", 6},
		{"boundMin", 0},
		{"boundMax", 255},
		{"z", 0},
		{"rotateX", 0},
		{"rotateY", 0},
		{"rotateZ", 0}
	};

	map<string, string> defaultStringParams{
		{"color", "white"},
		{"updating", "true"},
		{"primitive", "box"},
		{"fill", "true"}
	};

	map<string, float> defaultFloatParams{
		{"gain", 1.0},
		{"amt", 1.0},
		{"length", 0.95}
	};

};

# endif