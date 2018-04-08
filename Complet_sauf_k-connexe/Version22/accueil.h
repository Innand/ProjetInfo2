#ifndef ACCUEIL_H_INCLUDED
#define ACCUEIL_H_INCLUDED

#include "grman/grman.h"
#include <iostream>
#include <stack>

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
class Thing {

    private :
        grman::WidgetBox m_menu;

        ///Bouton du menu
        grman::WidgetButton m_graphe_1;

        grman::WidgetButton m_graphe_2;

        grman::WidgetButton m_graphe_3;

        grman::WidgetButton m_exit;

    public :

        /// Le constructeur de la classe (pas forc�ment par d�faut !)
        /// initialise les donn�es des widgets, place la hi�rarchie des sous-cadres etc...
        Thing();

        /// Une m�thode "update" de la classe doit �tre appel�e dans la boucle de jeu
        /// et cette m�thode doit propager l'appel � update sur les widgets contenus...
        /// Cette m�thode fait le lien entre l'interface, les �v�nements, et les cons�quences
        //  ( Cette m�thode pourrait s'appeler autrement, avoir des param�tres... )
        void update2();
        std::string accueil(BITMAP* fond_menu, bool *stop, bool *fin_boucle);


        /// On a des allocations dynamiques dans m_dynaclowns => � nettoyer dans le destructeur
        ~Thing();

};

#endif // ACCUEIL_H_INCLUDED
