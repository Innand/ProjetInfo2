#include "grman/grman.h"
#include <iostream>

#include "graph.h"

int main()
{
    bool finn=false, finn2=false, gauche=false, fin_inna1=false, fin_inna2=false;
    int cpt=0, s1=13, s2=13, s=13, cpt_inna=0;
    int cptt=0;
    Sommet s3;
    Sommet s4;

    /// A appeler en 1er avant d'instancier des objets graphiques etc...
    grman::init();

    /// Le nom du répertoire où se trouvent les images à charger
    grman::set_pictures_path("pics");

    /// Un exemple de graphe
    Graph g;
    g.make_example();


    /// Vous gardez la main sur la "boucle de jeu"
    /// ( contrairement à des frameworks plus avancés )
    while ( !key[KEY_ESC] )
    {
        if(cpt>=1)
            cpt++;
        if(cpt_inna>=1)
            cpt_inna++;

        /// Il faut appeler les méthodes d'update des objets qui comportent des widgets
        g.ajouter_sommet();

        ///afficher map aretes
        //g.afficher_aretes();

        ///ajouter arete
        if(cptt>=1)
            cptt++;

        g.ajouter_arete(&finn, &finn2, &gauche, &cptt, &s1, &s2);

        //g.supp_arete(&fin_inna1, &fin_inna2, &cpt_inna, &s3, &s4, &s);
        std::cout << 1;
        g.supprimer_sommet(&fin_inna1, &cptt);
        std::cout << 2;
        g.update();
        std::cout << 3;

        /// Mise à jour générale (clavier/souris/buffer etc...)
        grman::mettre_a_jour();

        if(cpt>=51)
            cpt=50;
    }

    g.enregistrer_donnees_som();
    g.enregistrer_donnees_ar();

    grman::fermer_allegro();

    return 0;
}
END_OF_MAIN();


