#ifndef ACCUEIL_H_INCLUDED
#define ACCUEIL_H_INCLUDED

#include "grman/grman.h"
#include <iostream>
#include <stack>

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
class Thing {

    private :
        grman::WidgetBox m_menu;

        ///Bouton du menu
        grman::WidgetButton m_graphe_1;

        grman::WidgetButton m_graphe_2;

        grman::WidgetButton m_graphe_3;

        grman::WidgetButton m_exit;

    public :

        /// Le constructeur de la classe (pas forcément par défaut !)
        /// initialise les données des widgets, place la hiérarchie des sous-cadres etc...
        Thing();

        /// Une méthode "update" de la classe doit être appelée dans la boucle de jeu
        /// et cette méthode doit propager l'appel à update sur les widgets contenus...
        /// Cette méthode fait le lien entre l'interface, les événements, et les conséquences
        //  ( Cette méthode pourrait s'appeler autrement, avoir des paramètres... )
        void update2();
        std::string accueil(BITMAP* fond_menu, bool *stop, bool *fin_boucle);


        /// On a des allocations dynamiques dans m_dynaclowns => à nettoyer dans le destructeur
        ~Thing();

};

#endif // ACCUEIL_H_INCLUDED
