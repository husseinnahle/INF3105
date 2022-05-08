#include "carte.h"

void Carte::transferer_resulat(stack<string>& lieux, stack<string>& routes, string& lieux_str, string& routes_str, string& route_top) const
{
  while (!lieux.empty())
  {
    lieux_str += lieux.top() + " ";
    lieux.pop();
  }
  while (!routes.empty())
  {
    routes_str += route_top != routes.top() ? routes.top() + " " : "";      
    route_top = routes.top();
    routes.pop();
  }
}

double Carte::chercher_chemin(const string& origine_str, vector<string> destinations_str, string& lieux_str, string& routes_str) const
{
  stack<string> lieux;
  stack<string> routes;

  // Utiliser pour enregistrer la derniere route visitée.
  // Utiliser pour éviter d'avoir deux mêmes routes consécutives dans le résultat.
  string route_top = "";

  double distance_total = 0;
  int origine = carte.at(origine_str);
  int position = origine;

	while (!destinations_str.empty())
	{
		double distance = numeric_limits<double>::infinity();
    int destination = -1;
		int lieu_visite;

		for (long unsigned int i = 0; i < destinations_str.size(); ++i)
    {
      stack<string> lieux_tmp;
      stack<string> routes_tmp;
			double distance_tmp = chercher_chemin(position, carte.at(destinations_str[i]), lieux_tmp, routes_tmp);

			if (distance_tmp < distance)
			{
				distance = distance_tmp;
				destination = carte.at(destinations_str[i]);
				lieu_visite = i;
        lieux = lieux_tmp;
        routes = routes_tmp;
			}	
		}

    // Enlever la destination visitée
		destinations_str.erase(destinations_str.begin() + lieu_visite);
    transferer_resulat(lieux, routes, lieux_str, routes_str, route_top);
 
		distance_total += distance;
		position = destination;
	}

  // Chercher le chemin de routre
  distance_total += chercher_chemin(position,origine, lieux, routes);
  transferer_resulat(lieux, routes, lieux_str, routes_str, route_top);

  return distance_total;
}

// Reference : http://ericbeaudry.uqam.ca/INF3105/videos/S13-3z-astar.mp4
double Carte::chercher_chemin(const int& origine, const int& destination, stack<string>& lieux_o, stack<string>& routes) const
{
  unordered_map<int, int> chemin;
  chemin[origine] = -1;

  // Dictionnaire qui enregistre les distances accumulées de l'origine à chaque lieu visité
  unordered_map<int, double> distances;
  distances[origine] = 0;

  // Enregistrer les lieux visités. La priorité est égale à la distance restante pour arriver à la destination.
  // Le lieu avec la priorité la moins élevée se trouve au sommet. Le sommet représente la prochaine destination.
  priority_queue<Priorite> visites;
  visites.emplace(Priorite(origine, 0));

  while (!visites.empty())
  {
    int position = visites.top().position;

    // Verifier si on est arrivé à la destination
    if (position == destination)
    {
      consrtuire_chemin(position, chemin, lieux_o, routes);
      // Retourner la distance accumulée pour arriver à la destination
      return distances[destination];
    }

    visites.pop();

    // Chercher la direction optimale
    for (long unsigned int i = 0; i < lieux[position].directions.size(); i++)
    {
      int suivant = lieux[position].directions[i].lieu;
      double d = distance(lieux[position], lieux[suivant]) + distances[position];
      if (distances.find(suivant) == distances.end() || d < distances[suivant])
      {
          chemin[suivant] = position;
          distances[suivant] = d;
          visites.emplace(Priorite(suivant, d + distance(lieux[suivant], lieux[destination])));
      }
    }
  }

  // Chemin non trouve
  return -1;
}

void Carte::consrtuire_chemin(int courant, unordered_map<int, int>& chemin, stack<string>& lieux_o, stack<string>& routes) const
{
  int suivant = courant;
  courant = chemin[courant];

  // Itereration inverse (destination vers l'origine)
  // (raison pour laquelle on a choisi d'utiliser une stack...)
  while (courant != -1)
  {
    lieux_o.push(lieux[courant].nom);
    
    // Rechercher la route 
    for (auto direction = lieux[courant].directions.rbegin();
      direction != lieux[courant].directions.rend(); ++direction)
    {
      if (suivant == direction->lieu && direction->route != lieux_o.top())
      {
        routes.push(direction->route);
        break;
      }
    }

    suivant = courant;
    courant = chemin[courant];
  }
}

void Carte::ajouter_lieu(const Lieu& lieu)
{
  int index = lieux.size();
  lieux.push_back(lieu);
  carte[lieu.nom] = index;
}

void Carte::ajouter_direction(string& route, const vector<string>& lieux)
{
  int source = -1;
  for (auto lieu : lieux)
  {
    int destination = carte.at(lieu);
    if (source != -1)
    {
      this->lieux[source].directions.push_back(Direction(destination, route));
    }
    source = destination;
  }
}

double Carte::distance(const Lieu& origine, const Lieu& destination) const
{
  return origine.distance(destination);
}

istream& operator >> (istream& is, Carte& carte)
{
  // Placer les lieux (sommets)
  while (is) 
  {
    string nom;
    Coordonnee position;
    is >> nom;
    if (nom == "---")
    {
      // Placer les routes (arêtes)
      while (is)
        {
          vector<string> lieux;
          string route;
          char dp;
          is >> route >> dp;
          while (is)
          {
            string sommet;
            is >> sommet;
            if (sommet == ";")
            {
              break;
            }
            lieux.push_back(sommet);
          }
          carte.ajouter_direction(route, lieux);
        }
    }
    is >> position;
    carte.ajouter_lieu(Lieu(nom, position));
  }
  return is;
}
