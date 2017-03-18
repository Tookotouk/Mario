#ifndef DEF_PERSONNAGE
#define DEF_PERSONNAGE 
#include <iostream>
#include "Mouvement.hpp"
class Personnage
{
public:
enum Etat{
	droite,//0
	droiteHaut,//1
	gauche,//2
	gaucheHaut,//3
	haut,//4
	bas,//5
	droiteBas,//6
	gaucheBas,//7
	none//8
};
private:
	int nombreVie;
	float vitesseDeplacement;
	float vitesseSaut;
	int saut;
	bool vivant;
	Etat directionMouvement;
	sf::Sprite mario;
	bool toucheSol;
	int animation;
	Etat mouvementPrec;
	sf::SoundBuffer sautBuffer;
	sf::Sound sautSon;
public:
	Personnage(){
		nombreVie = 5;
		directionMouvement = none;
		vivant = true;
		mario;
		toucheSol = true;
		saut = 0;
		animation = 0;
		vitesseDeplacement = 0;
		vitesseSaut = 0;
		mouvementPrec = none;
		sautSon;
	};
	Personnage(sf::Sprite m){
		nombreVie = 5;
		directionMouvement = none;
		vivant = true;
		mario = m;
		toucheSol = true;
		saut = 0;
		animation = 0;
		vitesseDeplacement = 4;
		vitesseSaut = 4;
		mouvementPrec = none;
		sautSon;
	};
	sf::Sprite getSprite(){
		return mario;
	}
	int getVieRestant(){
		return nombreVie;
	}
	void setSon(){
		sautBuffer.loadFromFile("Sounds/big_jump.ogg");
		sautSon.setBuffer(sautBuffer);
	}
	void updateMouvementPrec(){
		if (directionMouvement != none)
		{
			mouvementPrec = directionMouvement;
		}
	}
	int getState(){
		return directionMouvement;
	}
	void decrementeVie(){
		nombreVie--;
	}
	void animerADroite(){
		if (animation%8 == 0)
		{
			mario.setTextureRect(sf::IntRect(animation*2,0,16,32));
		}
		if (animation > 16)
		{
			animation = 0;
		}
		animation++;
	}
	void animerIdle(){
		if (mouvementPrec == gauche)
		{
			mario.setTextureRect(sf::IntRect(7*16,0,-16,32));
		}else{
			mario.setTextureRect(sf::IntRect(6*16,0,16,32));
		}
	}
	void animerAGauche(){
		if (animation%8 == 0)
		{
			mario.setTextureRect(sf::IntRect(animation*2,0,-16,32));
		}
		if (animation > 16)
		{
			animation = 0;
		}
		animation++;
	}
	void animeHaut(){
		if (mouvementPrec == gauche)
		{
			mario.setTextureRect(sf::IntRect(5*16,0,-16,32));
		}
		else{
			mario.setTextureRect(sf::IntRect(4*16,0,16,32));
		}
	}
	void animat(){
		switch(directionMouvement){
			case droite :
				if (mouvementPrec != droite)
				 	animation = 15;
				animerADroite();
				break;
			case gauche : 
				if (mouvementPrec != gauche)
				 	animation = 15;
				animerAGauche();
				break;
			case haut : 
				animeHaut();
				break;
			case droiteHaut :
				mouvementPrec = droite;
				animeHaut(); 	
				break;
			case gaucheHaut : 
				mouvementPrec = gauche;
				animeHaut();	
				break;
			case droiteBas : 
				if (mouvementPrec != droite)
				 	animation = 15;
				animerADroite();
				break;
			case gaucheBas:
				if (mouvementPrec != gauche)
				 	animation = 15;
				animerAGauche();
				break;
			case bas:
				break;
			case none:
				animerIdle();
				break;
		}
	}
	void setStatus(bool t){
		vivant = t;
	}
	void setTexture(sf::Sprite m){
		mario = m;
	}
	void afficherPersonnage(sf::RenderWindow *window){
		window->draw(mario);
	}
	void setPos(sf::Vector2f pos){
		mario.setPosition(pos);
	}
	void direction(){
		directionMouvement = Etat(saisitTouche());
	}
	bool verifierBlocADroite(sf::Vector2f pos,Monde m){
		return (m.getBloc(pos.x+1,pos.y).coll() or m.getBloc(pos.x+1,pos.y-1).coll() or m.getBloc(pos.x+1,pos.y-1.9).coll());
	}
	bool verifierBlocAGauche(sf::Vector2f pos,Monde m){
		return (m.getBloc(pos.x-0.1,pos.y).coll() or m.getBloc(pos.x-0.1,pos.y-1).coll() or m.getBloc(pos.x-0.1,pos.y-1.9).coll());
	}
	bool verifierBlocHaut(sf::Vector2f pos,Monde m){
		return (m.getBloc(pos.x,pos.y-2).coll() or m.getBloc(pos.x+0.9,pos.y-2).coll());
	}	
	bool verifierBlocBas(sf::Vector2f pos,Monde m){
		return (m.getBloc(pos.x,pos.y+0.1).coll() or m.getBloc(pos.x+0.9,pos.y+0.1).coll());
	}
	bool verifierBlocAngleDroiteBas(sf::Vector2f pos,Monde m){
		return (m.getBloc(pos.x+1,pos.y+0.1).coll());
	}
	bool verifierBlocAngleDroiteHaut(sf::Vector2f pos,Monde m){
		return (m.getBloc(pos.x+1,pos.y-2).coll());
	}
	bool verifierBlocAngleGaucheHaut(sf::Vector2f pos,Monde m){
		return (m.getBloc(pos.x-0.1,pos.y-2).coll());
	}
	bool verifierBlocAngleGaucheBas(sf::Vector2f pos,Monde m){
		return (m.getBloc(pos.x-0.1,pos.y+0.1).coll());
	}
	bool getStatus(){
		return vivant;
	}
	void bouger(){
		switch(directionMouvement){
			case droite : 
				mario.move(vitesseDeplacement,0);
				break;
			case gauche : 
				mario.move(-vitesseDeplacement,0);
				break;
			case haut : 
				if(saut==1)
					sautSon.play();
				mario.move(0,-vitesseSaut);
				directionMouvement = none;
				break;
			case droiteHaut : 
				if(saut==1)
					sautSon.play();	
				mario.move(vitesseDeplacement,-vitesseSaut);
				directionMouvement = none;
				break;
			case gaucheHaut : 
				if(saut==1)
					sautSon.play();	
				mario.move(-vitesseDeplacement,-vitesseSaut);
				directionMouvement = none;
				break;
			case droiteBas : 
				mario.move(vitesseDeplacement,vitesseSaut);
				directionMouvement = none;
				break;
			case gaucheBas:
				mario.move(-vitesseDeplacement,vitesseSaut);
				directionMouvement = none;
				break;
			case bas:
				mario.move(0,vitesseSaut);
				directionMouvement = none;
				break;
			case none:
				break;
		}
	}
	void tuerJoueur(){
		vivant = false;
	}
	void verifCollision(Monde *m){
		sf::Vector2f position(((mario.getPosition().x))/16,((mario.getPosition().y)/16)+2);//coordonnée du point bas gauche du perso
		if(position.y > m->getSize().y - 1)
			vivant = false;
		if (verifierBlocBas(position,*m))//si il y a un bloc en desous mario touche le sol
		{
			toucheSol = true;
			saut = 0;//sa hauteur de saut = 0
		}
		else if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)))//sinon si mario n'est pas en train de sauter alors il ne touche plus le sol
		{
			toucheSol = false;
		}
		switch(directionMouvement){
			case droiteHaut:
				if (verifierBlocHaut(position,*m))//si il y a un bloc au dessus de mario
				{
					m->frapperBloc((int)(position.x),(int)position.y-2.1);//alors mario tape le bloc au dessus de lui
					m->frapperBloc((int)(position.x+0.9),(int)position.y-2.1);
					toucheSol = false;//il ne touche plus le sol
					if (verifierBlocADroite(position,*m))//si en plus il y a un bloc a sa droite
					{
						if (toucheSol)//et qu'il touche le sol
						{
							directionMouvement = none;//ne rien faire
							break;
						}//fin de si il touche le sol
						directionMouvement = bas;//sinon aller vers le bas
						saut--;//réduire la hauteur de son saut
						break;
					}//fin de si il y a un bloc a droite
					directionMouvement = droiteBas;//sinon aller droite
					break;
				}//fin de si il y a un bloc en haut
				if (verifierBlocADroite(position,*m))//si il y a un bloc a droite
				{
					if (verifierBlocHaut(position,*m))//et si il y a un bloc au dessus
					{
						toucheSol = false;//mario ne touche plus le sol
						m->frapperBloc((int)(position.x),(int)position.y-2.1);//mario frappe le bloc au dessus de lui
						m->frapperBloc((int)(position.x+0.9),(int)position.y-2.1);
						if (toucheSol)//si il touche le sol
						{
							directionMouvement = none;//ne rien faire
							break;
						}//fin de si il touche le sol
						directionMouvement = bas;//sinon aller vers le bas
						saut--;//reduire la hauteur de son saut
						break;
					}//fin de si il y a un bloc en haut
					if (saut < (int)((5*16)/vitesseSaut))//si la hauteur de saut < 5 blocs
					{
						directionMouvement = haut;//aller vers le haut
						saut++;//augmenter la hauteur de son saut
						if (saut == (int)((5*16)/vitesseSaut))//si la hauteur de son saut est au max alors il ne touche plus le sol
						{
							toucheSol = false;
						}
					}//fin de si la hauteur du saut < 5 blocs
					if (!toucheSol)//si il ne touche plus le sol
					{
						directionMouvement = bas;//aller vers le bas
						saut--;//reduire la hauteur de son saut
					}//fin de sil il touche pas le sol
					break;
				}//fin de si il y a un bloc a droite
				if (!toucheSol)//si il touche pas le sol
				{
					if (verifierBlocADroite(position,*m))
					{
						directionMouvement = bas;//si il y a un bloc a droite aller vers le bas
					}
					else{
						directionMouvement = droiteBas;//sinon allers vers bas droite
					}
					saut--;
					break;
				}//fin de si il touche pas le sol
				if (saut <= (int)((5*16)/vitesseSaut) && toucheSol)//si la hauteur du saut < 5 blocs et si il touche le sol
				{
					saut++;//augmenter la hauteur du saut
					if (saut==(int)((5*16)/vitesseSaut))
					{
						toucheSol = false;//si la hauteur = hauteur max alors il touche plus le sol
					}
					break;
				}//fin de si la hauteur du saut < 5 blocs et si il touche le sol
				directionMouvement = none;//sinon ne pas bouger
				break;
			case gaucheHaut:
				if (verifierBlocHaut(position,*m))
				{
					m->frapperBloc((int)(position.x),(int)position.y-2.1);
					m->frapperBloc((int)(position.x+0.9),(int)position.y-2.1);
					toucheSol = false;
					if (verifierBlocAGauche(position,*m))
					{
						if (toucheSol)
						{
							directionMouvement = none;
							break;
						}
						directionMouvement = bas;
						saut--;
						break;
					}
					directionMouvement = gaucheBas;
					break;
				}
				if (verifierBlocAGauche(position,*m))
				{
					if (verifierBlocHaut(position,*m))
					{
						toucheSol = false;
						m->frapperBloc((int)(position.x),(int)position.y-2.1);
						m->frapperBloc((int)(position.x+0.9),(int)position.y-2.1);
						if (toucheSol)
						{
							directionMouvement = none;
							break;
						}
						directionMouvement = bas;
						saut--;
						break;
					}
					if (saut < (int)((5*16)/vitesseSaut))
					{
						directionMouvement = haut;
						saut++;
						if (saut == (int)((5*16)/vitesseSaut))
						{
							toucheSol = false;
						}
					}
					if (!toucheSol)
					{
						directionMouvement = bas;
						saut--;
					}
					break;
				}
				if (!toucheSol)
				{
					if (verifierBlocAGauche(position,*m))
					{
						directionMouvement = bas;
					}
					else{
						directionMouvement = gaucheBas;
					}
					saut--;
					break;
				}
				if (saut <= (int)((5*16)/vitesseSaut) && toucheSol)
				{
					saut++;
					if (saut==(int)((5*16)/vitesseSaut))
					{
						toucheSol = false;
					}
					break;
				}
				directionMouvement = none;
				break;
			case droite:
				if (verifierBlocADroite(position,*m))
				{
					if (toucheSol)
					{
						directionMouvement = none;
						break;
					}
					directionMouvement = bas;
					saut--;
					break;
				}
				if (toucheSol)
				{
					directionMouvement = droite;
					break;
				}
				directionMouvement = droiteBas;
				saut--;
				break;
			case gauche:
				if (verifierBlocAGauche(position,*m))
				{
					if (toucheSol)
					{
						directionMouvement = none;
						break;
					}
					directionMouvement = bas;
					saut--;
					break;
				}
				if (toucheSol)
				{
					directionMouvement = gauche;
					break;
				}
				directionMouvement = gaucheBas;
				saut--;
				break;
			case haut:
				if (verifierBlocHaut(position,*m))
				{
					toucheSol = false;
					m->frapperBloc((int)(position.x),(int)position.y-2.1);
					m->frapperBloc((int)(position.x+0.9),(int)position.y-2.1);
					if (toucheSol)
					{
						directionMouvement = none;
						break;
					}
					directionMouvement = bas;
					saut--;
					break;
				}
				if (saut <= (int)((5*16)/vitesseSaut) && toucheSol)
				{
					saut++;
					if (saut==(int)((5*16)/vitesseSaut))
					{
						toucheSol = false;
					}
					break;
				}
				directionMouvement = bas;
				saut--;
				break;
			case none:
				if (!toucheSol)
				{
					directionMouvement = bas;
					saut--;
					break;
				}
				break;
		}
	}
};
#endif