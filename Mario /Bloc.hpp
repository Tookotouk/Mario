#ifndef DEF_BLOC
#define DEF_BLOC 
class Bloc
{
private:
	bool cassable;
	bool frapper;
	sf::RectangleShape rectangle;
	bool collision;
public:
	Bloc(bool c,sf::RectangleShape r,bool col){
		cassable = c;
		rectangle = r;
		collision = col;
		frapper = false;
	}
	sf::RectangleShape getTexture(){
		return this->rectangle;
	}
	bool getFrapper(){
		return frapper;
	}
	void setFrapper(bool t){
		frapper = t;
	}
	void setPos(int posX,int posY){
		rectangle.setPosition(posX,posY);
	}
	bool coll(){
		return collision;
	}
	
};
#endif