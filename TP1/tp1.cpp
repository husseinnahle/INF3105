/*  
 * TP1 - INF3105 - H2022
 * Hussein Nahle
 * Ridley Saint-Orice
 */

#include <iostream>
#include <stdexcept>
#include "immeuble.h"
#include "station.h"
#include "tableau.h"
#include "installation.h"
#include "parser.h"

// Chercher le nom du fichier d'entré. O(1)
std::string chercher_nom_fichier(const int& argc, const char**& argv)
{
  if (argc < 2)
  {
    std::string nom_fichier;
    std::cout << "Entrer le nom du fichier : ";
    std::cin >> nom_fichier;
    return nom_fichier;
  }
  return argv[1];
}

// Calculer le nombre de clients de toutes les stations. O(n)
int nombre_clients_total(const Tableau<Installation>& installations)
{
  int nombre_clients_total = 0;
  for (int i = 0; i < installations.taille(); i++)
  {
    nombre_clients_total += installations[i].get_nombre_clients(); 
  }
  return nombre_clients_total;
}

// Calculer le factoriel de n. O(n)
long factoriel(int n)
{
  long j = 1;
  for (int i = 1; i <= n; i++)
  {
    j *= i;
  }
  return j;
}

// Retourne true s'il y a une interférence entre 2 stations. O(1)
bool interferance(const Installation& installation, const Station& station)
{
  double somme_rayon = installation.get_rayon() + station.get_rayon();
  double distance = installation.distance(station);
  return installation.get_frequence() == station.get_frequence() && distance <= somme_rayon;
}

// Retourne true si la station à placer est en interférence avec une des installations. O(n)
bool interferance(const Tableau<Installation>& installations, const Station& station)
{
  for (int i = 0; i < installations.taille(); i++)
  {
    if (interferance(installations[i], station))
    {
      return true;
    }    
  }
  return false;
}

// Retourne true si un immeuble a été déjà assigné à une station. O(n)
bool est_client(const Tableau<Installation>& installations, const Immeuble& immeuble)
{
  for (int i = 0; i < installations.taille(); i++)
  {
    if (installations[i].chercher_client(immeuble) != -1)
    {
      return true; 
    }
  }
  return false;
}

// Retourne true si l'immeuble se trouve dans le rayon d'une station. O(1)
bool est_inclu(const Installation& installation, const Immeuble& immeuble)
{
  return immeuble.distance(installation) <= installation.get_rayon();
}

// Retourne true si les rayons des stations sont egaux. O(n)
bool verifier_rayons(const Tableau<Station>& stations)
{
  for (int i = 0; i < stations.taille(); i++)
  {
    if (stations[i].get_rayon() != stations[0].get_rayon())
    {
      return true;
    }
  }
  return false;
}

// Lire le fichier d'entré et initialiser les tableaux stations et immeubles. O(n!)
void initialiser(const std::string& fichier, Tableau<Station>& stations, Tableau<Immeuble>& immeubles,
                 Tableau<Installation>& installations, Tableau<Tableau<Station>>& permutations_stations)
{
  Parser parser(fichier);
  parser.lire();
  parser.stations(stations);
  parser.immeubles(immeubles);
  installations.redimentionner(stations.taille());
  if (verifier_rayons(stations))
  {
    permutations_stations.redimentionner(factoriel(stations.taille()));
    // La fonction permuter retourne un tableau de tableaux de stations contenant 
    // toutes les combinaisons possibles des éléments du tableau "stations".
    // Cette fonction a une complexité temporelle égale à O(n!)
    stations.permuter(permutations_stations);
    return;
  }
  // Si les rayons des stations sont égaux alors on n'a pas besoin d'analyser toutes les combinaisons
  permutations_stations.ajouter(stations);  
}

// Chercher l'immeuble optimal pour placer une station. O(m^2)
void analyser(const Station& station, const Tableau<Immeuble>& immeubles, Tableau<Installation>& installations)
{
  Installation nouvelle_installation(station);
  for (int i = 0; i < immeubles.taille(); i++)
  {
    if (immeubles[i].get_hauteur() < station.get_hauteur() || interferance(installations, station))
    {
      continue;
    }    
    Installation* temp = new Installation(station, immeubles[i]);
    for (int j = 0; j < immeubles.taille(); j++)
    {
      if (!est_client(installations, immeubles[j]) && est_inclu(*temp, immeubles[j]))
      {
        temp->ajouter_client(immeubles[j]);
      }
    }
    if (nouvelle_installation.get_nombre_clients() <= temp->get_nombre_clients())
    {
      nouvelle_installation = *temp;
    }
    delete temp;    
  }
  // Enregistrer l'immeuble optimal
  installations.ajouter(nouvelle_installation);
}

// Faire l'analyse pour toutes les combinaisons possibles de stations et 
// choisir la permutation ayant le nombre maximum de clients. O(n! * n)
void analyser(const Tableau<Tableau<Station>>& permutations_stations, Tableau<Installation>& installations, const Tableau<Immeuble>& immeubles)
{
  int nombre_clients_total_max = 0;
  for (int i = 0; i < permutations_stations.taille(); i++)
  {
    int nombre_clients = 0;
    Tableau<Installation>* temp = new Tableau<Installation>(permutations_stations[0].taille());
    for (int j = 0; j < permutations_stations[i].taille(); j++)
    {
      analyser(permutations_stations[i][j], immeubles, *temp);
    }
    nombre_clients = nombre_clients_total(*temp);
    if (nombre_clients > nombre_clients_total_max)
    {
      nombre_clients_total_max = nombre_clients;
      installations = *temp;
    }
    delete temp;
  }
}

// Afficher le resultat final. O(n)
void afficher(const Tableau<Installation>& installations)
{
  for (int i = 0; i < installations.taille(); i++)
  {
    std::cout << installations[i].get_station_nom() << " " << installations[i].get_immeuble_nom() << std::endl;
  }
  std::cout << nombre_clients_total(installations) << std::endl;
}

int main(int argc, const char** argv)
{
  Tableau<Station> stations;
  Tableau<Immeuble> immeubles;
  Tableau<Installation> installations;
  Tableau<Tableau<Station>> permutations_stations;
  std::string nom_fichier = chercher_nom_fichier(argc, argv);
  try
  {
    initialiser(nom_fichier, stations, immeubles, installations, permutations_stations);
    analyser(permutations_stations, installations, immeubles);
    afficher(installations);
    return 0;
  }
  catch(const std::exception& exception)
  {
    std::cerr << "Erreur : " << exception.what() << std::endl;
    return 1;
  }
}
