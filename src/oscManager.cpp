#include "oscManager.h"
#include "ofApp.h"

void oscManager::receiveParams(map<string, string> params) {
	
	map<string, int> triggerParams;
	map<string, int> intParams;
	map<string, string> stringParams;
	map<string, float> floatParams;
	
	for (const auto& kv : defaultTriggerValues) {
		triggerParams.insert(pair<string, int>(kv.first, matchParam(params, kv.first, kv.second)));
	}

	for (const auto& kv : defaultIntParams) {
		intParams.insert(pair<string, int>(kv.first, matchParam(params, kv.first, kv.second)));
	}

	for (const auto& kv : defaultStringParams) {
		stringParams.insert(pair<string, string>(kv.first, matchParam(params, kv.first, kv.second)));
	}

	for (const auto& kv : defaultFloatParams) {
		floatParams.insert(pair<string, float>(kv.first, matchParamf(params, kv.first, kv.second)));
	}
	
	string targetSystem = matchParam(params, "sys", "grid");
	string type = matchParam(params, "type", "circle");
	string color = matchParam(params, "color", "white");
	int target = matchParam(params, "target", 0);
	//float gain = matchParamf(params, "gain", 1.0);

	// TODO: this must be temporary!!!
	//float amount = ofMap(gain, 0, 1, 0, 255);

	if (targetSystem == "grid") {
		if (type == "circle") {
			(*grids)[target].midPointEllipseTrigger(
				triggerParams["rad"],
				triggerParams["rad"],
				triggerParams["x"],
				triggerParams["y"],
				floatParams,
				intParams,
				stringParams
			);
		}
		else if (type == "ellipse") {
			(*grids)[target].midPointEllipseTrigger(
				triggerParams["rad"],
				triggerParams["rad2"],
				triggerParams["x"],
				triggerParams["y"],
				floatParams,
				intParams,
				stringParams
			);
		}
		else if (type == "square") {
			(*grids)[target].midPointSquareTrigger(
				triggerParams["x"],
				triggerParams["y"],
				triggerParams["rad"],
				floatParams,
				intParams,
				stringParams
			);
		}
		else if (type == "diagonal") {
			(*grids)[target].midPointDiagonalTrigger(
				triggerParams["x"],
				triggerParams["y"],
				triggerParams["rad"],
				floatParams,
				intParams,
				stringParams
			);
		}
		else if (type == "line") {
			cout << "line TODO\n";
		}
	}
	else if (targetSystem == "cam") {
		((ofApp*)ofGetAppPtr())->setCamPos(triggerParams["x"], triggerParams["y"], triggerParams["rad"]);
	}

	triggerParams.clear();

}

int oscManager::matchParam(map<string, string> m, string paramName, int defVal) {
	if (m.find(paramName) == m.end()) {
		return defVal;
	}
	else {
		return stoi(m[paramName]);
	}
}

float oscManager::matchParamf(map<string, string> m, string paramName, float defVal) {
	if (m.find(paramName) == m.end()) {	
		return defVal;
	}
	else {
		return stof(m[paramName]);
	}
}

string oscManager::matchParam(map<string, string> m, string paramName, string defVal) {
	if (m.find(paramName) == m.end()) {
		return defVal;
	}
	else {
		return m[paramName];
	}
}