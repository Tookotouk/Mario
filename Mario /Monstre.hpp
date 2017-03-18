#ifndef DEF_MONSTRE
#define DEF_MONSTRE
class Monstre
{
enum EtatMonstre{
	droite,
	gauche,
	bas,
	none
};
private:
	EtatMonstre direction;
	bool vivant;
	sf::Sprite texture;
	int animation;
	float vitesseDeplacement;
	int waitDespawn;
	sf::SoundBuffer sonBuffer;
	sf::Sound son;
public:
	Monstre(){

	}
	Monstre(sf::Sprite p,sf::Vector2f v){
		vivant = true;
		vitesseDeplacement = 1;
		texture = p;
		direction = droite;
		animation = 0;
		texture.setPosition(v);
		waitDespawn = 0;
		sonBuffer;
		son;
	}
	sf::Sprite getSprite(){
		return texture;
	}
	void setSon(){
		sonBuffer.loadFromFile("Sounds/kick.ogg");
		son.setBuffer(sonBuffer);
	}
	bool getStatus(){
		return vivant;
	}
	void setPosition(float x,float y){
		texture.setPosition(sf::Vector2f(x,y));
	}
	void afficher(sf::RenderWindow *w){
		w->draw(texture);
	}
	void animer(){
		if (animation > 1.9*16/vitesseDeplacement)
		{
			animation = 0;
		}
		if (animation%16/vitesseDeplacement == 0)
		{
			texture.setTextureRect(sf::IntRect(animation*vitesseDeplacement,0,16,16));
		}
		animation++;
	}
	void bouger(){
		switch(direction){
			case droite : 
				texture.move(vitesseDeplacement,0);
				animer();
				break;
			case gauche : 
				texture.move(-vitesseDeplacement,0);
				animer();
				break;
			case bas:
				texture.move(vitesseDeplacement,0);
			case none:
				break;
		}
	}
	int getWaitDespawn(){
		return waitDespawn;
	}
	void addWaitDespawn(){
		waitDespawn++;
	}
	void tuer(Personnage* joueur,Monde m){
		if (m.getBloc((int)((texture.getPosition().x/16)+0.5),(int)texture.getPosition().y/16).getFrapper())
		{
			vivant = false;
			texture.setTextureRect(sf::IntRect(0,0,0,0));
			son.play();
			waitDespawn++;
			return;
		}
		if(joueur->getSprite().getGlobalBounds().intersects(texture.getGlobalBounds())){
			if (joueur->getSprite().getPosition().y+16 < texture.getPosition().y - 8)
			{
				vivant = false;
				texture.setTextureRect(sf::IntRect(32,0,16,16));
				waitDespawn++;
				son.play();
			}
			else{
				joueur->tuerJoueur();
			}
		}
	}
	bool verifierBlocADroite(sf::Vector2f pos,Monde m){
		return (m.getBloc(pos.x+1.15,pos.y-0.1).coll() or m.getBloc(pos.x+1.15,pos.y-1).coll());
	}
	bool verifierBlocAGauche(sf::Vector2f pos,Monde m){
		return (m.getBloc(pos.x-0.1,pos.y-0.1).coll() or m.getBloc(pos.x-0.1,pos.y-1).coll());
	}
	bool verifierBlocBas(sf::Vector2f pos,Monde m){
		return (m.getBloc(pos.x,pos.y).coll() or m.getBloc(pos.x+1,pos.y).coll());
	}
	bool verifierBlocAngleDroiteBas(sf::Vector2f pos,Monde m){
		return (m.getBloc(pos.x+1,pos.y).coll());
	}
	bool verifierBlocAngleGaucheBas(sf::Vector2f pos,Monde m){
		return (m.getBloc(pos.x,pos.y).coll());
	}
	void verifColl(Monde m){
		sf::Vector2f position(((texture.getPosition().x))/16,((texture.getPosition().y)/16)+1);//coordonnée du point bas gauche du mob
		switch(direction){
				case droite:
					if (verifierBlocADroite(position,m) or !verifierBlocAngleDroiteBas(position,m))
					{
						direction = gauche;
						break;
					}
					break;
				case gauche:
					if (verifierBlocAGauche(position,m) or !verifierBlocAngleGaucheBas(position,m))
					{
						direction = droite;
						break;
					}
					break;
				case none:
					/*if (!verifierBlocBas(position,m))
					{
						direction = bas;
						break;
					}*/
					break;
		}
	}	
	~Monstre(){}
	
};
#endif