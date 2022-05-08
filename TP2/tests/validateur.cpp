#include <iostream>
#include <cctype>
#include <fstream>
#include <sstream>
#include <list>
#include <map>
#include <cstring>
using namespace std;

// Fonction pour tester l'équivalence de deux string sans tenir compte des espaces blancs (' ' et '\t').
bool stringsequivalentes(const string& s1, const string& s2){
    unsigned int i1=0;
    unsigned int i2=0;
    while(true){
        while(s1[i1]==' ' || s1[i1]=='\t') ++i1;
        while(s2[i2]==' ' || s2[i2]=='\t') ++i2;
        if(i1>=s1.size()) break;
        if(i2>=s2.size()) break;
        if(s1[i1++] != s2[i2++]) return false;
        //if(tolower(s1[i1++]) != tolower(s2[i2++])) return false;
    }
    return i1>=s1.size() && i2>=s2.size();
}

void lireMANQUE(istream& is, map<string, int>& manque){
    while(is && !is.eof()){
        string nom;
        int qte;
        is >> nom >> qte >> std::ws;
        if(nom==";") break;
        manque[nom] += qte;
    }
}

int main(int argc, const char** argv){
    bool erreur=false, mode_verbose=false, mode_details=false;
    const char* fichier_solution = NULL;
    const char* fichier_resultat = NULL;
    
    for(int i=1,j=0;i<argc;i++){
        if(argv[i][0]=='-')
            switch(argv[i][1]){
                case 'v':
                    mode_verbose=true;
                    break;
                case 'd':
                    mode_details=true;
                    break;
                default:
                    cerr << "Option '" << argv[i] << "' invalide!" << endl;
                    erreur=true;
            }
        else
            switch(j++){
                case 0:
                    fichier_solution = argv[i];
                    break;
                case 1:
                    fichier_resultat = argv[i];
                    break;
                default:
                    cerr << "Argument en trop: " << argv[i] << " !" << endl;
                    erreur=true;
            }
    }
    // Validation du nombre de paramètres
    if(erreur || fichier_resultat==NULL){
        cout << "./valideur solution.txt votreresultat.txt [-v]" << endl;
        return 1;
    }
    
    // Ouvertures des fichiers
    ifstream isolution(fichier_solution);
    if(isolution.fail()) {
        cout << "Fichier inexistant: " << fichier_solution << endl;
        return 2;
    }
    ifstream iresultat(fichier_resultat);
    if(iresultat.fail()) {
        cout << "Fichier inexistant: " << fichier_resultat << endl;
        return 3;
    }
    
    // Compteurs
    int nbRequetes=0, nbBons=0, nbErreurs=0;
    
    // Boucle principale : lire ligne par ligne les fichiers solution et résultat, et comparer
    while(isolution && !isolution.eof()){
        string ligne_solution, ligne_resultat;

        if(isolution)
            getline(isolution, ligne_solution);
        if(ligne_solution.empty())
            break; // le fichier solution est terminé
        nbRequetes++;
        //cout << nbRequetes << "...";

        if(iresultat)
            getline(iresultat, ligne_resultat);
        if(ligne_resultat.empty())
            continue; // le fichier résultat est terminé (lire quand même le fichier solution pour compter)
        
        bool ok = false;
        
        // Changement de spécification (0m a disparu)... valider quand même l'ancienne.
        if(stringsequivalentes("0m IMPOSSIBLE", ligne_resultat))
            ligne_resultat = "IMPOSSIBLE";
        if(stringsequivalentes("0m IMPOSSIBLE", ligne_solution))
            ligne_solution = "IMPOSSIBLE";

        if(stringsequivalentes(ligne_solution, ligne_resultat)){
            ok = true;
        }else{
            stringstream sstr_solution(ligne_solution);
            stringstream sstr_resultat(ligne_resultat);
            
            string mot1_solution, mot1_resultat;
            sstr_solution >> mot1_solution;
            sstr_resultat >> mot1_resultat;
            
            if(mot1_solution==mot1_resultat){
            
                // Résultat d'une commande RECOMMANDER qui commence par une distance suivi d'un m collé
                if(!mot1_solution.empty() && mot1_solution[mot1_solution.length()-1]=='m'){
                    list<string> liste_solution, liste_resultat;
                    while(sstr_solution){
                        string s;
                        sstr_solution >> s >> std::ws;
                        if(!s.empty())
                            liste_solution.push_back(s);
                    }
                    while(sstr_resultat){
                        string s;
                        sstr_resultat >> s >> std::ws;
                        if(!s.empty())
                            liste_resultat.push_back(s);
                    }
                    if(liste_resultat==liste_solution)
                        ok = true;
                    liste_resultat.reverse();
                    if(liste_resultat==liste_solution)
                        ok = true;
                }
                
                // Résultat MANQUE
                if(mot1_solution=="MANQUE"){
                    map<string, int> manque_solution, manque_resultat;
                    lireMANQUE(sstr_solution, manque_solution);
                    lireMANQUE(sstr_resultat, manque_resultat);
                    ok = manque_resultat==manque_solution;
                }
            }
        }
        
        if(ok)
            nbBons++;
        else
            nbErreurs++;
            
        if(!ok && mode_details)
            cout << nbRequetes << ". Erreur!" << endl;
           
    }
    
    // Affichage du résultat
    if(mode_verbose){
        cout << nbBons << " bon(s)\t" << nbErreurs << " erreur(s)\t";
        cout << '/' << nbRequetes << "\t|\t";
        if(nbRequetes==0)
            cout << "Erreur";
        else if(nbBons==0 && nbErreurs==0)
            cout << "Aucun_Résultat";
        else if(nbBons==nbRequetes)
            cout << "OK";
        else if(nbBons>0 && nbErreurs==0)
            cout << "OK_interrompu";
        else
            cout << "Échec";
    }else{
        cout << nbBons << '\t' << nbErreurs;
    }
    cout << endl;
    return 0;
}

