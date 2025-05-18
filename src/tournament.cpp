#include "tournament.hpp"

Tournament::Tournament() : numTeams(0) {}

Tournament::Tournament(istream& input) {
    input >> numTeams;
    wins.resize(numTeams);

    for (int i = 0; i < numTeams; i++) {
        input >> wins[i];
    }
    
    games.assign(numTeams, vector<int>(numTeams, 0));
    for (int i = 0; i < numTeams-1; i++) {
        for (int j = i+1; j < numTeams; j++) {
            input >> games[i][j];
            games[j][i] = games[i][j];
        }
    }
}

void Tournament::printData() const {
    cout << "Number of teams: " << numTeams << endl;
    cout << "Current wins: ";
    for (int w : wins) cout << w << " ";
    cout << endl << "Remaining games:" << endl;
    for (int i = 0; i < numTeams; i++) {
        for (int j = 0; j < numTeams; j++) {
            cout << setw(3) << games[i][j] << " ";
        }
        cout << endl;
    }
}

bool Tournament::checkInitialConditions() {
    int remainingGamesTeam1 = 0;

    for (int j = 1; j < numTeams; j++) remainingGamesTeam1 += games[0][j];

    int maxWinsTeam1 = wins[0] + remainingGamesTeam1;
    maxAdditionalWins.resize(numTeams);

    for (int i = 1; i < numTeams; i++) {
        maxAdditionalWins[i] = maxWinsTeam1 - wins[i] - 1;
        if (maxAdditionalWins[i] < 0) {
            return false;
        }
    }
    
    return true;
}

Graph Tournament::buildFlowGraph() const {
    int numGames = (numTeams-1)*(numTeams-2)/2;
    int totalVertices = 1 + numGames + (numTeams-1) + 1;

    Graph g(totalVertices);
    g.source = 0;
    g.sink = totalVertices - 1;

    int firstGameVertex = 1;
    int firstTeamVertex = firstGameVertex + numGames;
    int gameVertexIndex = firstGameVertex;

    // Connect source to games
    for (int i = 1; i < numTeams; i++) {
        for (int j = i+1; j < numTeams; j++) {
            if (games[i][j] > 0) {
                g.addEdge(g.source, gameVertexIndex, games[i][j]);
                int teamI = firstTeamVertex + (i-1);
                int teamJ = firstTeamVertex + (j-1);
                g.addEdge(gameVertexIndex, teamI, INF);
                g.addEdge(gameVertexIndex, teamJ, INF);
            }
            gameVertexIndex++;
        }
    }

    // Connect teams to sink
    for (int i = 1; i < numTeams; i++) {
        int teamVertex = firstTeamVertex + (i-1);
        g.addEdge(teamVertex, g.sink, maxAdditionalWins[i]);
    }

    return g;
}

int Tournament::totalRemainingGames() const {
    int total = 0;

    for (int i = 1; i < numTeams; i++)
        for (int j = i+1; j < numTeams; j++)
            total += games[i][j];

    return total;
}

bool Tournament::canTeam1Win() {
    if (!checkInitialConditions()) return false;

    Graph flowGraph = buildFlowGraph();
    int maxFlow = fordFulkerson(flowGraph);
    int totalGames = totalRemainingGames();

    return maxFlow == totalGames;
}