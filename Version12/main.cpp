#include "grman/grman.h"
#include <iostream>
#include <string>

#include "graph.h"

int main()
{

    bool fin=false, finn2=false, gauche=false, fin_inna1=false, choix1=false, choix2=false, ev=false;
    int cpt=0, cpt2=0, s=0, s1=13, s2=13, cpt_inna=0, chaine=4;
    int cptt=0;
    std::string nom="", nom_fic_som="", nom_fic_ar="", nom_fic_idx_arc="";
    Sommet s3, s4;
    std::vector<Graph> g;
    Graph g_temp;

    g.push_back(g_temp);
    g.push_back(g_temp);

    /// Vous gardez la main sur la "boucle de jeu"
    /// ( contrairement � des frameworks plus avanc�s )
    while ( !key[KEY_ESC] )
    {
        if(chaine==4)
        {
            std::cout << "Entrer le reseau trophique a explorer :\n(Taper 'pics' pour graphe Ocean, 'pics2' pour graphe Savane)\n";
            std::cin >> nom;

            if(nom=="pics")
            {
                nom_fic_som="chaine/donnees_sommets1.txt";
                nom_fic_ar="chaine/relations1.txt";
                chaine=0;
            }
            else if(nom=="pics2")
            {
                nom_fic_som="chaine2/donnees_sommets2.txt";
                nom_fic_ar="chaine2/relations2.txt";
                chaine=1;
            }

            /// A appeler en 1er avant d'instancier des objets graphiques etc...
            grman::init();

            /// Le nom du r�pertoire o� se trouvent les images � charger
            grman::set_pictures_path(nom);

            /// Un exemple de graphe
            if(nom=="pics" && !choix1)
            {
                choix1=true;
                g[chaine].make_example(nom_fic_som, nom_fic_ar);
            }
            else if(nom=="pics2" && !choix2)
            {
                choix2=true;
                g[chaine].make_example(nom_fic_som, nom_fic_ar);
            }
        }

        if(cpt>=1)
            cpt++;
        if(cpt2>=1)
            cpt2++;
        if(cpt_inna>=1)
            cpt_inna++;
        if(cptt>=1)
            cptt++;

        /// Il faut appeler les m�thodes d'update des objets qui comportent des widgets
        //g[chaine].ajouter_sommet(chaine);
        //g[chaine].evolution_pop(&ev, &cpt2);

        ///afficher map aretes
        //g.afficher_aretes();

        ///ajouter arete

        //g[chaine].ajouter_arete(&finn, &finn2, &gauche, &cptt, &s1, &s2);

        g[chaine].supp_arete(&fin_inna1, &cpt_inna, &s);

        g[chaine].supprimer_sommet(&fin, &cptt);

        g[chaine].update();

        /// Mise � jour g�n�rale (clavier/souris/buffer etc...)
        grman::mettre_a_jour();

        if(cpt>=51)
            cpt=50;
        if(cpt2>=51)
            cpt2=50;

        if(key[KEY_E])
            chaine=4;
    }

    g[chaine].enregistrer_donnees_som(nom_fic_som);
    g[chaine].enregistrer_donnees_ar(nom_fic_ar);

    grman::fermer_allegro();
    std::cout << 5;

    return 0;
}
END_OF_MAIN();


