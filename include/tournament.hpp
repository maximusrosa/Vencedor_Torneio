#include <iostream>
#include <vector>
#include <iomanip>
#include "ford_fulkerson.hpp"

class Tournament {
private:
    int numTeams;
    vector<int> wins;
    vector<vector<int>> games;
    vector<int> maxAdditionalWins;

public:
    Tournament();
    Tournament(istream& input);
    
    void printData() const;
    bool checkInitialConditions();
    Graph buildFlowGraph() const;
    int totalRemainingGames() const;
    bool canTeam1Win();
};