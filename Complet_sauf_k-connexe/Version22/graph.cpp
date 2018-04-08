#include "graph.h"

/***************************************************
                    VERTEX
****************************************************/

/// Le constructeur met en place les éléments de l'interface
VertexInterface::VertexInterface(int idx, int x, int y, std::string pic_name, int pic_idx)
{
    // La boite englobante
    m_top_box.set_pos(x, y);
    m_top_box.set_dim(130, 100);
    m_top_box.set_moveable();

    // Le slider de réglage de valeur
    m_top_box.add_child( m_slider_value );
    m_slider_value.set_range(0.0, 100.0);  // Valeurs arbitraires, à adapter...
    m_slider_value.set_dim(20,80);
    m_slider_value.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);

    // Label de visualisation de valeur
    m_top_box.add_child( m_label_value );
    m_label_value.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Down);

    // Une illustration...
    if (pic_name!="")
    {
        m_top_box.add_child( m_img );
        m_img.set_pic_name(pic_name);
        m_img.set_pic_idx(pic_idx);
        m_img.set_gravity_x(grman::GravityX::Right);
    }

    // Label de visualisation d'index du sommet dans une boite
    m_top_box.add_child( m_box_label_idx );
    m_box_label_idx.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Down);
    m_box_label_idx.set_dim(20,12);
    m_box_label_idx.set_bg_color(BLANC);

    m_box_label_idx.add_child( m_label_idx );
    m_label_idx.set_message( std::to_string(idx) );

}

/// Gestion du Vertex avant l'appel à l'interface
void Vertex::pre_update()
{
    ///Si m_interface n'existe pas (NULL)
    if (!m_interface)
        return;

    /// Copier la valeur locale de la donnée m_value vers le slider associé
    m_interface->m_slider_value.set_value(m_value);

    /// Copier la valeur locale de la donnée m_value vers le label sous le slider
    m_interface->m_label_value.set_message( std::to_string( (int)m_value) );
}


/// Gestion du Vertex après l'appel à l'interface
void Vertex::post_update()
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donnée m_value locale
    m_value = m_interface->m_slider_value.get_value();
}

/***************************************************
                    EDGE
****************************************************/

/// Le constructeur met en place les éléments de l'interface
EdgeInterface::EdgeInterface(Vertex& from, Vertex& to)
{
    // Le WidgetEdge de l'interface de l'arc
    if ( !(from.m_interface && to.m_interface) )
    {
        std::cerr << "Error creating EdgeInterface between vertices having no interface" << std::endl;
        throw "Bad EdgeInterface instanciation";
    }
    m_top_edge.attach_from(from.m_interface->m_top_box);
    m_top_edge.attach_to(to.m_interface->m_top_box);
    m_top_edge.reset_arrow_with_bullet();

    // Une boite pour englober les widgets de réglage associés
    m_top_edge.add_child(m_box_edge);
    m_box_edge.set_dim(24,60);
    m_box_edge.set_bg_color(BLANCBLEU);

    // Le slider de réglage de valeur
    m_box_edge.add_child( m_slider_weight );
    m_slider_weight.set_range(0.0, 100.0);  // Valeurs arbitraires, à adapter...
    m_slider_weight.set_dim(16,40);
    m_slider_weight.set_gravity_y(grman::GravityY::Up);

    // Label de visualisation de valeur
    m_box_edge.add_child( m_label_weight );
    m_label_weight.set_gravity_y(grman::GravityY::Down);

}

void Edge::set_thickness(float epais)
{
    ///Modifier l'épaisseur de l'arète selon son poids que l'on passe en paramètre
    m_interface->m_top_edge.set_thickness(epais);
}

/// Gestion du Edge avant l'appel à l'interface
void Edge::pre_update()
{
    ///Si m_interface est NULL
    if (!m_interface)
        return;

    /// Copier la valeur locale de la donnée m_weight vers le slider associé
    m_interface->m_slider_weight.set_value(m_weight);

    /// Copier la valeur locale de la donnée m_weight vers le label sous le slider
    m_interface->m_label_weight.set_message( std::to_string( (int)m_weight ) );
}

/// Gestion du Edge après l'appel à l'interface
void Edge::post_update()
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donnée m_weight locale
    m_weight = m_interface->m_slider_weight.get_value();
}



/***************************************************
                    GRAPH
****************************************************/

/// Ici le constructeur se contente de préparer un cadre d'accueil des
/// éléments qui seront ensuite ajoutés lors de la mise ne place du Graphe
GraphInterface::GraphInterface(int x, int y, int w, int h)
{
    /// La boite qui contient toute l'interface d'un graphe
    m_top_box.set_dim(1000,740);
    m_top_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);

    /// Dans cette boite seront ajoutés des boutons de contrôle etc...
    m_top_box.add_child(m_tool_box);
    m_tool_box.set_dim(80,720);
    m_tool_box.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);
    m_tool_box.set_bg_color(BLANCBLEU);

    /// Dans cette boite seront ajoutés les (interfaces des) sommets et des arcs...
    m_top_box.add_child(m_main_box);
    m_main_box.set_dim(908,720);
    m_main_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);
    m_main_box.set_bg_color(BLANCJAUNE);

    ///Bouton pour revenir au menu
    m_top_box.add_child(m_button_1);
    m_button_1.set_dim(35,18);
    m_button_1.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);
    m_button_1.set_bg_color(makecol(255,0,0));

    //Création du message correspondant au bouton
    m_top_box.add_child(m_button_1_label);
    m_button_1_label.set_message("MENU");
    m_button_1_label.set_gravity_x(grman::GravityX::Right);
    m_button_1_label.set_posy(7);

    ///Bouton pour ajouter un sommet
    m_top_box.add_child(m_option_1);
    m_option_1.set_dim(160,18);
    m_option_1.set_gravity_x(grman::GravityX::Right);
    m_option_1.set_posy(30);
    m_option_1.set_bg_color(makecol(175,175,255));

    //Création du message correspondant au bouton
    m_top_box.add_child(m_option1_label);
    m_option1_label.set_message("Ajouter un sommet");
    m_option1_label.set_gravity_x(grman::GravityX::Right);
    m_option1_label.set_posy(37);

    ///Bouton pour ajouter une arète
    m_top_box.add_child(m_option_2);
    m_option_2.set_dim(160,18);
    m_option_2.set_gravity_x(grman::GravityX::Right);
    m_option_2.set_posy(55);
    m_option_2.set_bg_color(makecol(175,175,255));

    //Création du message correspondant au bouton
    m_top_box.add_child(m_option2_label);
    m_option2_label.set_message("Ajouter une arete");
    m_option2_label.set_gravity_x(grman::GravityX::Right);
    m_option2_label.set_posy(62);

    ///Bouton pour supprimer un sommet
    m_top_box.add_child(m_option_3);
    m_option_3.set_dim(160,18);
    m_option_3.set_gravity_x(grman::GravityX::Right);
    m_option_3.set_posy(80);
    m_option_3.set_bg_color(makecol(175,175,255));

    //Création du message correspondant au bouton
    m_top_box.add_child(m_option3_label);
    m_option3_label.set_message("Supprimer un sommet");
    m_option3_label.set_gravity_x(grman::GravityX::Right);
    m_option3_label.set_posy(87);

    ///Bouton pour supprimer une arète
    m_top_box.add_child(m_option_4);
    m_option_4.set_dim(160,18);
    m_option_4.set_gravity_x(grman::GravityX::Right);
    m_option_4.set_posy(105);
    m_option_4.set_bg_color(makecol(175,175,255));

    //Création du message correspondant au bouton
    m_top_box.add_child(m_option4_label);
    m_option4_label.set_message("Supprimer une arete");
    m_option4_label.set_gravity_x(grman::GravityX::Right);
    m_option4_label.set_posy(112);

    ///Bouton k-connexe
    m_top_box.add_child(m_option_5);
    m_option_5.set_dim(160,18);
    m_option_5.set_gravity_x(grman::GravityX::Right);
    m_option_5.set_posy(130);
    m_option_5.set_bg_color(makecol(175,175,255));

    //Création du message correspondant au bouton
    m_top_box.add_child(m_option5_label);
    m_option5_label.set_message("K-connexite");
    m_option5_label.set_gravity_x(grman::GravityX::Right);
    m_option5_label.set_posy(137);

    ///Bouton fortement connexe
    m_top_box.add_child(m_option_6);
    m_option_6.set_dim(160,18);
    m_option_6.set_gravity_x(grman::GravityX::Right);
    m_option_6.set_posy(155);
    m_option_6.set_bg_color(makecol(175,175,255));

    //Création du message correspondant au bouton
    m_top_box.add_child(m_option6_label);
    m_option6_label.set_message("Fortement connexe");
    m_option6_label.set_gravity_x(grman::GravityX::Right);
    m_option6_label.set_posy(162);

    ///Bouton évolution
    m_top_box.add_child(m_option_7);
    m_option_7.set_dim(160,18);
    m_option_7.set_gravity_x(grman::GravityX::Right);
    m_option_7.set_posy(180);
    m_option_7.set_bg_color(makecol(175,175,255));

    //Création du message correspondant au bouton
    m_top_box.add_child(m_option7_label);
    m_option7_label.set_message("Evolution");
    m_option7_label.set_gravity_x(grman::GravityX::Right);
    m_option7_label.set_posy(187);
}

///Méthode d'ajout d'un sommet
void Graph::ajouter_sommet(int chaine)
{
    ///Déclarattion des variables
    bool bibli=false;
    int choix=0;
    Sommet s;

    ///Si l'utilisateur clique sur le bouton d'ajout d'un sommet
    if((mouse_b&1) && ((mouse_x>=640 && mouse_x<=800) && (mouse_y>=30 && mouse_y<=48)))
    {
        ///Booléen indiquant la sélection de l'utilisateur d'ajouter un sommet
        bibli=true;
    }

    ///Si l'utilisateur  souhaite ajouter un sommet est vrai
    if(bibli)
    {
        ///Affichage de la bibliothèque
        choix=grman::biblio(chaine);

        ///Boucle parcourant chaque case de la map de sommets (Vertex)
        for(std::map<int,Vertex>::iterator it=m_vertices.begin(); it!=m_vertices.end(); ++it)
        {
            ///Blindage : Si le sommet à ajouté est déjà présent dans le graphe
            if(choix==it->first+1)
            {
                ///On affecte à choix la valeur 13 -> n'existe pas donc aucun sommet ne sera ajouté
                choix=13;
                std::cout << "\nAjout impossible. Le sommet que vous desirez ajouter existe deja.\n\n";
            }
        }

        ///Si aucun sommet n'a été sélectionné
        if(choix==0)
        {
            std::cout << "Vous n'avez pas saisi un sommet valide\n";
        }
        else if(choix==1)   ///Si l'utilisateur souhaite ajouter le sommet 0
        {
            ///On récupère les coordonnées du click
            s.m_coordx=mouse_x;
            s.m_coordy=mouse_y;
            ///Nom de l'image à ouvrir
            s.m_nom_img="0.jpg";
            ///Numéro du sommet
            s.m_num=0;

            ///Ajout du sommet au vecteur de sommet
            m_vect_sommets.push_back(s);

            ///Incrémentation du nombre de sommets
            m_ordre+=1;

            ///Ajout du sommet à l'interface graphique
            add_interfaced_vertex(m_vect_sommets[m_ordre-1].m_num, m_vect_sommets[m_ordre-1].m_taille_pop, m_vect_sommets[m_ordre-1].m_coordx, m_vect_sommets[m_ordre-1].m_coordy, m_vect_sommets[m_ordre-1].m_nom_img);
        }
        else if(choix==2)   ///Si l'utilisateur souhaite ajouter le sommet 1
        {
            ///On récupère les coordonnées du click
            s.m_coordx=mouse_x;
            s.m_coordy=mouse_y;
            ///Nom de l'image à ouvrir
            s.m_nom_img="1.jpg";
            ///Numéro du sommet
            s.m_num=1;

            ///Ajout du sommet au vecteur de sommet
            m_vect_sommets.push_back(s);
            ///Incrémentation du nombre de sommets
            m_ordre+=1;

            ///Ajout du sommet à l'interface graphique
            add_interfaced_vertex(m_vect_sommets[m_ordre-1].m_num, m_vect_sommets[m_ordre-1].m_taille_pop, m_vect_sommets[m_ordre-1].m_coordx, m_vect_sommets[m_ordre-1].m_coordy, m_vect_sommets[m_ordre-1].m_nom_img);
        }
        else if(choix==3)    ///Si l'utilisateur souhaite ajouter le sommet 2
        {
            ///On récupère les coordonnées du click
            s.m_coordx=mouse_x;
            s.m_coordy=mouse_y;
            s.m_nom_img="2.jpg";
            s.m_num=2;

            m_vect_sommets.push_back(s);
            ///Incrémentation du nombre de sommets
            m_ordre+=1;

            ///Ajout du sommet à l'interface graphique
            add_interfaced_vertex(m_vect_sommets[m_ordre-1].m_num, m_vect_sommets[m_ordre-1].m_taille_pop, m_vect_sommets[m_ordre-1].m_coordx, m_vect_sommets[m_ordre-1].m_coordy, m_vect_sommets[m_ordre-1].m_nom_img);
        }
        else if(choix==4)    ///Si l'utilisateur souhaite ajouter le sommet 3
        {
            ///On récupère les coordonnées du click
            s.m_coordx=mouse_x;
            s.m_coordy=mouse_y;
            s.m_nom_img="3.jpg";
            s.m_num=3;

            m_vect_sommets.push_back(s);
            ///Incrémentation du nombre de sommets
            m_ordre+=1;

            ///Ajout du sommet à l'interface graphique
            add_interfaced_vertex(m_vect_sommets[m_ordre-1].m_num, m_vect_sommets[m_ordre-1].m_taille_pop, m_vect_sommets[m_ordre-1].m_coordx, m_vect_sommets[m_ordre-1].m_coordy, m_vect_sommets[m_ordre-1].m_nom_img);
        }
        else if(choix==5)    ///Si l'utilisateur souhaite ajouter le sommet 4
        {
            ///On récupère les coordonnées du click
            s.m_coordx=mouse_x;
            s.m_coordy=mouse_y;
            s.m_nom_img="4.jpg";
            s.m_num=4;

            m_vect_sommets.push_back(s);
            ///Incrémentation du nombre de sommets
            m_ordre+=1;

            ///Ajout du sommet à l'interface graphique
            add_interfaced_vertex(m_vect_sommets[m_ordre-1].m_num, m_vect_sommets[m_ordre-1].m_taille_pop, m_vect_sommets[m_ordre-1].m_coordx, m_vect_sommets[m_ordre-1].m_coordy, m_vect_sommets[m_ordre-1].m_nom_img);
        }
        else if(choix==6)    ///Si l'utilisateur souhaite ajouter le sommet 5
        {
            ///On récupère les coordonnées du click
            s.m_coordx=mouse_x;
            s.m_coordy=mouse_y;
            s.m_nom_img="5.jpg";
            s.m_num=5;

            m_vect_sommets.push_back(s);
            ///Incrémentation du nombre de sommets
            m_ordre+=1;

            ///Ajout du sommet à l'interface graphique
            add_interfaced_vertex(m_vect_sommets[m_ordre-1].m_num, m_vect_sommets[m_ordre-1].m_taille_pop, m_vect_sommets[m_ordre-1].m_coordx, m_vect_sommets[m_ordre-1].m_coordy, m_vect_sommets[m_ordre-1].m_nom_img);
        }
        else if(choix==7)    ///Si l'utilisateur souhaite ajouter le sommet 6
        {
            ///On récupère les coordonnées du click
            s.m_coordx=mouse_x;
            s.m_coordy=mouse_y;
            s.m_nom_img="6.jpg";
            s.m_num=6;

            m_vect_sommets.push_back(s);
            ///Incrémentation du nombre de sommets
            m_ordre+=1;

            ///Ajout du sommet à l'interface graphique
            add_interfaced_vertex(m_vect_sommets[m_ordre-1].m_num, m_vect_sommets[m_ordre-1].m_taille_pop, m_vect_sommets[m_ordre-1].m_coordx, m_vect_sommets[m_ordre-1].m_coordy, m_vect_sommets[m_ordre-1].m_nom_img);
        }
        else if(choix==8)    ///Si l'utilisateur souhaite ajouter le sommet 7
        {
            ///On récupère les coordonnées du click
            s.m_coordx=mouse_x;
            s.m_coordy=mouse_y;
            s.m_nom_img="7.jpg";
            s.m_num=7;

            m_vect_sommets.push_back(s);
            ///Incrémentation du nombre de sommets
            m_ordre+=1;

            ///Ajout du sommet à l'interface graphique
            add_interfaced_vertex(m_vect_sommets[m_ordre-1].m_num, m_vect_sommets[m_ordre-1].m_taille_pop, m_vect_sommets[m_ordre-1].m_coordx, m_vect_sommets[m_ordre-1].m_coordy, m_vect_sommets[m_ordre-1].m_nom_img);
        }
        else if(choix==9)    ///Si l'utilisateur souhaite ajouter le sommet 8
        {
            ///On récupère les coordonnées du click
            s.m_coordx=mouse_x;
            s.m_coordy=mouse_y;
            s.m_nom_img="8.jpg";
            s.m_num=8;

            m_vect_sommets.push_back(s);
            ///Incrémentation du nombre de sommets
            m_ordre+=1;

            ///Ajout du sommet à l'interface graphique
            add_interfaced_vertex(m_vect_sommets[m_ordre-1].m_num, m_vect_sommets[m_ordre-1].m_taille_pop, m_vect_sommets[m_ordre-1].m_coordx, m_vect_sommets[m_ordre-1].m_coordy, m_vect_sommets[m_ordre-1].m_nom_img);
        }
        else if(choix==10)    ///Si l'utilisateur souhaite ajouter le sommet 9
        {
            ///On récupère les coordonnées du click
            s.m_coordx=mouse_x;
            s.m_coordy=mouse_y;
            s.m_nom_img="9.jpg";
            s.m_num=9;

            m_vect_sommets.push_back(s);
            ///Incrémentation du nombre de sommets
            m_ordre+=1;

            ///Ajout du sommet à l'interface graphique
            add_interfaced_vertex(m_vect_sommets[m_ordre-1].m_num, m_vect_sommets[m_ordre-1].m_taille_pop, m_vect_sommets[m_ordre-1].m_coordx, m_vect_sommets[m_ordre-1].m_coordy, m_vect_sommets[m_ordre-1].m_nom_img);
        }
        else if(choix==11)    ///Si l'utilisateur souhaite ajouter le sommet 10
        {
            ///On récupère les coordonnées du click
            s.m_coordx=mouse_x;
            s.m_coordy=mouse_y;
            s.m_nom_img="10.jpg";
            s.m_num=10;

            m_vect_sommets.push_back(s);
            ///Incrémentation du nombre de sommets
            m_ordre+=1;

            ///Ajout du sommet à l'interface graphique

            add_interfaced_vertex(m_vect_sommets[m_ordre-1].m_num, m_vect_sommets[m_ordre-1].m_taille_pop, m_vect_sommets[m_ordre-1].m_coordx, m_vect_sommets[m_ordre-1].m_coordy, m_vect_sommets[m_ordre-1].m_nom_img);
        }
        else if(choix==12)    ///Si l'utilisateur souhaite ajouter le sommet 11
        {
            ///On récupère les coordonnées du click
            s.m_coordx=mouse_x;
            s.m_coordy=mouse_y;
            s.m_nom_img="11.jpg";
            s.m_num=11;

            m_vect_sommets.push_back(s);
            ///Incrémentation du nombre de sommets
            m_ordre+=1;

            ///Ajout du sommet à l'interface graphique
            add_interfaced_vertex(m_vect_sommets[m_ordre-1].m_num, m_vect_sommets[m_ordre-1].m_taille_pop, m_vect_sommets[m_ordre-1].m_coordx, m_vect_sommets[m_ordre-1].m_coordy, m_vect_sommets[m_ordre-1].m_nom_img);
        }
    }
}

///Enregistrer dans un fichier
void Graph::enregistrer_donnees_som(std::string nom_fic_som)
{
    ///Ouverture du fichier
    std::ofstream fichier(nom_fic_som, std::ios::in);

    ///Si le fichier a bien été ouvert/crée
    if(fichier)
    {
        ///Enregistrer le nombre de sommets du graphe
        fichier << m_vertices.size() << std::endl;

        ///Boucle de parcours des sommets du graphe
        for(std::map<int, Vertex>::iterator it=m_vertices.begin(); it!=m_vertices.end(); it++)
        {
            ///Enregistrer l'indice du sommet
            fichier << it->first << " ";
            fichier << it->second.m_value << " ";

            ///Enregistrer la position x
            if(it->second.m_interface->m_top_box.get_posx()<=0) //Blindage si la position x<0 -> posx=0
            {
                it->second.m_interface->m_top_box.set_posx(0);
                fichier << it->second.m_interface->m_top_box.get_posx() << " ";
            }
            else
                fichier << it->second.m_interface->m_top_box.get_posx() << " ";

            ///Enregistrer la position y
            if(it->second.m_interface->m_top_box.get_posy()<=0)  //Blindage si la position y<0 -> posy=0
            {
                it->second.m_interface->m_top_box.set_posy(0);
                fichier << it->second.m_interface->m_top_box.get_posy() << " ";
            }
            else
                fichier << it->second.m_interface->m_top_box.get_posy() << " ";

            ///Enregistrer le nom de l'image
            fichier << it->second.m_interface->m_img.m_pic_name << std::endl;
        }
        ///Fermeture du fichier
        fichier.close();
    }
}

///Récupérer dans le fichier
void Graph::recup_donnees_som(std::string nom_fic_som)
{
    Sommet s;

    std::ifstream fichier(nom_fic_som);

    if(fichier)
    {
        fichier >> m_ordre;

        std::cout << m_ordre <<" ";
        for(int i=0; i<m_ordre; ++i)
        {
            fichier >> s.m_num;
            fichier >> s.m_taille_pop;
            fichier >> s.m_coordx;
            fichier >> s.m_coordy;
            fichier >> s.m_nom_img;

            m_vect_sommets.push_back(s);
        }
        fichier.close();
    }
}

/// enregister pour les relations (arcs)

///Enregistrer dans le fichier des relations
void Graph::enregistrer_donnees_ar(std::string nom_fic_ar)
{
    std::ofstream fichier(nom_fic_ar, std::ios::in);

    std::cout << 3;
    if(fichier)
    {
        fichier << m_edges.size() << std::endl;

        for(std::map<int, Edge>::iterator it=m_edges.begin(); it!=m_edges.end(); it++)
        {
            fichier << it->first << " ";
            fichier << it->second.m_from << " ";
            fichier << it->second.m_to << " ";
            fichier << it->second.m_weight << std::endl;
        }
        fichier.close();
    }
    std::cout << 4;
}

///Récupérer dans le fichier relations
void Graph::recup_donnees_ar(std::string nom_fic_ar)
{
    Edge a;

    std::ifstream fichier(nom_fic_ar);

    if(fichier)
    {
        fichier >> m_nb_aretes;

        for(int i=0; i<m_nb_aretes; ++i)
        {
            fichier >> a.m_num_arete;
            fichier >> a.m_from;
            fichier >> a.m_to;
            fichier >> a.m_weight;

            m_vect_aretes.push_back(a);
        }

        fichier.close();
    }
}

/// Méthode spéciale qui construit un graphe arbitraire (démo)
/// Cette méthode est à enlever et remplacer par un système
/// de chargement de fichiers par exemple.
/// Bien sûr on ne veut pas que vos graphes soient construits
/// "à la main" dans le code comme ça.
void Graph::make_example(std::string nom_fic_som, std::string nom_fic_ar)
{
    m_interface = std::make_shared<GraphInterface>(50, 0, 750, 300);
    // La ligne précédente est en gros équivalente à :
    // m_interface = new GraphInterface(50, 0, 750, 600);

    ///Récupérer les données (coordonnées, taille population, nom de fichier image)
    recup_donnees_som(nom_fic_som);
    recup_donnees_ar(nom_fic_ar);

    /// Les sommets doivent être définis avant les arcs
    for (int i =0; i<m_ordre; i++)
    {
        add_interfaced_vertex(m_vect_sommets[i].m_num, m_vect_sommets[i].m_taille_pop, m_vect_sommets[i].m_coordx, m_vect_sommets[i].m_coordy, m_vect_sommets[i].m_nom_img);
    }

    /// Les arcs doivent être définis entre des sommets qui existent !
    // AJouter l'arc d'indice 0, allant du sommet 1 au sommet 2 de poids 50 etc...

    for (int i =0; i<m_nb_aretes; i++)
    {
        add_interfaced_edge(m_vect_aretes[i].m_num_arete, m_vect_aretes[i].m_from, m_vect_aretes[i].m_to, m_vect_aretes[i].m_weight);
    }
}

/// La méthode update à appeler dans la boucle de jeu pour les graphes avec interface
void Graph::update(int *chaine)
{
    if(m_interface->m_button_1.clicked())
        *chaine=4;

    if (!m_interface)
        return;

    for (auto &elt : m_vertices)
        elt.second.pre_update();

    for (auto &elt : m_edges)
        elt.second.pre_update();

    m_interface->m_top_box.update();

    for (auto &elt : m_vertices)
        elt.second.post_update();

    for (auto &elt : m_edges)
        elt.second.post_update();

    this->set_thickness();
}

/// Aide à l'ajout de sommets interfacés
void Graph::add_interfaced_vertex(int idx, double value, int x, int y, std::string pic_name, int pic_idx )
{
    if ( m_vertices.find(idx)!=m_vertices.end() )
    {
        std::cerr << "Error adding vertex at idx=" << idx << " already used..." << std::endl;
        throw "Error adding vertex";
    }
    // Création d'une interface de sommet
    VertexInterface *vi = new VertexInterface(idx, x, y, pic_name, pic_idx);
    // Ajout de la top box de l'interface de sommet
    m_interface->m_main_box.add_child(vi->m_top_box);
    // On peut ajouter directement des vertices dans la map avec la notation crochet :
    m_vertices[idx] = Vertex(value, vi);
}

/// Aide à l'ajout d'arcs interfacés
void Graph::add_interfaced_edge(int idx, int id_vert1, int id_vert2, double weight)
{
    if ( m_edges.find(idx)!=m_edges.end() )
    {
        std::cerr << "Error adding edge at idx=" << idx << " already used..." << std::endl;
        throw "Error adding edge";
    }

    if ( m_vertices.find(id_vert1)==m_vertices.end() || m_vertices.find(id_vert2)==m_vertices.end() )
    {
        std::cerr << "Error adding edge idx=" << idx << " between vertices " << id_vert1 << " and " << id_vert2 << " not in m_vertices" << std::endl;
        throw "Error adding edge";
    }

    EdgeInterface *ei = new EdgeInterface(m_vertices[id_vert1], m_vertices[id_vert2]);
    m_interface->m_main_box.add_child(ei->m_top_edge);
    m_edges[idx] = Edge( weight, ei);
    /// OOOPS ! Prendre en compte l'arc ajouté dans la topologie du graphe !
    m_edges[idx].m_from = id_vert1;
    m_edges[idx].m_to = id_vert2;
    m_vertices[id_vert1].m_out.push_back(id_vert2);
    m_vertices[id_vert2].m_in.push_back(id_vert1);
}

///afficher la map d'arete
void Graph::afficher_aretes()
{
    for (const auto &elem : m_edges)
    {
        std::cout <<elem.first;
        std::cout <<elem.second.m_from;
        std::cout <<std::endl;
    }
}

void Graph::ajouter_arete(bool *finn, bool *finn2, bool *gauche, int *cptt, int *s1, int *s2)
{
    /// si il clique sur ajouter un sommet
    if(m_interface->m_option_2.clicked())
    {
        *finn=true;
        *cptt=1;
        std::cout << "Choisissez les deux sommets entre lesquels vous souhaitez ajouter une arete." <<std::endl;
    }

/// si il clique GAUCHE et dans l'ecran sur un sommet
    else if((mouse_b&1) && ((mouse_x>=0 && mouse_x<=800) && (mouse_y>=0 && mouse_y<=600)) && *finn && *cptt>=50)
    {
        ///on recupère les coordonnées de la ou on a clique
        double mouseposx = mouse_x;
        double mouseposy = mouse_y;

        for (std::map<int, Vertex>::iterator it=m_vertices.begin(); it!=m_vertices.end(); it++)
        {
            /// si il clique sur un sommet
            if ( mouseposy >=it->second.m_interface->m_top_box.get_posy() && mouseposy <=it->second.m_interface->m_top_box.get_posy() + 100 && mouseposx>=it->second.m_interface->m_top_box.get_posx()-80 && mouseposx <= it->second.m_interface->m_top_box.get_posx() +20 )
            {
                *s1=it->first;
            }
            ///on recupère ce sommet
        }
        *gauche=true;
    }

    if(*s1==13 && *gauche && *cptt>=40)
    {
        std::cout << "\nLe sommet selectionne n'existe pas.\n";
        *finn=false;
        *gauche=false;
    }

    /// s'il clique DROIT
    if (mouse_b&2 && ((mouse_x>=0 && mouse_x<=800) && (mouse_y>=0 && mouse_y<=600)) && *gauche)
    {
        double mouseposx = mouse_x;
        double mouseposy = mouse_y;

        for (std::map<int, Vertex>::iterator it=m_vertices.begin(); it!=m_vertices.end(); it++)
        {
            /// si il clique sur un sommet
            if (mouseposy >=it->second.m_interface->m_top_box.get_posy() && mouseposy <=it->second.m_interface->m_top_box.get_posy() + 100 && mouseposx>=it->second.m_interface->m_top_box.get_posx()-80 && mouseposx <= it->second.m_interface->m_top_box.get_posx() +20)
            {
                ///on recupère ce sommet
                *s2 = it->first;
            }
        }


        ///on créer une nouvelle arete du s1 au s2
        Edge e;
        std::map<int, Edge>::iterator f;
        f=m_edges.end();
        std::cout << "first" << f->first;
        e.m_num_arete=(f->first)+1;
        e.m_from= *s1;
        e.m_to=*s2;

        e.m_weight= 0;

        if(*s2!=13)
        {
            /// on l'ajoute au vecteur d'aretes
            m_vect_aretes.push_back(e);

            ///on l'ajoute à l'arète
            add_interfaced_edge(m_vect_aretes.size(), *s1, *s2, 0 );
            m_nb_aretes+=1;
            *cptt=0;
            *finn=false;
            *gauche = false;
            *s1=13;
            *s2=13;
        }
        else
        {
            std::cout << "\n\nLe sommet selectionne n'existe pas.\n\n";
            *cptt=0;
            *finn=false;
            *gauche = false;
            *s1=13;
            *s2=13;
        }
        *cptt=0;
    }
}

///Méthode de suppression d'un sommet
void Graph::supprimer_sommet(bool *fin1, int *cptt)
{
    std::vector<int> sup;
    /// si il clique sur ajouter un sommet
    if(m_interface->m_option_3.clicked())
    {
        *fin1=true;
        *cptt=1;
        std::cout << "Choisissez le sommet a supprimer." << std::endl;
    }

    /// si il clique GAUCHE et dans l'ecran sur un sommet
    else if((mouse_b&1) && ((mouse_x>=0 && mouse_x<=800) && (mouse_y>=0 && mouse_y<=600)) && *fin1 && *cptt>=30)
    {
        ///on recupère les coordonnées de là où on a clique
        double mouseposx = mouse_x;
        double mouseposy = mouse_y;

        for (std::map<int, Vertex>::iterator it=m_vertices.begin(); it!=m_vertices.end(); it++)
        {
            sup.clear();
            if (mouseposy >=it->second.m_interface->m_top_box.get_posy() && mouseposy <=it->second.m_interface->m_top_box.get_posy() + 100 && mouseposx>=it->second.m_interface->m_top_box.get_posx()-80 && mouseposx <= it->second.m_interface->m_top_box.get_posx() +20 )
            {
                for (std::map<int, Edge>::iterator it2=m_edges.begin(); it2!=m_edges.end(); it2++)
                {
                    if (it2->second.m_from==it->first || it2->second.m_to==it->first)
                    {
                        sup.push_back(it2->first);
                        m_nb_aretes-=1;
                        *fin1=false;
                        *cptt=0;
                    }
                }

                if(sup.size()!=0)
                {
                    for(unsigned int i=0; i<sup.size(); ++i)
                    {
                        m_nb_aretes-=1;
                        test_remove_edge(sup[i]);
                    }
                }


                /// si il clique sur un sommet
                m_interface->m_main_box.remove_child(m_vertices[it->first].m_interface->m_top_box);
                m_vertices.erase(it);
                return;
            }
        }
        *cptt=0;
    }
}

void Graph::test_remove_edge(int eidx)
{
/// référence vers le Edge à enlever
    Edge &remed=m_edges.at(eidx);

///Affichage
//    std::cout << 2 << m_vertices.size() << std::endl;
//
//    std::cout << "Removing edge " << eidx << " " << remed.m_from << "->" << remed.m_to << " " << remed.m_weight << std::endl;
//
///// Tester la cohérence : nombre d'arc entrants et sortants des sommets 1 et 2
//    std::cout << m_vertices[remed.m_from].m_in.size() << " " << m_vertices[remed.m_from].m_out.size() << std::endl;
//    std::cout << m_vertices[remed.m_to].m_in.size() << " " << m_vertices[remed.m_to].m_out.size() << std::endl;
//    std::cout << m_edges.size() << std::endl;
//
//    std::cout << 3 << m_vertices.size() << std::endl;

/// test : on a bien des éléments interfacés
    if (m_interface && remed.m_interface)
    {
/// Ne pas oublier qu'on a fait ça à l'ajout de l'arc :
        /* EdgeInterface *ei = new EdgeInterface(m_vertices[id_vert1], m_vertices[id_vert2]); */
        /* m_interface->m_main_box.add_child(ei->m_top_edge); */
        /* m_edges[idx] = Edge(weight, ei); */
/// Le new EdgeInterface ne nécessite pas de delete car on a un shared_ptr
/// Le Edge ne nécessite pas non plus de delete car on n'a pas fait de new (sémantique par valeur)
/// mais il faut bien enlever le conteneur d'interface m_top_edge de l'arc de la main_box du graphe
        m_interface->m_main_box.remove_child( remed.m_interface->m_top_edge );

//        std::cout << 4 << m_vertices.size() << std::endl;
    }

/// Il reste encore à virer l'arc supprimé de la liste des entrants et sortants des 2 sommets to et from !
/// References sur les listes de edges des sommets from et to
    std::vector<int> &vefrom = m_vertices[remed.m_from].m_out;
    std::vector<int> &veto = m_vertices[remed.m_to].m_in;
    vefrom.erase( std::remove( vefrom.begin(), vefrom.end(), eidx ), vefrom.end() );
    veto.erase( std::remove( veto.begin(), veto.end(), eidx ), veto.end() );
//    std::cout << 5 << m_vertices.size() << std::endl;

/// Le Edge ne nécessite pas non plus de delete car on n'a pas fait de new (sémantique par valeur)
/// Il suffit donc de supprimer l'entrée de la map pour supprimer à la fois l'Edge et le EdgeInterface
/// mais malheureusement ceci n'enlevait pas automatiquement l'interface top_edge en tant que child de main_box !
    m_edges.erase( eidx );

/// Tester la cohérence : nombre d'arc entrants et sortants des sommets 1 et 2
//    std::cout << m_vertices[remed.m_from].m_in.size() << " " << m_vertices[remed.m_from].m_out.size() << std::endl;
//    std::cout << m_vertices[remed.m_to].m_in.size() << " " << m_vertices[remed.m_to].m_out.size() << std::endl;
//    std::cout << m_vertices.size() << std::endl;
}

void Graph::ar_incidentes(bool *click, int *v, int *s, int *s2)
{
    if((mouse_b&1) && ((mouse_x>=0 && mouse_x<=800) && (mouse_y>=0 && mouse_y<=600)) )
    {
        ///on recupère les coordonnées de la ou on a clique
        double mouseposx = mouse_x;
        double mouseposy = mouse_y;

        for (std::map<int, Vertex> :: iterator it=m_vertices.begin(); it!=m_vertices.end(); ++it)
        {

            /// si il clique sur un sommet
            if ( mouseposy >=  it->second.m_interface->m_top_box.get_posy() && mouseposy <=it->second.m_interface->m_top_box.get_posy()  + 100 &&mouseposx>=it->second.m_interface->m_top_box.get_posx() -80 && mouseposx <= it->second.m_interface->m_top_box.get_posx()  +20 )
            {
                *v=it->first;
                std::cout << "sommet : "<<*v;

            }
            ///on recupère ce sommet

        }
        *click=true;
    }
    else if (*click)
    {
        std::map<int, Vertex> :: iterator it_sommet;
        it_sommet=m_vertices.find(*v);
        for (std::map<int, Edge> :: iterator it=m_edges.begin(); it!=m_edges.end(); ++it)
        {

            if (it->second.m_from == *v )
            {
                it_sommet->second.m_out.push_back(it->first);
            }
            else if (it->second.m_to == *v)
            {
                it_sommet->second.m_in.push_back(it->first);
            }

        }

        *click =false;
        ///affichage des vecteurs in et out
        /* for (unsigned int i =0; i<m_vertices[*v].m_in.size(); ++i)
         {
             std :: cout << "in " << it_sommet->second.m_in[i]<< std::endl;

         }

         for (unsigned int i=0; i<m_vertices[*v].m_out.size(); ++i)
         {
             std :: cout << "out " << it_sommet->second.m_out[i]<< std::endl;

         }*/

    }
}

///Fonction pour supprimer une arete
void Graph::supp_arete(bool *fin_inna1, int *cpt_inna, int *s)
{
    Edge arete_supp;
    std::map<int,Edge>::iterator it1;
    bool etape_suiv=false;
    bool *p_etape_suiv;
    p_etape_suiv= &etape_suiv;

    bool etape_suiv1=false;
    bool *p_etape_suiv1;
    p_etape_suiv1=&etape_suiv1;
    bool commenceSnd=false;

    int s2=0;

    ///Si on clique dans le menu sur supprimer une arete
    if(m_interface->m_option_4.clicked() && !(*fin_inna1))
    {
        *fin_inna1=true;
        *cpt_inna=1;
        std::cout<<"Cliquer sur le sommet d'ou part l'arete"<<std::endl;

        for (std::map<int, Edge>::iterator it = m_edges.begin(); it!=m_edges.end(); ++it)
        {
            std::cout << it->first << " " << it->second.m_from << " " << it->second.m_to << std::endl;
        }
    }

    else if( mouse_b&1 && mouse_x>=0 && mouse_x<=800 && mouse_y>=0 && mouse_y<=600 && (*fin_inna1) && (*cpt_inna>=50))
    {
        std::cout<<"on clique gauche"<<std::endl;
        int  mousepos_x=mouse_x;
        int  mousepos_y=mouse_y;

        for (std::map<int, Vertex>::iterator it = m_vertices.begin(); it!=m_vertices.end(); ++it)
        {
            std::cout << "On regarde si il y a un sommet correspondant" <<std::endl;

            if ( mousepos_y >=  it->second.m_interface->m_top_box.get_posy() && mousepos_y <=it->second.m_interface->m_top_box.get_posy()  + 100 &&mousepos_x>=it->second.m_interface->m_top_box.get_posx() -80 && mousepos_x <= it->second.m_interface->m_top_box.get_posx()  +20)
            {
                *s=it->first;
                std::cout<<"on a trouve s1 "<<*s<<std::endl;
            }
            *p_etape_suiv=true;
        }

        std::cout<<"Tres bien, veuillez maintenant cliquer sur le sommet d'arrivee de l'arete"<<std::endl;

        while (!commenceSnd && (*p_etape_suiv))
        {
            if(mouse_b&2 )
            {
                int  mousepos_x=mouse_x;
                int  mousepos_y=mouse_y;

                commenceSnd=true;

                for ( std::map<int, Vertex>::iterator it = m_vertices.begin(); it!=m_vertices.end(); ++it )
                {
                    if ( mousepos_y >=  it->second.m_interface->m_top_box.get_posy() && mousepos_y <=it->second.m_interface->m_top_box.get_posy()  + 100 &&mousepos_x>=it->second.m_interface->m_top_box.get_posx() -80 && mousepos_x <= it->second.m_interface->m_top_box.get_posx()  +20)
                    {
                        s2=it->first;
                        std::cout<<"on a trouve s2 "<<s2<<std::endl;
                        *p_etape_suiv1=true;
                    }
                }
            }
        }

        for(std::map<int, Vertex>::iterator it=m_vertices.begin(); it!=m_vertices.end(); it++)
        {
            if(it->first==*s)
            {
                std::cout << "\nPosX avant: " << it->second.m_interface->m_top_box.get_posx() << "\nPosY avant: " << it->second.m_interface->m_top_box.get_posy();
            }
        }

        if(*p_etape_suiv1==true && *p_etape_suiv==true)
        {
            for (std::map<int, Edge>::iterator it=m_edges.begin(); it!=m_edges.end(); it++)
            {
                if ((it->second.m_from==*s && it->second.m_to==s2) || (it->second.m_from==s2 && it->second.m_to==*s))
                {
                    test_remove_edge(it->first);
                    *fin_inna1=false;
                    *cpt_inna=0;
                    *p_etape_suiv=false;
                    *p_etape_suiv1=false;

                    return;
                }
            }
        }
    }
}

void Graph::set_thickness()
{
    for(auto& elem : m_edges)
    {
        elem.second.set_thickness(elem.second.m_weight);
    }
}

int Graph ::connexe()
{
    bool nelly1=false;
    int ctp=0;
    int ordre=0;
    int it, it_out=0;
    std::vector<int> sommets;

    std::cout << "\nMINcon " << m_vertices[0].m_in.size();

    if(nelly1 ==false)
    {
        for (std::map <int, Vertex> :: iterator it1=m_vertices.begin(); it1!=m_vertices.end(); ++it1)
        {
            ///on regarde tous les sommets choisis
            if (it1->second.m_actif)
            {
                ///on les marque a false
                it1->second.m_marque=false;
            }

        }
        nelly1 = true;
    }



    //on créer une file ou sont ranger les sommets
    std::queue<int> file;

    ///on trouve l'ordre du graphe av les sommets selectionnes
    for (std::map <int, Vertex> ::iterator itera = m_vertices.begin(); itera!=m_vertices.end(); ++itera)
    {
        if ( itera->second.m_actif == true )
        {
            ordre+=1;
        }

    }

    /// si on est passe dans la file une fois et qu'elle etait vide, plus de sommets adjacents



    for (auto elem : m_vertices)
    {

        std::cout << "Je suis : " << elem.first;
        if(elem.second.m_actif && !elem.second.m_marque )
        {
            std::cout << " et je suis rentré dans la boucle" << std::endl;
//std::cout << " le premier a etre mis : " <<som->first<<std::endl;
            elem.second.m_marque= true;
            file.push(elem.first);
            sommets.push_back(elem.first);

// boucle tant que la file n'est pas vide
//!*nelly2
            while (!file.empty() )
            {
                it=file.front();
                file.pop();

                //  std::cout<<"dans connexite, nb de sommets dans m_vertices : "<<m_vertices.size()<<std::endl;
                if ( m_vertices[it].m_out.empty() )
                {
                    std::cout<<"pas de successeurs"<<std::endl;
                }

                /// si le sommet est deconnecte du graphe

                //on parcourt tous ses voisins in


                std::cout << "\nMIN " << m_vertices[0].m_in.size() << " " << m_vertices[it].m_in.size() << "MOUT" << m_vertices[it].m_out.size() << "\n";

                for (unsigned int i=0; i<m_vertices[it].m_in.size(); ++i)
                {

                    std::map <int, Edge>:: iterator ite2;
                    //on récupère le numero de l'arete
                    ite2= m_edges.find(m_vertices[it].m_in[i]);
                    std::cout << "L'indice de l'arete est : " << ite2->first << std::endl;
                    //si le sommet m_from de l'arete est

                    if ( m_vertices[ite2->second.m_from].m_actif ==true && m_vertices[ite2->second.m_from].m_marque==false )
                    {
                        //on le marque
                        m_vertices[ite2->second.m_from].m_marque=true;

                        //on le push dans la file
                        file.push(ite2->second.m_from);

                        std::cout << "Je pushback" << std::endl;
                        sommets.push_back(ite2->second.m_from);
                        //std::cout << "pour m_in" << std::endl;
                    }
//            for (auto elem : sommets)
//            {
//                std::cout << elem <<std::endl;
//            }

                }


                //on parcourt tous ses voisins out
                for (unsigned int i=0; i<m_vertices[it].m_out.size(); ++i)
                {

                    std::map <int, Edge>:: iterator ite2;

                    ite2= m_edges.find(m_vertices[it].m_out[i]);

                    //std::cout << m_vertices[ite2->second.m_from].m_marque;
                    if ( m_vertices[ite2->second.m_to].m_actif ==true && m_vertices[ite2->second.m_to].m_marque==false)
                    {

                        m_vertices[ite2->second.m_to].m_marque=true;

                        //on le push dans la file
                        file.push(ite2->second.m_to);
                        sommets.push_back(ite2->second.m_to);
                        //std::cout << "pour m_out" << std::endl;
                    }
                }

                if (file.empty())
                {
                    return sommets.size();
                }
            }
        }
    }

    for (auto elem:m_vertices)
    {
        if(elem.second.m_actif ==  false)
        {
            std::cout << "sommet d'indice " << elem.first << " actif = false " <<std::endl;
        }
    }

    return 0;
}

///sous programmme permettant de trouver les k parmis n
///nous nous sommes inspirées des codes d'aides envoyés par nos profs
/// METTRE LIEN
/// en collaboration en Sarah LE
std::vector<std::vector <int>> Graph :: combinaisons ( int k)
{
    std::vector< std::vector <int>> combi;
    std::vector<int> temp;
    std::string bitmask(k, 1);
    bitmask.resize(m_ordre,0);

    do
    {
        for (int i=0; i<m_ordre; ++i)
        {
            if (bitmask[i])
            {
                std::cout<< " " << i;

                temp.push_back(i);
            }

        }
        combi.push_back(temp);
        temp.clear();



        std::cout <<std::endl;
    }
    while (std:: prev_permutation(bitmask.begin(), bitmask.end()));


    return combi;
}

void Graph::k_connexe(int k, Graph g)
{
    if(m_interface->m_option_5.clicked())
    {
        int ordre_depart2=0;
        int ordre_connexe=0;
        int nv_ordre=0;
        // ordre_connexe= connexe(nelly1, nelly2);
        //bool oui=true;
        bool encore_connexe=true;


        int compteur_actif=0;


        std::vector<std::vector<int>> combin;

//    if ( m_ordre == ordre_depart2)
//    {
//        oui =true;
//    }
///si notre graphe est connexe

        //std::cout << " dans le premier if" << std::endl;
//
//     for (std::map <int, Vertex> :: iterator it=m_vertices.begin(); it!= m_vertices.end(); ++it)
//        {
//            if (it->second.m_actif == false)
//                compteur++; ///m_ordre du nv graphe, nb de sommets actifs
//
//        }

///on recherche le nombre de combinaisons possibles
        combin= combinaisons(3);
        //std::cout<<"combi . size" << combin.size() <<std::endl;

        /// tant que le graphe est encore connexe
        while(encore_connexe)
        {
            ///on parcourt le vecteur de vecteur combi (pour toutes les combinaisons
            for (unsigned int i=0; i<combin.size(); ++i)
            {

                nv_ordre=0;
                ordre_connexe=0;
                compteur_actif=0;
//            for (std::map <int, Vertex> :: iterator it=m_vertices.begin(); it!= m_vertices.end(); ++it)
//            {
//                it->second.m_actif = true;
//
//            }

                for (auto elem : m_vertices)
                {
                    m_vertices[elem.first]=true;
                }
                /// a chaque tour on met un certains nombre k de sommets a actif=false
                for (unsigned int j=0; j<combin[i].size(); ++j)
                {
//std::cout << " combn.size" << combin[i].size() <<std::endl;
                    m_vertices[combin[i][j]].m_actif = false;
                    compteur_actif+=1;
                    // std::cout << "compteur actif : " <<compteur_actif<<std::endl;

                }
                std::cout <<compteur_actif<< " sont mis a false " <<std::endl;

///calcul du nouveal ordre sans les sommets non actifs
                for (std::map <int, Vertex> :: iterator it=m_vertices.begin(); it!= m_vertices.end(); ++it)
                {
                    if (it->second.m_actif == true)
                        nv_ordre++; ///m_ordre du nv graphe, nb de sommets actifs

                }

                std::cout << "nv ordre" <<nv_ordre<<std::endl;

                ordre_connexe=g.connexe();
                std::cout << " ordre connexe"<<ordre_connexe<<std::endl;
                ///con = nb de sommets qui appartiennent a la composante connexe

                if ( nv_ordre == ordre_connexe)
                {

                    std::cout << "le graphe est encore connexe" <<std::endl;

                }
                else if (nv_ordre != ordre_connexe)  /// si il y a le meme nombre de sommets dans le graphe que dans la comp connexe alors le graphe est connexe
                {

                    std::cout << "plus connexe et le nb d sommet a enlever est " << k<<std::endl;
                    std::cout << "les sommets retires sont " <<std::endl;
                    for (std::map <int, Vertex> :: iterator it=m_vertices.begin(); it!= m_vertices.end(); ++it)
                    {
                        if(it->second.m_actif == false)
                        {
                            std::cout << it->first << " | ";
                        }
                    }
                    std::cout<<std::endl;


                    encore_connexe =false;

                }


            }
        }
    }

}

void Graph::evolution_pop(bool *ev)
{
    double K=0, Nt=0, r=0.00000005, Nt1=0, Nt2=0, vitesse=0.3;
    int s=0, cpttemp=0;
    std::map<int, Vertex> :: iterator temp;

    if(m_interface->m_option_7.clicked())
    {
        *ev=true;

    }
    if(key[KEY_S])
    {
        *ev=false;
    }

    if(*ev)
    {
        ///Calcul du K
        for(std::map<int, Vertex>::iterator it = m_vertices.begin(); it!=m_vertices.end(); ++it)
        {
            K=0;
            Nt=0;
            Nt1=0;
            Nt2=0;
            cpttemp=0;
            vitesse=0.3;
            r=0.005;

            Nt=it->second.m_value;

            std::cout << "\n\nEspece: " << it->first << "\nNt: " << Nt;
            std::cout << "\nK: " << K << std::endl;

            ///Boucle de parcours du vecteur d'arètes
            for(std::map<int, Edge>::iterator it2 = m_edges.begin(); it2!=m_edges.end(); ++it2)
            {
                ///Si le prédateur de l'arète est le sommet actuel
                if(it->first==it2->second.m_to)
                {
                    cpttemp++;
                    s=it2->second.m_from;
                    temp=m_vertices.find(s);
                    K+=temp->second.m_value*((it2->second.m_weight)/100);
                }
            }

            if(it->second.m_in.size()==0)
            {
                for(std::map<int, Edge>::iterator it2 = m_edges.begin(); it2!=m_edges.end(); ++it2)
                {
                    if(it->first==it2->second.m_from)
                    {
                        s=it2->second.m_to;
                        temp=m_vertices.find(s);
                        Nt2-=temp->second.m_value*(it2->second.m_weight/100);
                    }
                }

                if(Nt2==0)
                    Nt1= Nt + (0.1 * Nt * r);
                else
                    Nt1= Nt - (0.1 * Nt * r);

                std::cout << "Pas bouffe" << r;
            }

            else if((it->second.m_in.size()==0 && it->second.m_in.size()==0) || cpttemp==0)
            {
                r=0.05;
                Nt1= Nt + (0.1 * Nt * r);
                std::cout << "Personne";
            }

            else if(it->second.m_out.size()==0)
            {
                std::cout <<(0.001*Nt*(1-(Nt/K)));
                if(K!=0)
                    Nt1= Nt+(0.001*Nt*(1-(Nt/K)))-(0.0001*(-0.3));
                else
                    Nt1=Nt-0.1;

                std::cout << "Pas maitre" << it->second.m_in.size();
            }

            else
            {

                std::cout << "Tout";
                for(std::map<int, Edge>::iterator it2 = m_edges.begin(); it2!=m_edges.end(); ++it2)
                {
                    if(it->first==it2->second.m_from)
                    {
                        s=it2->second.m_to;
                        temp=m_vertices.find(s);
                        std::cout << "p" << it2->second.m_weight;
                        Nt2-=(temp->second.m_value/15)*(it2->second.m_weight/100);
                    }
                }
                Nt2=Nt2*vitesse;
                std::cout << "Nt2: " << Nt2 << std::endl;

                if(K!=0)
                    Nt1=Nt+(r*Nt*(1-(1/K)))+Nt2;
                else
                    Nt1=Nt+(r*Nt)+Nt2;

            }


            std::cout << "\nNt1nouv: " << Nt1 << std::endl;

            if(Nt1>=100)
                Nt1=100;
            if(Nt1<=0)
                Nt1=0;

            std::cout << "\nNt1: " << Nt1<< std::endl;
            it->second.m_value=Nt1;
        }
    }
}
void Graph :: matrice_adj()
{
    int a=0;
    int b=0;
    double poids=0;
    std::vector<int> matrice_temp;
    std::map<int, Edge>::iterator it;

    for (int i=0; i<m_ordre; i++)
    {
        for (int j=0; j<m_ordre; j++)
        {
            matrice_temp.push_back(0);
        }
        m_matrice_adj.push_back(matrice_temp);
    }

    for (std::map<int,Edge>::iterator it2=m_edges.begin(); it2!=m_edges.end(); ++it2)
    {
        it= m_edges.find(it2->first);
        a=it->second.m_from;

        b=it->second.m_to;

        poids=it->second.m_weight;

        m_matrice_adj[a][b]=poids;

    }


    for (int n=0; n<m_ordre; n++)
    {
        for (int m=0; m<m_ordre; m++)
        {
            if (n==m)
                m_matrice_adj[n][m]=1;
        }
    }

}
std::vector <int> Graph::une_compo_fortement_connexes(int s)
{

    ///Fonction qui retournent un tab dynamique de booléens indiquant si les sommets forment ou non un circuit
    ///(composante fortement connexe) en passant par un sommet s

    matrice_adj();


///Definition variables locales
    std::vector <int> c1; ///Composantes connexes directes partant de s
    std::vector <int> c2; ///indirectes arrivant vers s
    std::vector <int> c; ///composante fortement connexe = c1 inter c2 à retourner
    int x, y; ///numeros de sommets intermédiaires des composantes connexes
    int ajoute = 1; ///booléen indiquant si une nouvelle composante connexe est ajoutée

///Initialisation à false des marqueurs de sommets
    for (std::map<int, Vertex>::iterator it = m_vertices.begin(); it!=m_vertices.end(); ++it)
    {
        it->second.m_marque=false;

    }
///C1 vecteur qui dit si sommet s connexe avec le sommet indice i
    for (int i=0; i<m_ordre; i++)
    {
        c1.push_back(0);
    }

///Rendre le sommet s connexe
    c1[s]=1 ;

///Recherche des composantes connexes partant de s à ajouter dans c1
    std::map<int,Vertex>::iterator itx;
    std::map<int,Vertex>::iterator ity;

///Tant qu'on ajoute encore des sommets dans notre composante
    while (ajoute==1)
    {
        ajoute=0; /// à chaque tour, recherche d'une nouvelle composante connexe à ajouter
///Pour tous les sommets x non marques et connectes en partant de s
///Marquer chaque sommet x et connecter les sommets non marqués y adjacents à x

///Parcourons nos sommets une premiere fois
        for (x=0; x<m_ordre; x++)
        {

            itx= m_vertices.find(x);
///Si ce sommet n'est pas marque et qu'il est connecte a notre sommet de départ (si c'est la premiere fois qu'on rentre dans la boucle y a que 0 qui passe)
            if ( itx->second.m_marque==false && c1[itx->first]==1)
            {
                ///On marque le sommet
                itx->second.m_marque=true;

                ///On parcourt une seconde fois nos sommets
                for (y=0; y<m_ordre; y++)
                {

                    ity=m_vertices.find(y);

                    ///Si ces deux sommets sont connectes et que le 2e sommets n'est pas marqué non plus (donc pour 0 on doit trouver tous ses voisins)
                    if (m_matrice_adj[x][y]!=0 && ity->second.m_marque==false )
                    {
                        ///On dit que le deuxieme sommet est connexe avec le sommet s
                        c1[y]=1;
                        ajoute=1; ///Nouvelle composante connexe ajoutee
                    }

                }

            }

        }

    } ///Fin du while

///Recherche des composantes connexes connexes arrivant à s à ajouter dans c2
    for (std::map<int, Vertex>::iterator it = m_vertices.begin(); it!=m_vertices.end(); ++it)
    {
        it->second.m_marque=false;
    }

    for (int i=0; i<m_ordre; i++)
    {
        c2.push_back(0);
    }
    std::vector<std::vector<int> > trans;
    std::vector<int> matrice_temp1;
    for (int i=0; i<m_ordre; i++)
    {
        for (int j=0; j<m_ordre; j++)
        {
            matrice_temp1.push_back(0);
        }
        trans.push_back(matrice_temp1);
    }



    for (int a=0; a<m_ordre; a++)
    {
        for (int b=0; b<m_ordre; b++)
        {
            trans[a][b]=m_matrice_adj[b][a];
        }
    }


///Rendre le sommet s connexe
    c2[s]=1;
    ajoute=1;
    while (ajoute==1)
    {
        ajoute=0; /// à chaque tour, recherche d'une nouvelle composante connexe à ajouter
        ///Pour tous les sommets x non marques et connectes en partant de s

        for (x=0; x<m_ordre; x++)
        {

            itx= m_vertices.find(x);

            if ( itx->second.m_marque==false && c2[itx->first]==1)
            {
                itx->second.m_marque=true;
                for (y=0; y<m_ordre; y++)
                {
                    ity=m_vertices.find(y);
                    if (trans[x][y]!=0 && ity->second.m_marque==false )
                    {
                        c2[y]=1;
                        ajoute=1; ///Nouvelle composante connexe ajoutee
                    }
                }

            }
        }

    }

///C vecteur qui dit si sommet s fortement connexe avec le sommet indice i

    for (int i=0; i<m_ordre; i++)
    {
        c.push_back(0);
    }
///Composante fortement connexe c= intersection de c1 et c2
    for (x=0; x<m_ordre; x++)
    {

        if (c1[x]==1 &&c2[x]==1)
        {
            c[x]=1;

        }

        else
            c[x]=0;


    }


    return c;

}

void Graph::compo_fort_connexes( std::vector <std::vector <int> > *mes_compo)
{
    std::map<int,Vertex>::iterator it_color;
    if(m_interface->m_option_6.clicked())
    {
        std::cout << "allo";
        ///Fonction qui retourne un tableau dynamique de toutes les composantes fortement connexes du graphe
        ///Paramètres
        ///Adjacence : matrice d'adjacence noeud-noeud du graphe
        ///ordre : nombre de sommets

        ///Variables locales
        std::vector <std::vector <int> > tabc;///Tableau dynamique des composantes fortement connexes à retourner
        std::vector <int> temporaire;
        int x, y; ///Numero de sommets intermédiaires comme indices des tableaux

        for (int i=0; i<m_ordre; i++)
        {
            for (int j=0; j<m_ordre; j++)
            {
                temporaire.push_back(0);
            }

        }


        ///Initialisation à false des marqueurs de sommets
        for (std::map<int, Vertex>::iterator it = m_vertices.begin(); it!=m_vertices.end(); ++it)
        {
            it->second.m_marque=false;

        }


        ///Pour tous les sommets x non marques
        ///Rechercher la composante fortement connexe de x
        ///Marquer chaque sommet x et marquer les sommets y connectés à x et non marques
        std::map<int,Vertex>::iterator itx;
        std::map<int,Vertex>::iterator ity;

///On parcourt une première fois tous nos sommets
        for (x=0; x<m_ordre; x++)
        {
            itx= m_vertices.find(x);


            ///On ajoute dans tab à l'indice de ce sommet ses composantes fortement connexes
            tabc.push_back( une_compo_fortement_connexes(x));

            ///On le marque
            itx->second.m_marque=true;
            ///On parcourt une seconde fois les sommets
            for (y=0; y<m_ordre; y++)
            {

                ity= m_vertices.find(y);
                ///Si x et y sont fortement connexes et que y n'est pas marque alors on marque y
                if (tabc[x][y]==1 && ity->second.m_marque==false)
                    ity->second.m_marque=true;
            }

        }



///Reconnaissance des composantes fortement connexes
///Initialisation d'un booléen
        bool different=false;

        int cpt=0;
        int cpt_2=0;
///Ma_compo contiendra une composante fortement connexes une a une
        std::vector <int> ma_compo;
///Mes_compo contiendra les composante fortement connexes


        for (unsigned int x=0; x<tabc.size(); x++)
        {
            if (tabc[0][x]==1)
                cpt_2++;
        }
        for (unsigned int x=0; x<tabc.size(); x++)
        {
            if( cpt_2>1)
                ma_compo.push_back(tabc[0][x]);
            else
            {
                for (int j=0; j<m_ordre; j++)
                {
                    ma_compo.push_back(0);
                }

            }

        }

        mes_compo->push_back(ma_compo);

        ma_compo.clear();


///Parcourons le tableau detecteur de forte connexite les lignes
        for (unsigned int j=1; j<m_ordre; j++)
        {

            ///Les colonnes
//        std::cout<<"Ma compo : ";
            for (unsigned int i=0; i<tabc.size(); i++)
            {

///On range une ligne de ce tableau dans notre vecteur ma compo
                ma_compo.push_back(tabc[j][i]);


            }



///Si on a deja range au moins une ligne dans notre tableau

            ///On parcourt le tableau qui regroupe toutes les composantes à la ligne et verifie
            ///Que la ligne que l'on veut ajouter est differente de celle qui precede



///Boucle pour verifier que deux lignes sont differentes

            for (unsigned int a=0; a<mes_compo->size(); a++)
            {



                unsigned int z=0;
                for (z=0; z<mes_compo->size(); z++)
                {


                    if(ma_compo[a]!=(*mes_compo)[a][z])
                    {
                        ///Si c'est bien different on rajoutera cette composante dans notre
                        ///Vecteur de forte connexite

                        cpt++;
                    }
                }
                if (cpt==z*m_ordre)
                {
                    different=true;
                }

            }


            if(different==true)
            {
                mes_compo->push_back(ma_compo);


            }


            ma_compo.clear();


        }

        ///Affichage composantes connexes

        if (mes_compo->size()==1 && cpt_2<2)
        {
            std::cout<<"Pas de composante fortement connexe dans ce graph"<<std::endl;


        }
        else
        {
            for (unsigned int i=0; i<mes_compo->size(); i++)
            {

                std::cout<<"La composante fortement connexe numero "<<i+1<<" est compose de : "<<std::endl;
                for (unsigned int j=0; j<m_ordre; j++)
                {
                    it_color= m_vertices.find(j);
                    if ((*mes_compo)[i][j]==1)
                    {
                        it_color->second.m_interface->m_top_box.set_bg_color(makecol(255,0,0));
                        std::cout <<" Sommet "<<j;
                    }
                }
                std::cout<<std::endl;
            }
        }
    }
    if(key[KEY_F])
    {
        std::cout << "AAAAAAAA";
        for (unsigned int i=0; i<mes_compo->size(); i++)
            {

                std::cout<<"La composante fortement connexe numero "<<i+1<<" est compose de : "<<std::endl;
                for (unsigned int j=0; j<m_ordre; j++)
                {
                    it_color= m_vertices.find(j);
                    if ((*mes_compo)[i][j]==1)
                    {
                        it_color->second.m_interface->m_top_box.set_bg_color(makecol(255,255,255));
                        std::cout <<" Sommet "<<j;
                    }
                }
                std::cout<<std::endl;
            }
    }
}

Graph Graph :: graph_reduit(std::vector <std::vector <int> > *mes_compo,Graph g)
{
    ///On cree un deuxième graphe qui sera le graphe reduit (ne contient que les composantes fortements connexe de g)
    Graph g_reduit;
    int nb_sommet=0;
///Declaration de nos variables
///Un vecteur d'iterateur de sommet et un iterateur de sommet
    std::vector <std::map<int, Vertex>::iterator> mes_iterators;
    std::map<int, Vertex>::iterator it;

///On parcourt mes compo
    for (int unsigned i=0; i<mes_compo->size(); i++)
    {
        for (int unsigned j=0; j<m_ordre; j++ )
        {

            if ((*mes_compo)[i][j]==1)
            {
///Si la case est egale à 1 alors le nb de sommet dans mon graph reduit est incrémenté
                nb_sommet++;
///On pushback un iterateur de ce sommet dans notre vecteur d'iterateur
                it= m_vertices.find(j);
                mes_iterators.push_back(it);


            }

        }

    }
///On ouvre le fichier qui contient les sommets du graph reduit en ecriture
    std::ofstream fichier1("chaine/graph_red_s1.txt", std::ios::in);
///Si le fichier est ouvert
    if(fichier1)
    {
        ///On y ecrit en premier le nombre de sommet c'est a dire l'ordre de notre graph reduit
        fichier1 << nb_sommet << std::endl;
///On parcourt notre vecteur d'iterateur pour inscire pour chaque sommet du graphe ses données
        for(unsigned int a=0; a<mes_iterators.size(); a++)
        {
            fichier1 << mes_iterators[a]->first << " ";
            std::cout<<mes_iterators[a]->first << " ";
            fichier1 << mes_iterators[a]->second.m_value << " ";

            if(mes_iterators[a]->second.m_interface->m_top_box.get_posx()<=0)
            {
                mes_iterators[a]->second.m_interface->m_top_box.set_posx(0);
                fichier1 << mes_iterators[a]->second.m_interface->m_top_box.get_posx() << " ";
            }
            else
                fichier1 << mes_iterators[a]->second.m_interface->m_top_box.get_posx() << " ";

            if(mes_iterators[a]->second.m_interface->m_top_box.get_posy()<=0)
            {
                mes_iterators[a]->second.m_interface->m_top_box.set_posy(0);
                fichier1 << mes_iterators[a]->second.m_interface->m_top_box.get_posy() << " ";
            }
            else
                fichier1 << mes_iterators[a]->second.m_interface->m_top_box.get_posy() << " ";

            fichier1 << mes_iterators[a]->second.m_interface->m_img.m_pic_name << std::endl;
        }
        fichier1.close();
        ///On ferme le fichier
    }


///Récupérer les données dans le fichier
    Sommet s;
    Sommet s_suiv;


    std::ifstream fichier("chaine/graph_red_s1.txt");

///Je souhaite recuperer les données afin de les afficher
///On ouvre le meme fichier en lecture

///Si le fichier est ouvert
    if(fichier)
    {
///On recupere l'ordre du graphe
        fichier >> g_reduit.m_ordre;

        g_reduit.m_ordre=nb_sommet;

///Puis les données des différents sommets
        fichier >> s.m_num;
        fichier >> s.m_taille_pop;
        fichier >> s.m_coordx;
        fichier >> s.m_coordy;
        fichier >> s.m_nom_img;
        g_reduit.m_vect_sommets.push_back(s);
        for(int i=1; i<g_reduit.m_ordre; ++i)
        {

            fichier >> s_suiv.m_num;

            if(s_suiv.m_num != s.m_num)
            {
                s.m_num=s_suiv.m_num;
                fichier >> s.m_taille_pop;
                fichier >> s.m_coordx;
                fichier >> s.m_coordy;
                fichier >> s.m_nom_img;

///On range  chaque sommet un par un dans le vecteur de sommet du graphe reduit
                g_reduit.m_vect_sommets.push_back(s);


            }


        }
        fichier.close();
///On ferme le fichier



    }


///Partie Aretes

///Initialisation du compteur d'aretes à 0
    int nb_ar=0;
///Declaration des varaibles
///Iterateur d'aretes, de sommets, et un vecteur d'iterateurs d'aretes
    std::map<int, Edge>::iterator itedge;
    std::map<int, Vertex>::iterator it_s;
    std::vector <std::map<int, Edge>::iterator> mes_iterators_ar;


///On parcourt notre vecteur de sommet du graphe reduit
    for (int i=0; i<g_reduit.m_vect_sommets.size(); i++)
    {

///On parcourt notre vecteur d'aretes du graph de depart

        for (std::map<int, Edge>::iterator it_ar_dep=g.m_edges.begin(); it_ar_dep!=g.m_edges.end(); it_ar_dep++)
        {
            ///On regarde si l'arete du graph de depart part d'un des sommets du graphe reduit
            if (it_ar_dep->second.m_from == i)
            {
                ///si oui on la range dans notre vecteur d'iterateurs
                mes_iterators_ar.push_back(it_ar_dep);
            }
            ///Si non on passe a la suivante
            ///On fait ca pour toutes les aretes du graph de depart
        }

///On reitere l'operation pour tous les sommets du graphe reduit
    }

///On obtient donc un vecteur contenant les iterateurs des aretes qui partent de
///sommets presents dans le graphe reduit

///on refait la meme chose sauf que cette fois si on prend que les aretes du vecteur

///On parcourt notre vecteur de sommet du graphe reduit
    for (int i=0; i<g_reduit.m_vect_sommets.size(); i++)
    {

///On parcourt notre vecteur d'iterateurs d'aretes

        for (int j=0; j<mes_iterators_ar.size(); j++)
        {
            ///On regarde si l'arete du graph de depart arrive a l'un des sommets du graphe reduit
            if (mes_iterators_ar[j]->second.m_to ==i)
            {
                ///si oui on la range dans notre vecteur d'aretes du graphe reduit
                g_reduit.m_vect_aretes.push_back(mes_iterators_ar[j]->second);
            }
            ///Si non on passe a la suivante
            ///On fait ca pour toutes les aretes du vecteur d'iterateurs
        }

///On reitere l'operation pour tous les sommets du graphe reduit
    }

    std::cout<<"Nombre d'aretes = " <<g_reduit.m_vect_aretes.size()<<std::endl;

///On ouvre en ecriture le fichier de sauvegarde des aretes du graphe reduit
    std::ofstream fichier_ar("chaine/graph_red_a1.txt", std::ios::in);
///Si le fichier est bien ouvert
    if(fichier_ar)
    {
        std::cout<<"fichier ouvert";
///On ecrit en premier le nombre d'aretes du graphe reduit
        fichier_ar<<g_reduit.m_vect_aretes.size()<<std::endl;
///On parcourt le vecteur d'aretes du graphe reduit

        for (int k=0; k<g_reduit.m_vect_aretes.size(); k++)

        {
            ///On ecrit pour chaque arete sauvegardée ses informations dans le fichier
            fichier_ar <<k<<" ";
            fichier_ar << g_reduit.m_vect_aretes[k].m_from << " ";
            fichier_ar << g_reduit.m_vect_aretes[k].m_to << " ";
            fichier_ar << g_reduit.m_vect_aretes[k].m_weight << std::endl;
        }
///On ferme le fichier
        fichier_ar.close();
    }
///On retourne le graphe reduit dans le main
    return g_reduit;
}
