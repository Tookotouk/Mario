#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include "Monde.hpp"
#include "Personnage.hpp"
#include "Monstre.hpp"
#include "main.hpp"

sf::ContextSettings settings(0,0,8,1,1);
sf::Texture sol,mur,ciel,textureMario,textureGoumba;
sf::RenderWindow window(sf::VideoMode(1920,1080),"Fenetre test",sf::Style::Fullscreen,settings);
sf::Sprite spriteMario,Goumba,HUDGoumba,MarioHUD;
std::vector<Monstre> mob;
Personnage joueur;
Monde un;
int i = 0;

int main(int argc, char const *argv[])
{
	bool Monde2Charger = false;
	sf::Music theme;
	theme.openFromFile("Sounds/main_theme_sped_up.ogg");
	theme.play();
	theme.setLoop(true);
	sf::Font fontMario;
	if(!fontMario.loadFromFile("police Mario.ttf")){
		return 1;
	}
	sf::Text nbMobRestant("test",fontMario,20);
	sf::Text nbVieRestant("test",fontMario,20);
	nbVieRestant.setColor(sf::Color::White);
	nbMobRestant.setColor(sf::Color::White);
	sf::View camPrincipal(sf::Vector2f(13*16, 8*16), sf::Vector2f(1.7*16*16, 1.7*16*9));
	window.setFramerateLimit(40);
	initTexture();
	HUDGoumba.setTexture(textureGoumba);
	HUDGoumba.setTextureRect(sf::IntRect(0,0,16,16));
	MarioHUD.setTexture(textureMario);
	MarioHUD.setTextureRect(sf::IntRect(0,0,16,16));
	joueur = Personnage(spriteMario);
	loadMonde1();
	sf::Text texte("GAME OVER\n\n Press Esc to quit", fontMario, 40);
	joueur.setSon();
	while(window.isOpen()){
		sf::Event event;
		while(window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
		updateCam(&camPrincipal);
		window.setView(camPrincipal);
		un.frapperBlocToFalse((int)((joueur.getSprite().getPosition().x))/16,(int)(((joueur.getSprite().getPosition().y)/16)-2));
		HUDGoumba.setPosition(sf::Vector2f(joueur.getSprite().getPosition().x-32,16));
		MarioHUD.setPosition(sf::Vector2f(joueur.getSprite().getPosition().x+32,16));
		nbMobRestant.setPosition(sf::Vector2f(joueur.getSprite().getPosition().x,16));
		nbVieRestant.setPosition(sf::Vector2f(joueur.getSprite().getPosition().x+64,16));
		nbMobRestant.setString("x" + std::to_string(mob.size()));
		nbVieRestant.setString("x"+std::to_string(joueur.getVieRestant()));
		if (joueur.getStatus())
		{
			mouvementPerso();
		}else{
			if (Monde2Charger == true)
			{
				if (joueur.getVieRestant() > 0)
				{
					joueur.decrementeVie();
					afficherVieRestant(nbVieRestant);
					loadMonde2();
					joueur.setStatus(true);
				}
				else{
					gameOver(texte);
					while(window.isOpen()){
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
						{
							window.close();
						}
					}
				}
			}
			else{
				if (joueur.getVieRestant()>0 )
				{
					joueur.decrementeVie();
					afficherVieRestant(nbVieRestant);
					loadMonde1();
					joueur.setStatus(true);
				}
				else{
					gameOver(texte);
					while(window.isOpen()){
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
						{
							window.close();
						}
					}
				}
			}
		}
		mobProg();
		affichage(nbMobRestant,nbVieRestant);
		if (mob.size() == 0)
		{
			if (Monde2Charger == true)
			{
				win(texte);
				while(window.isOpen()){
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
					{
						window.close();
					}
				}
			}
			loadMonde2();
			Monde2Charger = true;
		}
	}
	return 0;
}
void afficherVieRestant(sf::Text t){
	window.clear();
	window.draw(t);
	window.draw(MarioHUD);
	window.display();
	sf::sleep(sf::seconds(1));
	t.setString("x"+std::to_string(joueur.getVieRestant()));
	window.clear();
	window.draw(t);
	window.draw(MarioHUD);
	window.display();
	sf::sleep(sf::seconds(1));
}
void win(sf::Text t){
	t.setString("YOU WIN \n\nPress ESC to quit");
	t.setColor(sf::Color::White);
	window.clear();
	t.setPosition(sf::Vector2f(joueur.getSprite().getPosition().x-75,100));
	window.draw(t);
	window.display();
}
void gameOver(sf::Text t){
	t.setString("GAME OVER\n\nPress ESC to quit");
	t.setColor(sf::Color::White);
	window.clear();
	t.setPosition(sf::Vector2f(joueur.getSprite().getPosition().x-75,100));
	window.draw(t);
	window.display();
	//std::cout << "Game Over" << std::endl;
}
void loadMonde1(){
	window.clear();
	window.display();
	un.clearVector();
	mob.clear();
	un.construireLevel(lireFichier("niveau1.txt"),&sol,&mur,&ciel);
	spawnMob(lireFichier("niveau1.txt"));
	initPerso(&joueur);
}
void loadMonde2(){
	window.clear();
	window.display();
	un.clearVector();
	mob.clear();
	un.construireLevel(lireFichier("niveau2.txt"),&sol,&mur,&ciel);
	spawnMob(lireFichier("niveau2.txt"));
	initPerso(&joueur);
}
void mobProg(){
	for (int i = 0; i < mob.size(); ++i)
	{
		if (mob[i].getStatus())
		{
			mouvementMob(&mob[i]);
		}else{
			if (mob[i].getWaitDespawn() >0)
			{
				if (mob[i].getWaitDespawn() < 64)
				{
					mob[i].addWaitDespawn();
				}else{
					mob.erase(mob.begin()+i);
			}
		}
		}
	}
}
void updateCam(sf::View* cam){
	cam->setCenter(sf::Vector2f(joueur.getSprite().getPosition().x,cam->getCenter().y));
}
void spawnMob(std::vector<std::string> l){
	for(int i = 0; i<l.size();i++){
		for (int j = 0; j < l[i].length(); ++j){
			if (l[i][j] == 'G')
			{
				mob.push_back(Monstre(Goumba,sf::Vector2f(j*16,i*16)));
			}
		}
	}
	for (int i = 0; i < mob.size(); ++i)
	{
		mob[i].setSon();
	}
}	
void mouvementMob(Monstre* mob){
	mob->tuer(&joueur,un);
	mob->verifColl(un);
	mob->bouger();
}
void mouvementPerso(){
	joueur.direction();
	joueur.verifCollision(&un);
	joueur.animat();
	joueur.bouger();
	joueur.updateMouvementPrec();
}
void affichage(sf::Text nbMob,sf::Text nbVie){
	window.clear();
	un.afficherMonde(&window);
	for (int i = 0; i < mob.size(); ++i)
	{
		mob[i].afficher(&window);
	}
	if (joueur.getStatus() != false)
	{
		joueur.afficherPersonnage(&window);
	}
	window.draw(nbMob);
	window.draw(nbVie);
	window.draw(HUDGoumba);
	window.draw(MarioHUD);
	window.display();
}
void initTexture(){
	textureGoumba.loadFromFile("texture/GoumbaSprite.png");
	Goumba.setTexture(textureGoumba);
	Goumba.setTextureRect(sf::IntRect(0,0,16,16));
	textureMario.loadFromFile("texture/MarioSprite.png");
	spriteMario.setTexture(textureMario);
	spriteMario.setTextureRect(sf::IntRect(0,0,16,32));
	mur.loadFromFile("texture/mur.jpg");
	ciel.loadFromFile("texture/ciel.jpg");
	sol.loadFromFile("texture/sol.jpg");
}
std::vector<std::string> lireFichier(std::string nomFichier){
	std::ifstream fichier(nomFichier.c_str(), std::ios::in);  // on ouvre en lecture
	std::vector<std::string> s;
	if(fichier)  // si l'ouverture a fonctionné
	{
		std::string ligne;
        while(getline(fichier, ligne))  // tant que l'on peut mettre la ligne dans "contenu"
        {
                s.push_back(ligne);
        }
	}
	fichier.close();
	return s;
}
void initPerso(Personnage* perso){
	perso->setPos(sf::Vector2f(16*2,16*13-0.1));
}