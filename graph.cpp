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


/// Gestion du Edge avant l'appel à l'interface
void Edge::pre_update()
{
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
    m_top_box.set_dim(1000,740);
    m_top_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);

    m_top_box.add_child(m_tool_box);
    m_tool_box.set_dim(80,720);
    m_tool_box.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);
    m_tool_box.set_bg_color(BLANCBLEU);

    m_top_box.add_child(m_main_box);
    m_main_box.set_dim(908,720);
    m_main_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);
    m_main_box.set_bg_color(BLANCJAUNE);
}

void Graph::ajouter_sommet()
{
    bool bibli=false;
    int choix=0;
    Sommet s;

    if((mouse_b&1) && ((mouse_x>=500 && mouse_x<=800) && (mouse_y>=25 && mouse_y<=49)))
    {
        bibli=true;
    }

    if(bibli)
    {
        std::cout << 1;
        choix=grman::biblio();
        std::cout << std::endl << "AAA" << choix << "bb";

        if(choix==1)
        {
            s.m_coordx=mouse_x;
            s.m_coordy=mouse_y;
            s.m_nom_img="0.jpg";
            s.m_num=m_ordre;

            m_vect_sommets.push_back(s);
            m_ordre+=1;

            add_interfaced_vertex(m_vect_sommets[m_ordre-1].m_num, m_vect_sommets[m_ordre-1].m_taille_pop, m_vect_sommets[m_ordre-1].m_coordx, m_vect_sommets[m_ordre-1].m_coordy, m_vect_sommets[m_ordre-1].m_nom_img);
        }
        else if(choix==2)
        {
            s.m_coordx=mouse_x;
            s.m_coordy=mouse_y;
            s.m_nom_img="1.jpg";
            s.m_num=m_ordre;

            m_vect_sommets.push_back(s);
            m_ordre+=1;

            add_interfaced_vertex(m_vect_sommets[m_ordre-1].m_num, m_vect_sommets[m_ordre-1].m_taille_pop, m_vect_sommets[m_ordre-1].m_coordx, m_vect_sommets[m_ordre-1].m_coordy, m_vect_sommets[m_ordre-1].m_nom_img);
        }
        else if(choix==3)
        {
            s.m_coordx=mouse_x;
            s.m_coordy=mouse_y;
            s.m_nom_img="2.jpg";
            s.m_num=m_ordre;

            m_vect_sommets.push_back(s);
            m_ordre+=1;

            add_interfaced_vertex(m_vect_sommets[m_ordre-1].m_num, m_vect_sommets[m_ordre-1].m_taille_pop, m_vect_sommets[m_ordre-1].m_coordx, m_vect_sommets[m_ordre-1].m_coordy, m_vect_sommets[m_ordre-1].m_nom_img);
        }
        else if(choix==4)
        {
            s.m_coordx=mouse_x;
            s.m_coordy=mouse_y;
            s.m_nom_img="3.jpg";
            s.m_num=m_ordre;

            m_vect_sommets.push_back(s);
            m_ordre+=1;

            add_interfaced_vertex(m_vect_sommets[m_ordre-1].m_num, m_vect_sommets[m_ordre-1].m_taille_pop, m_vect_sommets[m_ordre-1].m_coordx, m_vect_sommets[m_ordre-1].m_coordy, m_vect_sommets[m_ordre-1].m_nom_img);
        }

        std::cout << m_vect_sommets[m_ordre-1].m_num << " " << m_vect_sommets[m_ordre-1].m_coordx << " " << m_vect_sommets[m_ordre-1].m_coordy << " ajout\n";
    }
}

///Enregistrer dans un fichier
void Graph::enregistrer_donnees_som(std::string nom_fic_som)
{
    std::ofstream fichier(nom_fic_som, std::ios::in);

    if(fichier)
    {
        fichier << m_ordre << std::endl;

        for(std::map<int, Vertex>::iterator it=m_vertices.begin(); it!=m_vertices.end(); it++)
        {
            fichier << it->first << " ";
            fichier << it->second.m_value << " ";
            fichier << it->second.m_interface->m_top_box.get_posx() << " ";
            fichier << it->second.m_interface->m_top_box.get_posy() << " ";
            fichier << it->second.m_interface->m_img.m_pic_name << std::endl;
        }
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

    if(fichier)
    {
        fichier << m_nb_aretes << std::endl;

        for(std::map<int, Edge>::iterator it=m_edges.begin(); it!=m_edges.end(); it++)
        {
            fichier << it->first << " ";
            fichier << it->second.m_from << " ";
            fichier << it->second.m_to << " ";
            fichier << it->second.m_weight << std::endl;
        }
        fichier.close();
    }
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
void Graph::update()
{
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
    m_edges[idx] = Edge(weight, ei);
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
    if((mouse_b&1) && ((mouse_x>=500 && mouse_x<=800) && (mouse_y>=49 && mouse_y<=66)) && !(*finn))
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
        e.m_num_arete=m_nb_aretes;
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
    }
}


///Fonction pour supprimer une arete
void Graph::supp_arete(bool *fin_inna1, int *cpt_inna, int *s)
{

    Edge arete_supp;
    std::map<int,Edge>::iterator it;
    std::map<int,Edge>::iterator it1;
    bool etape_suiv=false;
    bool *p_etape_suiv;
    p_etape_suiv= &etape_suiv;


    bool etape_suiv1=false;
    bool *p_etape_suiv1;
    p_etape_suiv1=&etape_suiv1;
    bool commenceSnd=false;

    int s2;

    bool click=false;
    int v=0;


    ///Si on clique dans le menu sur supprimer une arete
    if(mouse_b&1 && mouse_x>=500 && mouse_x<=800 && mouse_y>=70 && mouse_y<=100 && !(*fin_inna1))
    {
        *fin_inna1=true;
        *cpt_inna=1;
        std::cout<<"Cliquer sur le sommet d'ou part l'arete"<<std::endl;
    }

    else if( mouse_b&1 && mouse_x>=0 && mouse_x<=800 && mouse_y>=0 && mouse_y<=600 && (*fin_inna1) && (*cpt_inna>=50))
    {
        std::cout<<"on clique gauche"<<std::endl;
        int  mousepos_x=mouse_x;
        int  mousepos_y=mouse_y;

        for (std::map<int, Vertex>::iterator it = m_vertices.begin(); it!=m_vertices.end(); ++it)
        {
            std::cout<<"On regarde si il y a un sommet correspondant"<<std::endl;

            if ( mousepos_y >=  it->second.m_interface->m_top_box.get_posy() && mousepos_y <=it->second.m_interface->m_top_box.get_posy()  + 100 &&mousepos_x>=it->second.m_interface->m_top_box.get_posx() -80 && mousepos_x <= it->second.m_interface->m_top_box.get_posx()  +20)
            {
                *s=it->first;
                std::cout<<"on a trouve s1"<<*s<<std::endl;

            }
            *p_etape_suiv=true;
        }

        std::cout<<"Tres bien, veuillez maintenant cliquer sur le sommet d'arrivee de l'arete"<<std::endl;

        while (!commenceSnd && (*p_etape_suiv))
        {
            if(mouse_b&2 )
            {
                commenceSnd=true;



                for ( std::map<int, Vertex>::iterator it = m_vertices.begin(); it!=m_vertices.end(); ++it )
                {

                    if ( mousepos_y >=  it->second.m_interface->m_top_box.get_posy() && mousepos_y <=it->second.m_interface->m_top_box.get_posy()  + 100 &&mousepos_x>=it->second.m_interface->m_top_box.get_posx() -80 && mousepos_x <= it->second.m_interface->m_top_box.get_posx()  +20)
                    {

                        s2=it->first;
                        std::cout<<"on a trouve s2"<<s2<<std::endl;
                        *p_etape_suiv1=true;
                    }
                }
            }
        }

        if(*p_etape_suiv1==true && *p_etape_suiv==true)
        {


            for (std::map<int, Edge> :: iterator it=m_edges.begin(); it!=m_edges.end(); ++it)
            {

                if( (it->second.m_from==*s || it->second.m_to==*s)  && ( it->second.m_from==s2 || it->second.m_to==s2) )
                {

                    ///On delete l'arete


                    m_edges.erase(it->first);
                    m_nb_aretes -=1;
                    arete_supp=it->second;
                    std::cout <<"Arete supprime"<<std::endl;
                }

            }


         ar_incidentes(&click, &v, s, &s2);


            for (std::vector<int> :: iterator it=m_vertices[*s].m_in.begin(); it!=m_vertices[*s].m_in.end(); ++it)
            {
              std::cout<<"essai 1"<<std::endl;
                if (arete_supp.m_from==*it || arete_supp.m_to==*it)
                {
                    std::cout<<"size in " <<m_vertices[*s].m_in.size();
                    std::cout<<"size in " <<m_vertices[*s].m_out.size();
                    std::cout<<"essai 2"<<std::endl;
                    m_vertices[*s].m_in.erase(it);
                    std::cout<<"essai 3"<<std::endl;
                }

            }
            for (std::vector<int> :: iterator it=m_vertices[*s].m_out.begin(); it!=m_vertices[*s].m_out.end(); ++it)
            {
                if (arete_supp.m_from==*it || arete_supp.m_to==*it)
                {
                    m_vertices[*s].m_out.erase(it);
                }
            }

            for (std::vector<int> :: iterator it=m_vertices[s2].m_in.begin(); it!=m_vertices[s2].m_in.end(); ++it)
            {
                if (arete_supp.m_from==*it || arete_supp.m_to==*it)
                {
                    m_vertices[s2].m_in.erase(it);
                }

            }
            for (std::vector<int> :: iterator it=m_vertices[s2].m_out.begin(); it!=m_vertices[s2].m_out.end(); ++it)
            {
                if (arete_supp.m_from==*it || arete_supp.m_to==*it)
                {
                    m_vertices[s2].m_out.erase(it);
                }
            }


        }
        *cpt_inna=0;
    *fin_inna1=false;

    }



}



void Graph::supprimer_sommet(bool *fin1, int *cptt)
{
    /// si il clique sur ajouter un sommet
    if((mouse_b&1) && ((mouse_x>=500 && mouse_x<=800) && (mouse_y>=70 && mouse_y<=100)) && !(*fin1))
    {
        *fin1=true;
        *cptt=1;
        std::cout << "Choisissez le sommet a supprimer." <<std::endl;
    }

    /// si il clique GAUCHE et dans l'ecran sur un sommet
    else if((mouse_b&1) && ((mouse_x>=0 && mouse_x<=800) && (mouse_y>=0 && mouse_y<=600)) && *fin1 && *cptt>=50)
    {
        ///on recupère les coordonnées de la ou on a clique
        double mouseposx = mouse_x;
        double mouseposy = mouse_y;

        for (std::map<int, Vertex>::iterator it=m_vertices.begin(); it!=m_vertices.end(); it++)
        {
            if (mouseposy >=it->second.m_interface->m_top_box.get_posy() && mouseposy <=it->second.m_interface->m_top_box.get_posy() + 100 && mouseposx>=it->second.m_interface->m_top_box.get_posx()-80 && mouseposx <= it->second.m_interface->m_top_box.get_posx() +20 )
            {
                /// si il clique sur un sommet
                m_interface->m_main_box.remove_child(m_vertices[it->first].m_interface->m_top_box);
                m_vertices.erase(it);
                m_ordre-=1;
                *fin1=false;
            }
        }
    }
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


void Graph::test_remove_edge( int eidx)
{
/// référence vers le Edge à enlever
Edge &remed=m_edges.at(eidx);
std::cout << "Removing edge " << eidx << " " << remed.m_from << "->" << remed.m_to << " " << remed.m_weight << std::endl;
/// Tester la cohérence : nombre d'arc entrants et sortants des sommets 1 et 2
std::cout << m_vertices[remed.m_from].m_in.size() << " " << m_vertices[remed.m_from].m_out.size() << std::endl;
std::cout << m_vertices[remed.m_to].m_in.size() << " " << m_vertices[remed.m_to].m_out.size() << std::endl;
std::cout << m_edges.size() << std::endl;
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
}
/// Il reste encore à virer l'arc supprimé de la liste des entrants et sortants des 2 sommets to et from !
/// References sur les listes de edges des sommets from et to
std::vector<int> &vefrom = m_vertices[remed.m_from].m_out;
std::vector<int> &veto = m_vertices[remed.m_to].m_in;
vefrom.erase( std::remove( vefrom.begin(), vefrom.end(), eidx ), vefrom.end() );
veto.erase( std::remove( veto.begin(), veto.end(), eidx ), veto.end() );
/// Le Edge ne nécessite pas non plus de delete car on n'a pas fait de new (sémantique par valeur)
/// Il suffit donc de supprimer l'entrée de la map pour supprimer à la fois l'Edge et le EdgeInterface
/// mais malheureusement ceci n'enlevait pas automatiquement l'interface top_edge en tant que child de main_box !
m_edges.erase( eidx );
/// Tester la cohérence : nombre d'arc entrants et sortants des sommets 1 et 2
std::cout << m_vertices[remed.m_from].m_in.size() << " " << m_vertices[remed.m_from].m_out.size() << std::endl;
std::cout << m_vertices[remed.m_to].m_in.size() << " " << m_vertices[remed.m_to].m_out.size() << std::endl;
std::cout << m_edges.size() << std::endl;
}
