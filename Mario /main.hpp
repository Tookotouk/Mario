void affichage(sf::Text nbMob,sf::Text nbVie);
void updateCam(sf::View* cam);
void spawnMob(std::vector<std::string> l);
void mouvementPerso();
void initTexture();
std::vector<std::string> lireFichier(std::string nomFichier);
void initPerso(Personnage* perso);
void initMob();
void mouvementMob(Monstre* mob);
void mobProg();
void loadMonde1();
void loadMonde2();
void gameOver(sf::Text t);
void win(sf::Text t);
void afficherVieRestant(sf::Text t);