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

struct Muchie {
    Varf *v1, *v2;
};

class Graf {
    vector<Varf*> varfuri;
    vector<vector<bool>> matriceAdiacenta;
    int maxValoare;
public:
    Graf();
    Graf(vector<vector<bool>> matriceAdiacenta);
    Graf(const Graf& graf);

    vector<Varf*> enumerareVarfuri();
    vector<Muchie> enumerareMuchii();
    int getGrad(int v);
    bool suntAdiacente(int u, int v);
    vector<int> getVecini(int v);

    void insereazaMuchie(int u, int v);
    void stergeMuchie(int u, int v);
    void insereazaVarfIzolat();
    void stergeVarf(int v);
    void contractieMuchie(int u, int v);
};

Graf::Graf()
{
    maxValoare = -1;
}

Graf::Graf(vector<vector<bool>> matrice) : matriceAdiacenta(matrice)
{
    for (int i = 0; i < matrice.size(); ++i) {
        Varf* newVarf = new Varf();
        newVarf->id = i;
        varfuri.push_back(newVarf);
    }

    maxValoare = matrice.size() - 1;
}

Graf::Graf(const Graf& graf)
{
    for (Varf* v : graf.varfuri) {
        Varf* newVarf = new Varf(*v);
        varfuri.push_back(newVarf);
    }

    matriceAdiacenta = graf.matriceAdiacenta;
    maxValoare = graf.maxValoare;
}

/// operatii statice

vector<Varf*> Graf::enumerareVarfuri()
{
    return varfuri;
}

vector<Muchie> Graf::enumerareMuchii()
{
    vector<Muchie> muchii;

    Muchie temp;

    for (int i = 0; i < matriceAdiacenta.size(); ++i) {
        for (int j = 0; j < i; ++j) {
            if (matriceAdiacenta[i][j]) {
                temp.v1 = varfuri[i];
                temp.v2 = varfuri[j];
                muchii.push_back(temp);
            }
        }
    }

    return muchii;
}

int Graf::getGrad(int nrOrdine)
{
    int rezultat = 0;
    for (int i = 0; i < matriceAdiacenta.size(); ++i) {
        if (matriceAdiacenta[nrOrdine][i]) {
            ++rezultat;
        }
    }

    return rezultat;
}

bool Graf::suntAdiacente(int u, int v) {
    return matriceAdiacenta[u][v];
}

vector<int> Graf::getVecini(int v) {
    vector<int> rezultat;

    for (int i = 0; i < matriceAdiacenta.size(); ++i) {
        if (matriceAdiacenta[v][i]) {
            rezultat.push_back(i);
        }
    }

    return rezultat;
}

/// operatii dinamice

void Graf::insereazaMuchie(int u, int v)
{
    matriceAdiacenta[u][v] = matriceAdiacenta[v][u] = 1;
}

void Graf::stergeMuchie(int u, int v)
{
    matriceAdiacenta[u][v] = matriceAdiacenta[v][u] = 0;
}

void Graf::insereazaVarfIzolat()
{
    Varf* newVarf = new Varf();
    newVarf->id = ++maxValoare;
    varfuri.push_back(newVarf);

    for (int i = 0; i < matriceAdiacenta.size(); ++i) {
        matriceAdiacenta[i].push_back(0);
    }

    vector<bool> ultimaLinie(matriceAdiacenta.size() + 1, 0);
    matriceAdiacenta.push_back(ultimaLinie);
}
/// todo: swap mai eficient

void Graf::stergeVarf(int v)
{
    for (int i = 0; i < matriceAdiacenta.size(); ++i) {
        matriceAdiacenta[i].erase(matriceAdiacenta[i].begin() + v);
    }

    matriceAdiacenta.erase(matriceAdiacenta.begin() + v);

    delete varfuri[v];
    varfuri.erase(varfuri.begin() + v);
}

/// sters varful cu cei mai putini vecini
/// daca u ramane, adaugam vecinii lui v
void Graf::contractieMuchie(int u, int v)
{
    stergeMuchie(u, v);
    vector<int> veciniU = getVecini(u);
    vector<int> veciniV = getVecini(v);

    vector<int> veciniConcatenati;
    veciniConcatenati.insert(veciniConcatenati.end(), veciniU.begin(), veciniU.end());
    veciniConcatenati.insert(veciniConcatenati.end(), veciniV.begin(), veciniV.end());

    set<int> reuniuneVecini(veciniConcatenati.begin(), veciniConcatenati.end());

    stergeVarf(u);
    stergeVarf(v);

    insereazaVarfIzolat();

    for (auto itr : s) {
        matriceAdiacenta[maxValoare][itr] = matriceAdiacenta[itr][maxValoare] = 1;
    }
}

int main()
{
    vector<vector<bool>> matriceAdiacenta =
    {
        {0, 1, 1, 1},
        {1, 0, 0, 1},
        {1, 0, 0, 0},
        {1, 1, 0, 0}
    };


    return 0;
}
