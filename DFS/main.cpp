#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <map>

using namespace std;

string i2s(int a) {
	string tmp = "";
	stringstream ss;
	ss << a;
	ss >> tmp;
	return tmp;
}

void initial_graph(map <int, int>& reverserules,map<int, int>& rules, vector<vector<int>>& paths, int& start, int& terminal) {
	
	int nodes;
	int lines;
	cin >> nodes >> lines >> start >> terminal;
	paths.resize(nodes);
	for (int i = 0; i < paths.size(); i++)
	{
		paths[i].resize(nodes);
	}
	
	int valuecount = 0;
	for (int i = 0; i < lines; i++)
	{
		int row;
		int col;
		int weight;
		cin >> row >> col >> weight;
		if (rules.find(row) != rules.end()) {
			if (rules.find(col) != rules.end()) {
				paths[rules.find(row)->second][rules.find(col)->second] = weight;
			}
			else {
				rules.insert(pair<int, int>(col, valuecount++));
				paths[rules.find(row)->second][rules.find(col)->second] = weight;
			}
		}
		else {
			rules.insert(pair<int, int>(row, valuecount++));
			if (rules.find(col) != rules.end()) {
				paths[rules.find(row)->second][rules.find(col)->second] = weight;
			}
			else {
				rules.insert(pair<int, int>(col, valuecount++));
				paths[rules.find(row)->second][rules.find(col)->second] = weight;
			}
		}

	}
	
	for (auto i = rules.begin(); i != rules.end(); i++)
	{
		reverserules.insert(pair<int, int>(i->second, i->first));
	}
	//system("PAUSE");
}

void DFS(map<int,int>reverserules,vector<pair<string, int>>& solution, vector<vector<int>>paths, int cur, int terminal, int cost, string visited) {
	if (visited.length() > paths.size() * 5) {
		return;
	}
	//auto it = reverserules.find(cur);
	if (reverserules.find(cur)->second == terminal ) {
		solution.push_back(pair<string, int>(visited, cost));
		return;
	}
	if (paths.size() > cur) {
		for (int i = 0; i < paths[cur].size(); i++)
		{
			if (paths[cur][i] != 0 && cur != i) {

				DFS(reverserules,solution, paths, i, terminal, cost + paths[cur][i], visited + " " + i2s(i));
			}
		}
	}

}

bool compare(const pair<string, int>& a, const  pair<string, int>& b) {
	return a.second < b.second;
}

int main() {
	vector<vector<int>>paths;
	int start, terminal;
	vector<pair<string, int>>solution;
	map<int, int>rules;
	map<int, int>reverserules;
	initial_graph(reverserules,rules,paths, start, terminal);
	for (int i = 0; i < paths[rules.find(start)->second].size(); i++)
	{
		int cost = 0;
		string visited = "";
		if (paths[rules.find(start)->second][i] != 0) {
			visited = i2s(rules.find(start)->second);
			DFS(reverserules,solution, paths, rules.find(start)->second, terminal, cost, visited);
		}
	}

	if (solution.size() >= 1) {
		sort(solution.begin(), solution.end(), compare);
		stringstream ss(solution[0].first);
		string tmp;
		string output="";
		while (ss >> tmp) {
			output += i2s(reverserules.find(stoi(tmp))->second) ;
			output += " ";
		}
		output =  output.substr(0, output.length() - 1);
		cout << output;
		cout << endl;
		cout << solution[0].second;
	}
	else {
		cout << " no soultion";
	}
	return 0;
}