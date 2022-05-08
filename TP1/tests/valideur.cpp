#include <iostream>
#include <fstream>
#include <assert.h>
#include "../point.h"

#include <vector>
#include <map>


using namespace std;

struct Immeuble{
    Immeuble() : couvert(false){}
    string nom;
    Point  position;
    double hauteur;
    int    nbclients;
    bool   couvert;
    friend istream& operator >> (istream& is, Immeuble& im);
};

struct Station{
    string nom;
    double hauteurmin;
    double rayon;
    double frequence;
    friend istream& operator >> (istream& is, Station& im);
};

istream& operator >> (istream& is, Immeuble& im){
    is >> im.nom >> im.position >> im.hauteur >> im.nbclients;
    return is;
}

istream& operator >> (istream& is, Station& s){
    is >> s.nom >> s.rayon >> s.hauteurmin >> s.frequence;
    return is;
}

int main(int argc, const char** argv)
{
    if(argc<3){
        cout << "./evaluateur probleme.txt probleme.resultat.txt" << endl;
        return 1;
    }
    map<string, Immeuble> immeubles;
    map<string, Station>  stations;

    ifstream fileprobleme(argv[1]);       
    {
        int nbstations;
        fileprobleme >> nbstations;
        for(int i=0;i<nbstations;i++){
            Station s;
            fileprobleme >> s;
            stations[s.nom] = s;
        }
    }
    
    while(fileprobleme)
    {
        Immeuble immeuble;
        fileprobleme >> immeuble;
        if(!fileprobleme) break;
        immeubles[immeuble.nom] = immeuble;
    }
    
    ifstream fileresultat(argv[2]);
    for(int s=0;s<stations.size();s++){
        string nomstation, nomimmeuble;
        fileresultat >> nomstation >> nomimmeuble;
        if(stations.find(nomstation)==stations.end()){
            cerr << "La station " << nomstation << " n'existe pas!" << endl;
            break;
        }
        Station& station = stations[nomstation];
        if(nomimmeuble=="--") continue;
        
        if(immeubles.find(nomimmeuble)==immeubles.end()){
            cerr << "La station " << nomimmeuble << " n'existe pas!" << endl;
            break;
        }        
        Immeuble& immeuble = immeubles[nomimmeuble];
        if(station.hauteurmin>immeuble.hauteur) continue;
        
        for(map<string, Immeuble>::iterator iter=immeubles.begin();iter!=immeubles.end();iter++){
            Immeuble& immeuble2 = iter->second;
            double d = immeuble.position.distance(immeuble2.position);
            if(d<=station.rayon)
                immeuble2.couvert = true;
        }
    }
    
    int nbclients = 0;
    for(map<string, Immeuble>::iterator iter=immeubles.begin();iter!=immeubles.end();iter++){
        Immeuble& immeuble2 = iter->second;
        if(immeuble2.couvert)
            nbclients += immeuble2.nbclients;
    }
    
    cout << nbclients << endl;
    
    return 0;
}
