#include <bits/stdc++.h>

using namespace std;

/// operatii de implementat:

/// statice:
// enumerare varfuri
// enumerare muchii
// pentru fiecare varf, o functie care returneaza gradul varfului
// functie booleana care pentru doua varfuri u, v returneaza true <=> u, v sunt adiacente (u ~ v)
// functie care returneaza vecinii lui v

/// operatii dinamice
// insertia unei muchii
// stergerea unei muchii
// insertia unui varf izolat
// stergerea unui varf
// contractia unei muchii

struct Varf {
    int id;
};

class Graf {
    vector<Varf*> varfuri;
    unordered_map<int, int> pozitieVarf;
    unordered_map<int, unordered_set<int>> listeAdiacenta;
    int maxValoare;
public:
    Graf();
    Graf(vector<vector<int>> liste);
    Graf(const Graf& graf);

    vector<Varf*> enumerareVarfuri();
    void enumerareMuchii();
    int getGrad(int id);
    bool suntAdiacente(int u, int v);
    unordered_set<int> getVecini(int idVarf);

    void insereazaMuchie(int u, int v);
    void stergeMuchie(int u, int v);
    void insereazaVarfIzolat();
    void stergeVarf(int v);
    void contractieMuchie(int u, int v);
};

vector<Varf*> Graf::enumerareVarfuri()
{
    return varfuri;
}

void Graf::enumerareMuchii()
{
    for (const auto& varf : listeAdiacenta) {
        for (const auto& vecin : varf.second) {
            if (varf.first < vecin) {
                cout << varf.first << " " << vecin << "\n";
            }
        }
    }
}

int Graf::getGrad(int id)
{
    return listeAdiacenta[id].size();
}

bool Graf::suntAdiacente(int u, int v)
{
    if (listeAdiacenta[u].size() < listeAdiacenta[v].size()) {
        auto it = lower_bound(listeAdiacenta[u].begin(), listeAdiacenta[u].end(), v);
        if (it != listeAdiacenta[u].end() && *it == v) {
            return true;
        }
        return false;
    }
    else {
        auto it = lower_bound(listeAdiacenta[v].begin(), listeAdiacenta[v].end(), u);
        if (it != listeAdiacenta[v].end() && *it == u) {
            return true;
        }
        return false;
    }
}

unordered_set<int> Graf::getVecini(int idVarf)
{
    return listeAdiacenta[idVarf];
}

void Graf::insereazaMuchie(int u, int v)
{
    listeAdiacenta[u].insert(v);
    listeAdiacenta[v].insert(u);
}

void Graf::stergeMuchie(int u, int v)
{
    listeAdiacenta[u].erase(v);
    listeAdiacenta[v].erase(u);
}

void Graf::insereazaVarfIzolat()
{
    Varf* newVarf = new Varf();
    newVarf->id = ++maxValoare;
    varfuri.push_back(newVarf);

    pozitieVarf[maxValoare] = varfuri.size() - 1;

    listeAdiacenta[newVarf->id] = unordered_set<int> ();
}

void Graf::stergeVarf(int v)
{
    for (const auto& vecin : listeAdiacenta[v]) {
        listeAdiacenta[vecin].erase(v);
    }

    listeAdiacenta.erase(v);

    swap(varfuri[pozitieVarf[v]], varfuri[varfuri.size() - 1]);
    varfuri.pop_back();
    pozitieVarf.erase(v);
}

void Graf::contractieMuchie(int u, int v)
{
    // sterg varful cu cei mai putini vecini
    if (listeAdiacenta[u].size() < listeAdiacenta[v].size()) {
        for (const auto& vecin : listeAdiacenta[u]) {
            listeAdiacenta[v].insert(vecin);
        }
        stergeVarf(u);
    }
    else {
        for (const auto& vecin : listeAdiacenta[v]) {
            listeAdiacenta[u].insert(vecin);
        }
        stergeVarf(v);
    }
}

int main()
{

    return 0;
}
