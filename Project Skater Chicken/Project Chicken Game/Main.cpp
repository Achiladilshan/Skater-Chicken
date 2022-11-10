/*===========================================================================

	INTE 11223 	: Programming Concepts
	Game Name   : Skate Chicken
	Version     : 1.0

	---- Team Members ----

	IM/2020/003 - Achila Dilshan Abeysinghe
	IM/2020/089 - Pramod Pinimal
	IM/2020/090 - Theekshana Fernando
	IM/2020/052 - Zafry Mubarak
	IM/2020/062 - Sakthigiri Thevarasa

============================================================================*/

#include <iostream>
#include <random>//for random generating
#include <string>
#include <sstream>

#include <SFML/Graphics.hpp>//sfml library


using namespace sf;// Avoid having to put sf in front of all the SFML classes and functions
using namespace std;

//declare functions
int enemyselection(int x, int y, int px);
int enemyspawnplace();


int main() {

	int windowWidth = 1920;
	int windowHeight = 1080;
	// window size

	// open window
	RenderWindow window(VideoMode(windowWidth, windowHeight), "Skater Chicken", Style::None);
	window.setFramerateLimit(60);//frame rate limit

	//textures of the projects
	Texture t1, t2, t3, t4, t5, t6, h1, t11, t12, t13, ht;
	t1.loadFromFile("resources/background.png");//background
	t2.loadFromFile("resources/left.png");//left chicken
	t3.loadFromFile("resources/right.png");//right chicken
	t4.loadFromFile("resources/1.png");//normal egg
	t5.loadFromFile("resources/2.png");//stool
	t6.loadFromFile("resources/3.png");//golden egg

	t11.loadFromFile("resources/11.png");//broken normal egg
	t12.loadFromFile("resources/12.png");//stool on ground
	t13.loadFromFile("resources/13.png");//broken gold egg

	ht.loadFromFile("resources/heart.png");//health


	h1.loadFromFile("resources/home.png");//back to home button

	Sprite sBackground(t1), sLeft(t2), sRight(t3), home(h1), enemy(t4), bonus(t6), broke(t11), heart(ht);
	/* A Sprite is an image that can be used as a 2d object,
	 * which have coordinates (x, y) and which you can move,
	 * destroy or create during the game
	 * textures can't move them during the game */

	vector <Sprite> enemies, bonuses, brokes, hearts;

	enemies.push_back(Sprite(enemy)); //-- don't need more textures
	bonuses.push_back(Sprite(bonus)); // make repetition
	brokes.push_back(Sprite(broke));
	hearts.push_back(Sprite(heart));

	int enemySpawnTimerMax = 50;
	int enemySpawntimer = 0;
	int enemySpeed = 11;//stools and normal eggs
	int bonusSpeed = 15;//golden eggs
	float ChickenSpeed = 20; //chicken travel speed

	float x = window.getSize().x / 2 - sLeft.getGlobalBounds().width / 2, y = window.getSize().y - sLeft.getGlobalBounds().height; //chicken image position
	float hx = window.getSize().x - heart.getGlobalBounds().width - 20;//hearth position

	int points = 0;
	int health = 3;

	int a = 1;//variable for identify left click or right click
	int n = 0;//check the which object is falling(normal egg or stool)
	int g = 0;//gold eggs falling

	Texture b1, b2, b3, m1, go, rt, htpw;
	b1.loadFromFile("resources/landing/play.png");//play button
	b2.loadFromFile("resources/landing/how to play.png");//how to play button
	b3.loadFromFile("resources/landing/quit.png");//quit button

	m1.loadFromFile("resources/landing/plain.png");//menu window
	go.loadFromFile("resources/game over.png");//game over window
	rt.loadFromFile("resources/retry.png");//game over window
	htpw.loadFromFile("resources/htp.png");//How to play window


	Sprite btn1(b1), btn2(b2), btn3(b3), fwindow(m1), gameover(go), retry(rt), htplay(htpw);

	Cursor cursor;


	bool landing = true;//landing page logic
	bool over = false;//game over page
	bool htp = false;//how to play page logic
	bool focus = true;//check window is focus

	//------- FONT score

	Text score, point;

	Font font, font1;

	font.loadFromFile("Comic Gecko Pro.otf");
	font1.loadFromFile("Bungee-Regular.ttf");

	// Set the font
	score.setFont(font);
	score.setCharacterSize(75);

	point.setFont(font1);
	point.setCharacterSize(135);

	// color for font
	score.setFillColor(Color::White);
	point.setFillColor(Color::Black);



	//game loop
	while (window.isOpen())
	{


		Event event;

		//------------------------------------------------

		//------------ Landing page --------------------//

		while (landing == true) {


			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed) {
					landing = false;
					// Someone closed the window
					window.close();
				}
				else if (event.type == Event::GainedFocus)//check window is focus or not
					focus = true;
				else if (event.type == Event::LostFocus)
					focus = false;
			}

			if (focus == true) {//if window is focus

				if (Keyboard::isKeyPressed(Keyboard::Escape))
				{
					landing = false;
					// Someone closed the window
					window.close();
				}


				///////when hover on button

				if (Mouse::getPosition(window).x >= 628 and Mouse::getPosition(window).x <= 1290 and Mouse::getPosition(window).y >= 239 and Mouse::getPosition(window).y <= 364)
				{
					cursor.loadFromSystem(Cursor::Hand);
					window.setMouseCursor(cursor);//mouse cursor change to hand
					btn1.setColor(Color(230, 230, 230, 255));
					if (Mouse::isButtonPressed(Mouse::Left)) {
						landing = false;
						//****** reset all variable to restart the game ****//

						x = 785, y = 730; //chicken image position
						a = 1;//variable for identify left click or right click
						n = 0;//check the which object is falling
						g = 0;
						enemySpawntimer = 0;
						points = 0; // set points to 0
						health = 3; // set health full
						enemies.clear();
						bonuses.clear();
						brokes.clear();

					}
				}
				else if (Mouse::getPosition(window).x >= 628 and Mouse::getPosition(window).x <= 1290 and Mouse::getPosition(window).y >= 466 and Mouse::getPosition(window).y <= 600)
				{
					cursor.loadFromSystem(Cursor::Hand);
					window.setMouseCursor(cursor);//mouse cursor change to hand
					btn2.setColor(Color(230, 230, 230, 255));
					if (Mouse::isButtonPressed(Mouse::Left)) {

						htp = true;
						landing = false;
					}
				}
				else if (Mouse::getPosition(window).x >= 628 and Mouse::getPosition(window).x <= 1290 and Mouse::getPosition(window).y >= 696 and Mouse::getPosition(window).y <= 828)
				{
					cursor.loadFromSystem(Cursor::Hand);
					window.setMouseCursor(cursor);//mouse cursor change to hand
					btn3.setColor(sf::Color(230, 230, 230, 255));
					if (Mouse::isButtonPressed(Mouse::Left)) {
						landing = false;
						// Someone closed the window
						window.close();
					}
				}
				else {
					cursor.loadFromSystem(Cursor::Arrow);
					window.setMouseCursor(cursor);//mouse cursor change to Arrow
					btn1.setColor(Color::White);
					btn2.setColor(Color::White);
					btn3.setColor(Color::White);
				}

				window.clear();

				window.draw(fwindow);

				//button positions
				btn1.setPosition(522, 135);
				window.draw(btn1);

				btn2.setPosition(522, 365);
				window.draw(btn2);

				btn3.setPosition(522, 595);
				window.draw(btn3);

				window.display();
			}

		}

		//----------------- end of the landing page ---------------//

		//------------------------------------------------------------------

		//------------ How to Play page --------------------//
		while (htp == true) {

			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed) {
					landing = false;
					// Someone closed the window
					window.close();
				}
				else if (event.type == Event::GainedFocus)//check window is focus or not
					focus = true;
				else if (event.type == Event::LostFocus)
					focus = false;
			}
			if (focus == true) {//if window is focus

				if (Keyboard::isKeyPressed(Keyboard::Escape))
				{
					over = false;
					// Someone closed the window
					window.close();
				}
				if (Mouse::getPosition(window).x >= 20 and Mouse::getPosition(window).x <= 154 and Mouse::getPosition(window).y >= 20 and Mouse::getPosition(window).y <= 154)
				{
					cursor.loadFromSystem(sf::Cursor::Hand);
					window.setMouseCursor(cursor);//mouse cursor change to hand
					if (Mouse::isButtonPressed(Mouse::Left)) {
						landing = true;
						htp = false;
					}
				}
				else {
					cursor.loadFromSystem(Cursor::Arrow);
					window.setMouseCursor(cursor);//mouse cursor change to Arrow
				}
				window.clear();
				window.draw(htplay);
				home.setPosition(20, 20); //back to home icon
				window.draw(home);
				window.display();
			}


		}

		//----------------- game over page -----------------------//

		while (over == true) {

			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed) {
					landing = false;
					// Someone closed the window
					window.close();
				}
				else if (event.type == Event::GainedFocus)//check window is focus or not
					focus = true;
				else if (event.type == Event::LostFocus)
					focus = false;
			}

			if (focus == true) {//if window is focus

				if (Keyboard::isKeyPressed(Keyboard::Escape))
				{
					over = false;
					// Someone closed the window
					window.close();
				}
				///////when hover on button
				if (Mouse::getPosition(window).x >= home.getPosition().x and Mouse::getPosition(window).x <= home.getPosition().x + home.getGlobalBounds().width and Mouse::getPosition(window).y >= home.getPosition().y and Mouse::getPosition(window).y <= home.getPosition().y + home.getGlobalBounds().height)
				{
					cursor.loadFromSystem(Cursor::Hand);
					window.setMouseCursor(cursor);//mouse cursor change to hand

					if (Mouse::isButtonPressed(Mouse::Left)) {
						landing = true;
						over = false;

						//****** reset all variable to restart the game ****//

						x = 785, y = 730; //chicken image position
						a = 1;//variable for identify left click or right click
						n = 0;//check the which object is falling
						g = 0;
						enemySpawntimer = 0;
						points = 0; // set points to 0
						health = 3; // set health full
						enemies.clear();
						bonuses.clear();
						brokes.clear();
					}
				}
				else if (Mouse::getPosition(window).x >= retry.getPosition().x and Mouse::getPosition(window).x <= retry.getPosition().x + retry.getGlobalBounds().width and Mouse::getPosition(window).y >= retry.getPosition().y and Mouse::getPosition(window).y <= retry.getPosition().y + retry.getGlobalBounds().height)
				{
					cursor.loadFromSystem(Cursor::Hand);
					window.setMouseCursor(cursor);//mouse cursor change to hand

					if (Mouse::isButtonPressed(Mouse::Left)) {
						//****** reset all variable to restart the game ****//

						x = 785, y = 730; //chicken image position
						a = 1;//variable for identify left click or right click
						n = 0;//check the which object is falling
						g = 0;
						enemySpawntimer = 0;
						points = 0; // set points to 0
						health = 3; // set health full
						enemies.clear();
						bonuses.clear();
						brokes.clear();

						over = false;
					}
				}
				else {
					cursor.loadFromSystem(Cursor::Arrow);
					window.setMouseCursor(cursor);//mouse cursor change to Arrow
				}



				stringstream ss;
				ss << points;

				point.setString(ss.str());


				window.clear();

				window.draw(gameover);

				home.setPosition(window.getSize().x / 2 - 250, window.getSize().y - 145);
				window.draw(home);

				retry.setPosition(window.getSize().x / 2 + 150, window.getSize().y - 145);
				window.draw(retry);

				//------------ Draw Score

				point.setPosition(window.getSize().x / 2 - point.getGlobalBounds().width / 2, 630);
				window.draw(point);


				window.display();

			}
		}
		//-----------------------------------------------------------

		////--------------- Back to home button

		if (Mouse::getPosition(window).x >= 20 and Mouse::getPosition(window).x <= 154 and Mouse::getPosition(window).y >= 20 and Mouse::getPosition(window).y <= 154)
		{
			cursor.loadFromSystem(sf::Cursor::Hand);
			window.setMouseCursor(cursor);//mouse cursor change to hand
			if (Mouse::isButtonPressed(Mouse::Left)) {
				landing = true;

				//****** reset all variable to restart the game ****//

				x = 785, y = 730; //chicken image position
				a = 1;//variable for identify left click or right click
				n = 0;//check the which object is falling
				g = 0;
				enemySpawntimer = 0;
				points = 0; // set points 0
				health = 3; // set health full
				enemies.clear();
				bonuses.clear();
				brokes.clear();

			}
		}
		else {
			cursor.loadFromSystem(Cursor::Arrow);
			window.setMouseCursor(cursor);//mouse cursor change to Arrow
		}

		//---------------------------------------------------------------
		//-------------- game start --------------------

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				// Someone closed the window
				window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			// Someone closed the window
			window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Left))//left arrow click
		{
			a = 1;
			// move left...
			if (x >= 20) {
				x -= ChickenSpeed;
			}

		}
		else if (Keyboard::isKeyPressed(Keyboard::Right))//right arrow click
		{
			a = 2;
			// move right...
			if (x <= window.getSize().x - sLeft.getGlobalBounds().width - 20) {
				x += ChickenSpeed;
			}
		}

		//------ heart positions

		for (int i = 1; i < health + 1; i++) {
			heart.setPosition(hx, 150);
			hearts.push_back(Sprite(heart));//put the heart to list
			hx = hx - heart.getGlobalBounds().width - 35;
		}

		hx = window.getSize().x - heart.getGlobalBounds().width - 20;

		if (health == 0) {//when health is 0 game is over
			over = true;
		}



		/////------------------ enemies falling --------------------/////
		if (brokes.size() > 6) {
			brokes.erase(brokes.begin());//remove broken pieces when reach 6 pieces // @suppress("Invalid arguments")
		}


		for (int i = 1; i < enemies.size(); i++) {

			enemies[i].move(0, enemySpeed);//move enemies to down

			//check enemy reach bottom
			if (enemies[i].getPosition().y > window.getSize().y - enemy.getGlobalBounds().height + 10) {

				if (enemies[i].getTexture() == &t4) {//check enemy type to select the broken type
					broke.setTexture(t11);
					broke.setPosition(enemies[i].getPosition().x, window.getSize().y - broke.getGlobalBounds().height + 10);
					brokes.push_back(Sprite(broke));//put the broken type to list
					health--;

				}
				else if (enemies[i].getTexture() == &t5) {//check enemy type to select the broken type
					broke.setTexture(t12);
					broke.setPosition(enemies[i].getPosition().x, window.getSize().y - broke.getGlobalBounds().height + 10);
					brokes.push_back(Sprite(broke));//put the broken type to list
				}


				enemies.erase(enemies.begin() + i);//remove the enemy when reach bottom // @suppress("Invalid arguments")

			}


		}

		for (int i = 1; i < bonuses.size(); i++) {

			bonuses[i].move(0, bonusSpeed);//move golden eggs to down

			//check enemy reach bottom
			if (bonuses[i].getPosition().y > window.getSize().y - bonus.getGlobalBounds().height + 10) {

				if (bonuses[i].getTexture() == &t6) {//check enemy type to select the broken type
					broke.setTexture(t13);
					broke.setPosition(bonuses[i].getPosition().x, window.getSize().y - broke.getGlobalBounds().height + 10);
					brokes.push_back(Sprite(broke));//put the broken type to list
				}

				bonuses.erase(bonuses.begin() + i);//remove the enemy when reach bottom // @suppress("Invalid arguments")

			}


		}




		if (enemySpawntimer >= enemySpawnTimerMax)
		{
			n = enemyselection(1, 2, 60);//(first number,second number, probability for first number)
			g = enemyselection(3, 0, 10);//(first number,second number, probability for first number)

			if (n == 1) {
				enemy.setTexture(t4);//fall normal egg
			}
			else if (n == 2) {
				enemy.setTexture(t5);//fall stool
			}

			if (g == 3) {
				bonus.setPosition(enemyspawnplace(), -40);//set starting position
				bonuses.push_back(Sprite(bonus));//put the enemy type to list

			}

			enemy.setPosition(enemyspawnplace(), -40);//set starting position
			enemies.push_back(Sprite(enemy));//put the enemy type to list


			enemySpawntimer = 0;//reset timer

		}
		else {
			enemySpawntimer += 1;//spawn time++
		}

		//--------- COLLISION

		if (a == 1) {

			for (int i = 1; i < enemies.size(); i++) {

				if (sLeft.getGlobalBounds().intersects(enemies[i].getGlobalBounds())) {
					if (enemies[i].getTexture() == &t4) {
						points += 5;
					}
					else {
						if (points >= 10)
							points -= 10;
						else if (points > 0)
							points -= 5;

					}
					enemies.erase(enemies.begin() + i);
				}
			}

			for (int i = 1; i < bonuses.size(); i++) {

				if (sLeft.getGlobalBounds().intersects(bonuses[i].getGlobalBounds())) {

					points += 25;
					bonuses.erase(bonuses.begin() + i);
				}
			}
		}
		else if (a == 2) {

			for (int i = 1; i < enemies.size(); i++) {

				if (sRight.getGlobalBounds().intersects(enemies[i].getGlobalBounds())) {

					if (enemies[i].getTexture() == &t4) {
						points += 5;
					}
					else {
						if (points >= 10)
							points -= 10;
						else if (points > 0)
							points -= 5;
					}
					enemies.erase(enemies.begin() + i);
				}
			}

			for (int i = 1; i < bonuses.size(); i++) {

				if (sRight.getGlobalBounds().intersects(bonuses[i].getGlobalBounds())) {

					points += 25;
					bonuses.erase(bonuses.begin() + i);
				}
			}

		}

		stringstream ss;
		ss << "Score: " << points;

		score.setString(ss.str());


		//---------- render
		window.clear();//clear old frame

		window.draw(sBackground); //display background image


		///---------- Draw Eggs

		for (int i = 1; i < enemies.size(); i++) {
			window.draw(enemies[i]);
		}


		for (int i = 1; i < bonuses.size(); i++) {
			window.draw(bonuses[i]);
		}

		for (int i = 1; i < brokes.size(); i++) {
			window.draw(brokes[i]);
		}

		//----------- Draw home
		home.setPosition(20, 20); //back to home icon
		window.draw(home);


		///---------- Draw chicken

		if (a == 1) {//when click left arrow
			sLeft.setPosition(x, y);
			window.draw(sLeft);
		}
		else {//when click right arrow
			sRight.setPosition(x, y);
			window.draw(sRight);
		}

		///---------- Draw health

		for (int i = 1; i < health + 1; i++) {
			window.draw(hearts[i]);
		}

		//------------ Draw Score


		score.setPosition(window.getSize().x - 450, 20);
		window.draw(score);



		window.display(); // Show everything we just drew
	}


	//end of the game
	return 0;
}




int enemyselection(int x, int y, int px)//c mean rejection number
{

	int n = 1 + rand() % 100;//here, it gives to n a random value from 1 to 100

	// n is smaller than px with probability px/100
	if (n <= px)
		return x;

	else
		return y;

}

int enemyspawnplace()
{
	int x = 15 + rand() % 1700;  //here, it gives to n a random value from 10 to 1700
	return x;

}


