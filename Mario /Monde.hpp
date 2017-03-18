#ifndef DEF_MONDE
#define DEF_MONDE 
#include <vector>
#include <string>

#include "Bloc.hpp"
class Monde
{
private:
	std::vector< std::vector<Bloc> > level;
public:
	Monde(){
		level;
	};
    void ajouterBloc(std::vector<Bloc> b){
		this->level.push_back(b);
	}
	sf::Vector2i getSize(){
		return sf::Vector2i(level[0].size(),level.size());
	}
	void afficherMonde(sf::RenderWindow *window){
		int posX = 0;
		int posY = 0;
		for (int i = 0; i < level[0].size(); ++i)
		{
			for (int j = 0; j < level.size(); ++j)
			{
				level[j][i].setPos(posX,posY);
				window->draw(level[j][i].getTexture());
				posY+=16;
			}
			posX+=16;
			posY = 0;
		}
	}
	void clearVector(){
		level.clear();
	}
	void construireLevel(std::vector<std::string> l,sf::Texture* sol,sf::Texture* mur,sf::Texture* ciel){
		std::vector<Bloc> tmp;
		Bloc* bloctmp;
		sf::RectangleShape recttmp;
		for(int i = 0; i<l.size();i++){
			for (int j = 0; j < l[i].length(); ++j)
			{
				if (l[i][j] == 'M')
				{
					recttmp.setSize(sf::Vector2f(16, 16));
					recttmp.setTexture(mur);
					recttmp.setTextureRect(sf::IntRect(0,0,16,16));
					bloctmp = new Bloc(true,recttmp,true);
				}
				if (l[i][j] == 'S')
				{
					recttmp.setSize(sf::Vector2f(16, 16));
					recttmp.setTexture(sol);
					recttmp.setTextureRect(sf::IntRect(0,0,16,16));
					bloctmp = new Bloc(false,recttmp,true);
				}
				if (l[i][j] != 'S' and l[i][j] != 'M')
				{
					recttmp.setSize(sf::Vector2f(16, 16));
					recttmp.setTexture(ciel);
					recttmp.setTextureRect(sf::IntRect(0,0,16,16));
					bloctmp = new Bloc(false,recttmp,false);
				}
				tmp.push_back(*bloctmp);
				delete bloctmp;
			}
			this->ajouterBloc(tmp);
			tmp.clear();
		}
	}
	Bloc getBloc(int x,int y){
		return level[y][x];
	}
	void frapperBloc(int x,int y){
		(level[y][x]).setFrapper(true);
	}
	void frapperBlocToFalse(int x,int y){
		(level[y][x]).setFrapper(false);
	}
	
};
#endif