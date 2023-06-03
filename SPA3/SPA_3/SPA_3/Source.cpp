#include "DijkstraShortestPath.h"

using namespace std;


int main()
{

    cout << "Tocke A i B mogu postati nedostupne zbog nasumicno postavljenih barijera.jednostavno ponovno pokrenite."<<endl;
    cout << "Kao rezultat toga, softver samo izlazi" << endl;
    cout << "Ako se to dogodi, ponovno pokrenite." << endl;

    cout << endl;

    bool walls = true;
    cout << "Treba li simulacija biti pokrenuta sa zidovima (1) ili bez zidova (0)? > ";
    cin >> walls;

    int row_a;
    int column_a;
    int row_b;
    int column_b;

    cout << "Red 1 - 20" << endl;
    cout << "Stupac 1 - 40" << endl;

    cout << "Umetnite red tocke A : ";
    cin >> row_a;
    cout << "Umetnite stupac tocke A: ";
    cin >> column_a;
    cout << "Umetnite red tocke B: ";
    cin >> row_b;
    cout << "Umetnite stupac tocke B: ";
    cin >> column_b;

    DijkstraShortestPath path(row_a, column_a, row_b, column_b, walls);

    return 0;
}
