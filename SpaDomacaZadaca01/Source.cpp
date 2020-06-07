#include "SFML/Graphics.hpp"


#include <iostream>


#include"Short_path.h"

using namespace sf;
using namespace std;



int main(int argc, char* argv) 
{
	cout
		<< "Za postavljanje pozicije CIJEPIVA drzite  LEFT CTRL + LEFT MOUSE BUTTON" << endl
		<< "Za postavljanje pozicije ZIVI ZID drzite LEFT MOUSE BUTTON" << endl
		<< "Za postavljanje pozicije PERNARA drzite LEFT SHIFT + LEFT MOUSE BUTTON" << endl
		<< "Za brisanje RIGHT MOUSE BUTTON" << endl
		<< "Za pokretanje CIJEPLJENJE I CIPIRANJE PERNARA pritisnite ENTER" << endl;
		


	Short_path Short_path;
	const int boxOnX = 40, boxOnY = 40;
	sf::RenderWindow window(sf::VideoMode(1280.0f, 720.0f), "CIJEPI PERNARA by Lovrhino Behnino");
	//window.setFramerateLimit(144);

	//window.setVerticalSyncEnabled(true);
	RectangleShape box[boxOnX][boxOnY];

	Texture pernar;
	pernar.loadFromFile("Texture/pernar.jpg");

	Texture needle;
	needle.loadFromFile("Texture/Needle.jpg");

	Texture zivi_zid;
	zivi_zid.loadFromFile("Texture/zivizid.png");

	
	
	
	const int boxSizeX = 40, boxSizeY =40;
	for (int x = 0; x < boxOnX; x++)
		for (int y = 0; y < boxOnY; y++)
		{
			box[x][y].setSize(Vector2f(float(boxSizeX), float(boxSizeY)));
			box[x][y].setOutlineThickness(1.2f);
			box[x][y].setOutlineColor(Color::Black);
			box[x][y].setFillColor(Color::White);

		}
	box[0][0].setTexture(&needle);
	box[9][9].setTexture(&pernar);
	while (window.isOpen()) {

		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::EventType::Closed)
				window.close();

			if (Mouse::isButtonPressed(Mouse::Left))
			{
				Vector2i  mousePos = Mouse::getPosition(window);
				int x = floor(mousePos.x / boxSizeX);
				int y = floor(mousePos.y / boxSizeY);
				if (box[x][y].getFillColor() != Color::Green && box[x][y].getFillColor() != Color::Red) {
					
					//box[x][y].setFillColor(Color::Magenta);
					box[x][y].setTexture(&zivi_zid);
					Short_path.setObstacle(x, y);
				}
			}
			if (Mouse::isButtonPressed(Mouse::Right))
			{
				Vector2i  mousePos = Mouse::getPosition(window);
				int x = floor(mousePos.x / boxSizeX);
				int y = floor(mousePos.y / boxSizeY);
				if (box[x][y].getFillColor() != Color::Green && box[x][y].getFillColor() != Color::Red) {
					box[x][y].setFillColor(Color::White);
					box[x][y].setTexture(NULL);
					Short_path.unsetObstacle(x, y);
				}
			}
			if (Keyboard::isKeyPressed(Keyboard::LControl) ) 
			{
				if (Mouse::isButtonPressed(Mouse::Left))
				{
					for (int x = 0; x < boxOnX; x++)
						for (int y = 0; y < boxOnY; y++)
						{
							if (box[x][y].getTexture() == &needle)
							{
								box[x][y].setFillColor(Color::White);
								box[x][y].setTexture(NULL);
								Short_path.unsetObstacle(x, y);
								
							}
						}
					Vector2i  mousePos = Mouse::getPosition(window);
					int x = floor(mousePos.x / boxSizeX);
					int y = floor(mousePos.y / boxSizeY);
					box[x][y].setTexture(&needle);
					//box[x][y].setFillColor(Color::Green);
					Short_path.setStart(x, y);
				}
			}
			if (Keyboard::isKeyPressed(Keyboard::LShift) ) 
			{
				if (Mouse::isButtonPressed(Mouse::Left))
				{

					for (int x = 0; x < boxOnX; x++)
						for (int y = 0; y < boxOnY; y++)
						{
							if (box[x][y].getTexture() == &pernar) 
							{
								box[x][y].setFillColor(Color::White);
								box[x][y].setTexture(NULL);
								Short_path.unsetObstacle(x, y);
							}
						}
					Vector2i  mousePos = Mouse::getPosition(window);
					int x = floor(mousePos.x / boxSizeX);
					int y = floor(mousePos.y / boxSizeY);
					box[x][y].setTexture(&pernar);
					//box[x][y].setFillColor(Color::Red);
					Short_path.setEnd(x, y);
					//Short_path.setObstacle(x, y);
				}
			}
			if (Keyboard::isKeyPressed(Keyboard::Enter))
			{
				Short_path.Solve_Short_path();
				for (int x = 0; x < boxOnX; x++)
					for (int y = 0; y < boxOnY; y++)
					{
						if (Short_path.getVisitedState(x, y) == 1 && !(box[x][y].getFillColor() == Color::Green) && !(box[x][y].getFillColor() == Color::Red))
							box[x][y].setFillColor(Color(255, 255, 204));

						//if (Short_path.getVisitedState(x, y) == 0 && !(box[x][y].getFillColor() == Color::Green) && !(box[x][y].getFillColor() == Color::Red) && !(box[x][y].getFillColor() == Color::Magenta))
						//	box[x][y].setFillColor(Color::Blue);

						if (Short_path.getParentState(x, y) == 1 && !(box[x][y].getFillColor() == Color::Red))
							box[x][y].setFillColor(Color::Yellow);
					}
				
			}
		}
		window.clear(Color::Red);
		for (int x = 0; x < boxOnX; x++)
			for (int y = 0; y < boxOnY; y++)
			{
				box[x][y].setPosition(x * boxSizeX, y * boxSizeY);
				window.draw(box[x][y]);
			}
		window.display();
	}
	
	return 0;
}