#include <iostream>
#include <fstream>
#include "carte.h"
#include <sstream>

using namespace std;


int main(int argc, const char** argv)
{
    if(argc<4){
        cout << "Syntaxe : valideur carte.txt missions.txt missions.resultat [missions.solution]" << endl;
        return 0;
    }
    
    std::ifstream fcarte(argv[1]);
    std::ifstream fmissions(argv[2]);
    std::ifstream fresultat(argv[3]);
    std::ifstream* fsolution = NULL;
    if(argc>4){
        fsolution = new ifstream(argv[4]);
        if(fsolution->fail()){
            delete fsolution;
            fsolution = NULL;
        }
    }
    
    Carte carte;
    fcarte >> carte;
    fcarte.close();
    
    int nbMissions=0;
    int nbValide=0;
    int nbOptimal=0;
    int nbDistOk=0;
    int nbCheminRoutesOk=0;

    while(fmissions){
        string nomlieuaffaire;
        char deuxpoints = 0;
        fmissions >> nomlieuaffaire >> deuxpoints;
        if(!fmissions) break;
        assert(deuxpoints==':');
        set<string> destinations;
        while(fmissions){
            string destination;
            fmissions >> destination; // ne pas ajouter « >> std::std » ici.
            if(destination==";" || !fmissions) break;
            assert(destination.find(";")==string::npos);
            destinations.insert(destination);
        }
        
        nbMissions++;
        cout << nbMissions << ". ";
        
        list<string> chemin_noeuds, chemin_routes;
        
        string cheminN, cheminR, distanceM;
        getline(fresultat, cheminN);
        getline(fresultat, cheminR);
        getline(fresultat, distanceM);
        {
            stringstream ss(cheminN);
            while(ss){
                string noeud;
                ss >> noeud;
                if(!noeud.empty()) chemin_noeuds.push_back(noeud);
            }
        }
        {
            stringstream ss(cheminR);
            while(ss){
                string route;
                ss >> route;
                if(!route.empty()) chemin_routes.push_back(route);
            }
        }
        int distance=0;
        {
            stringstream ss(distanceM);
            ss >> distance;
        }
        
        // Solution
        int distanceoptimale = -1;
        if(fsolution!=NULL){
            string optimalN, optimalR, optimalM;
            getline(*fsolution, optimalN);
            getline(*fsolution, optimalR);
            getline(*fsolution, optimalM);
            stringstream ss(optimalM);
            ss >> distanceoptimale;
        }
        
        // Validation
        bool valide=false, optimal=false, distOK=false, cheminRoutesOK=false;
        carte.validerTrajet(nomlieuaffaire, destinations, chemin_noeuds, chemin_routes, 
                                 valide, optimal, distOK, cheminRoutesOK,
                                 distance, distanceoptimale);
        if(distOK) nbDistOk++;
        if(cheminRoutesOK) nbCheminRoutesOk++;
        if(valide) nbValide++;
        if(optimal) nbOptimal++;
    }
    
    cout << "-----------------------------\nSommaire :" << endl;
    cout << "Valid\tOptimal\tDistOK\tRouteOK\t/NbMiss\tRéussi?" << endl;
    cout << nbValide << '\t';
    if(fsolution!=NULL) cout << nbOptimal; else cout << "?";
    cout << '\t'
         << nbDistOk << '\t'
         << nbCheminRoutesOk << '\t'
         << '/' << nbMissions << '\t';
    if(nbDistOk==nbMissions /*&& nbCheminRoutesOk==nbMissions*/){
        if(nbOptimal==nbMissions) cout << "Optimal";
        else if(nbValide==nbMissions) cout << "Valide";
        else cout << "Echec";
    }else{
        cout << "Echec";
    }
    cout << endl;
    delete fsolution;
    return 0;
}
