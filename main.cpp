#include "grman/grman.h"
#include <iostream>
#include <string>

#include "graph.h"

int main()
{

    bool finn=false, finn2=false, gauche=false, fin_inna1=false;

    int cpt=0, s1=13, s2=13, cpt_inna=0, s=0;

    int cptt=0;
    std::string nom="", nom_fic_som="", nom_fic_ar="";
    Sommet s3, s4;

    std::cout << "Entrer le reseau trophique a explorer :\n(Taper 'pics' pour graphe Ocean, 'pics2' pour graphe Savane)\n";
    std::cin >> nom;

    if(nom=="pics")
    {
        nom_fic_som="chaine/donnees_sommets1.txt";
        nom_fic_ar="chaine/relations1.txt";
    }
    else if(nom=="pics2")
    {
        nom_fic_som="chaine2/donnees_sommets2.txt";
        nom_fic_ar="chaine2/relations2.txt";
    }

    /// A appeler en 1er avant d'instancier des objets graphiques etc...
    grman::init();

    /// Le nom du répertoire où se trouvent les images à charger
    grman::set_pictures_path(nom);

    /// Un exemple de graphe
    Graph g;
    g.make_example(nom_fic_som, nom_fic_ar);


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

        g.supp_arete( &fin_inna1,&cpt_inna,&s);
        //int eidx;
       // g.test_remove_edge( eidx)
       // g.supprimer_sommet(&fin_inna1, &cptt);

        g.update();

        /// Mise à jour générale (clavier/souris/buffer etc...)
        grman::mettre_a_jour();

        if(cpt>=51)
            cpt=50;
        if(cpt_inna>=51)
            cpt_inna=50;


    }

    g.enregistrer_donnees_som(nom_fic_som);
    g.enregistrer_donnees_ar(nom_fic_ar);

    grman::fermer_allegro();

    return 0;
}
END_OF_MAIN();


