#include "accueil.h"

/***************************************************
                    THING (test)

  Cette classe correspond au cadre en bas � gauche
  avec diff�rents bidules interactifs assembl�s dessus
  VOIR LE CONSTRUCTEUR ET LA METHODE UPDATE EN DETAIL
  ( dans test.cpp ) pour d�crypter l'utilisation
  des widgets propos�s ( vous pouvez en ajouter d'autres
  en compl�tant widget.h et widget.cpp, r�pertoire
  de projet grman )
****************************************************/

/// Le constructeur de la classe (pas forc�ment par d�faut !)
/// initialise les donn�es des widgets, place la hi�rarchie des sous-cadres etc...

/// Tous les widgets sont des attributs directs (PAS DES POINTEURS, PAS DE NEW)
/// de la classe encapsulante (ici Thing) de telle sorte qu'ils sont d�truits
/// automatiquement quand la classe Thing est d�truite.
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

/// Une m�thode update de la classe doit �tre appel�e dans la boucle de jeu
/// et cette m�thode doit propager l'appel � update sur les widgets contenus...
/// Cette m�thode fait le lien entre l'interface, les �v�nements, et les cons�quences
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


/// On a des allocations dynamiques dans m_dynaclowns => � nettoyer dans le destructeur
Thing::~Thing() {}
