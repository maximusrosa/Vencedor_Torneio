#include "tournament.hpp"

int main() {
    Tournament t(cin);
    // t.printData(); // Uncomment for debugging

    cout << (t.canTeam1Win() ? "sim" : "não") << endl;

    return 0;
}