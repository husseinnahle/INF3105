#if !defined(_PARSER__H_)
#define _PARSER__H_

#include <stdexcept>
#include <fstream>
#include <sstream>
#include <string>

#include "tableau.h"
#include "station.h"
#include "immeuble.h"

class Parser
{
  public:
    Parser(const std::string& fichier);
    void lire();
    void stations(Tableau<Station>&);
    void immeubles(Tableau<Immeuble>&);

  private:
    std::string nom_fichier;
    int nombre_stations;
    Tableau<std::string> entrees;
};
#endif
