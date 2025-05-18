#include "tournament.hpp"

int main() {
    Tournament t(cin);
    // t.printData(); // Uncomment for debugging

    cout << (t.canTeam1Win() ? "Yes" : "No") << endl;

    return 0;
}