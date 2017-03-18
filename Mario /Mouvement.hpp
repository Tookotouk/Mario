#include <iostream>
#include <SFML/Window/Keyboard.hpp>

int saisitTouche(){
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{	
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		{
			return 1;//droiteHaut
		}
		return 0;//droite
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{	
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		{
			return 3;//gaucheHaut
		}
		return 2;//gauche
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{	
		return 4;//haut
	}
	/*else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{	
		return 5;//bas
	}*/
	return 8;//none
}