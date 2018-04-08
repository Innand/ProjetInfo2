#include "accueil.h"

/***************************************************
                    THING (test)

  Cette classe correspond au cadre en bas à gauche
  avec différents bidules interactifs assemblés dessus
  VOIR LE CONSTRUCTEUR ET LA METHODE UPDATE EN DETAIL
  ( dans test.cpp ) pour décrypter l'utilisation
  des widgets proposés ( vous pouvez en ajouter d'autres
  en complétant widget.h et widget.cpp, répertoire
  de projet grman )
****************************************************/

/// Le constructeur de la classe (pas forcément par défaut !)
/// initialise les données des widgets, place la hiérarchie des sous-cadres etc...

/// Tous les widgets sont des attributs directs (PAS DES POINTEURS, PAS DE NEW)
/// de la classe encapsulante (ici Thing) de telle sorte qu'ils sont détruits
/// automatiquement quand la classe Thing est détruite.
Thing::Thing()
{
    /// Menu test
    m_menu.add_child(m_graphe_1);
    m_graphe_1.set_pos(235, 195);
    m_graphe_1.set_dim(310,40);

    m_menu.add_child(m_graphe_2);
    m_graphe_2.set_pos(235, 260);
    m_graphe_2.set_dim(310,40);

    m_menu.add_child(m_graphe_3);
    m_graphe_3.set_pos(235, 322);
    m_graphe_3.set_dim(310,40);


    m_menu.add_child(m_exit);
    m_exit.set_dim(35,18);
    m_exit.set_pos(765, 0);
    m_exit.set_bg_color(ROUGE);
}

/// Une méthode update de la classe doit être appelée dans la boucle de jeu
/// et cette méthode doit propager l'appel à update sur les widgets contenus...
/// Cette méthode fait le lien entre l'interface, les événements, et les conséquences
void Thing::update2()
{
    m_menu.update();
}

std::string Thing::accueil(BITMAP* fond_menu, bool *stop, bool *fin_boucle)
{
    std::string nom="";
    blit(fond_menu,grman::page, 0,0,0,0, SCREEN_W, SCREEN_H);

    if(m_graphe_1.clicked())
    {
        nom="pics";
        *stop=true;
    }

    if(m_graphe_2.clicked())
    {
        nom="pics2";
        *stop=true;
    }

    if(m_graphe_3.clicked())
    {
        nom="pics3";
        *stop=true;
    }

    if(m_exit.clicked())
    {
        *stop=true;
        *fin_boucle=true;
    }

    return nom;
}


/// On a des allocations dynamiques dans m_dynaclowns => à nettoyer dans le destructeur
Thing::~Thing() {}
