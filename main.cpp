#include <SFML/Graphics.hpp> 
#include <iostream>         
#include <cmath>

using namespace sf;

float Pow(float a)
{
	float b;
	b = a * a;
	return b;
}
int RandomNumber(int min, int max)
{
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);

	return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}
int main()
{
	
	const int wight = 920;
	const int high = 500;
	const float speed = 0.1;
	
	float speedxyQx = 0;
	float speedxyQy = 0;
	float speedxyWx = 0;
	float speedxyWy = 0;
	float speedxEx = 0;
	float speedxEy = 0;



	int tim = 0;
	int trailindex = 1;

	    float distanceQW;
		float distanceQE;
		float distanceWE;

		float distanceQM;
		float distanceEM;
		float distanceWM;

	CircleShape planetQ;
	CircleShape planetW;
	CircleShape planetE;

	CircleShape pointlineQ[200];
	CircleShape pointlineW[200];
	CircleShape pointlineE[200];

	planetQ.setOrigin(15, 15);
	planetW.setOrigin(15, 15);
	planetE.setOrigin(15, 15);

	
	RenderWindow window(VideoMode(wight, high), "planets");
	


	planetQ.setRadius(20);
	planetQ.setPointCount(20);
	planetQ.setFillColor(Color(RandomNumber(40, 200), RandomNumber(40, 200), RandomNumber(40, 200)));
	planetQ.setPosition(100, 20);

	planetW.setPointCount(20);
	planetW.setRadius(20);
	planetW.setFillColor(Color(RandomNumber(40, 200), RandomNumber(40, 200), RandomNumber(40, 200)));
	planetW.setPosition(100, 200);

	planetE.setPointCount(20);
	planetE.setRadius(20);
	planetE.setFillColor(Color(RandomNumber(40, 200), RandomNumber(40, 200), RandomNumber(40, 200)));
	planetE.setPosition(100, 200);

	for (int c = 0; c <= 199; c++)
	{
		pointlineQ[c].setFillColor(Color(255,255,255));
		pointlineQ[c].setRadius(3);
		pointlineQ[c].setPointCount(7);

		pointlineW[c].setFillColor(Color(255, 255, 255));
		pointlineW[c].setRadius(3);
		pointlineW[c].setPointCount(7);

		pointlineE[c].setFillColor(Color(255, 255, 255));
		pointlineE[c].setRadius(3);
		pointlineE[c].setPointCount(7);
	}
	
	
	window.setVerticalSyncEnabled(true);

	Clock clock;
	float time;

	while (window.isOpen())
	{ 
		time = clock.getElapsedTime().asMicroseconds();
		if (time >= 0.01f)
		{
			if (tim == 199)
			{
				tim = 0;
		    }
			tim += 1;
		}

		Vector2i PixelyPos = Mouse::getPosition(window);//узнаем позицию мыши
		Vector2f mospos = window.mapPixelToCoords(PixelyPos);//узнаем позицию мыши

		if (time == 0.01f) 
		{ 
			
			clock.restart();
		}
		if (Keyboard::isKeyPressed(Keyboard::Num1))
		{
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				distanceQM = 1;
			}
			
			if (Keyboard::isKeyPressed(Keyboard::Q))
			{
				for (int c = 0; c <= 199; c++)
				{
					pointlineQ[c].setPosition(-10, -10);
					pointlineW[c].setPosition(-10, -10);
					pointlineE[c].setPosition(-10, -10);
				}
				planetQ.setPosition(mospos.x, mospos.y);
			}

		}
		else
		{
			distanceQM = LONG_MAX;
		}
		if (Keyboard::isKeyPressed(Keyboard::Num2))
		{
			if (Mouse::isButtonPressed(Mouse::Left))
			{
			
					distanceWM = 1;
				
			}
			if (Keyboard::isKeyPressed(Keyboard::Q))
			{
				for (int c = 0; c <= 199; c++)
				{
					pointlineQ[c].setPosition(-10, -10);
					pointlineW[c].setPosition(-10, -10);
					pointlineE[c].setPosition(-10, -10);
				}
				planetW.setPosition(mospos.x, mospos.y);
			}

		}
		else
		{
			distanceWM = LONG_MAX;
		}
		if (Keyboard::isKeyPressed(Keyboard::Num3))
		{
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				distanceEM = 1;
			}
			if (Keyboard::isKeyPressed(Keyboard::Q))
			{
				for (int c = 0; c <= 199; c++)
				{
					pointlineQ[c].setPosition(-10, -10);
					pointlineW[c].setPosition(-10, -10);
					pointlineE[c].setPosition(-10, -10);
				}
				planetE.setPosition(mospos.x, mospos.y);
			}

		}
		else
		{
			distanceEM = LONG_MAX;
		}
		if (Mouse::isButtonPressed(Mouse::Right))
		{
			distanceQW = sqrt((pow(2, abs((planetW.getPosition().x / 100) - (planetQ.getPosition().x / 100))) + (pow(2, abs((planetQ.getPosition().y / 100) - (planetW.getPosition().y / 100))))));
			distanceQE = sqrt((pow(2, abs((planetE.getPosition().x / 100) - (planetQ.getPosition().x / 100))) + (pow(2, abs((planetE.getPosition().y / 100) - (planetQ.getPosition().y / 100))))));
			distanceWE = sqrt((pow(2, abs((planetE.getPosition().x / 100) - (planetW.getPosition().x / 100))) + (pow(2, abs((planetE.getPosition().y / 100) - (planetW.getPosition().y / 100))))));
			
			speedxyQx += ((speed / pow(2,distanceQW)) * ((planetW.getPosition().x - planetQ.getPosition().x)/ distanceQW)) + ((-speed / pow(2, distanceQE)) * ((planetQ.getPosition().x - planetE.getPosition().x) / distanceQE)) + ((-speed / pow(2, distanceQM)) * ((planetQ.getPosition().x - mospos.x) / distanceQM));
				

			speedxyQy += ((speed / pow(2, distanceQW)) * ((planetW.getPosition().y - planetQ.getPosition().y)/ distanceQW)) + ((-speed / pow(2, distanceQE)) * ((planetQ.getPosition().y - planetE.getPosition().y) / distanceQE)) + ((-speed / pow(2, distanceQM)) * ((planetQ.getPosition().y - mospos.y) / distanceQM));

			
			speedxyWx += ((speed / pow(2, distanceQW)) * ((planetQ.getPosition().x - planetW.getPosition().x)/ distanceQW)) + ((speed / pow(2, distanceWE)) * ((planetE.getPosition().x - planetW.getPosition().x) / distanceWE)) + ((-speed / pow(2, distanceWM)) * ((planetW.getPosition().x - mospos.x) / distanceWM));
				

			speedxyWy += ((speed / pow(2, distanceQW)) * ((planetQ.getPosition().y - planetW.getPosition().y)/ distanceQW)) + ((speed / pow(2, distanceWE)) * ((planetE.getPosition().y - planetW.getPosition().y) / distanceWE)) + ((-speed / pow(2, distanceWM)) * ((planetW.getPosition().y - mospos.y) / distanceWM));
				

			speedxEx += ((speed / pow(2, distanceQE)) * ((planetQ.getPosition().x - planetE.getPosition().x )/ distanceQE)) + ((-speed / pow(2, distanceWE)) * ((planetE.getPosition().x - planetW.getPosition().x) / distanceWE)) + ((-speed / pow(2, distanceEM)) * ((planetE.getPosition().x - mospos.x) / distanceEM));
			
				
			speedxEy += ((speed / pow(2, distanceQE)) * ((planetQ.getPosition().y - planetE.getPosition().y )/ distanceQE)) + ((-speed / pow(2, distanceWE)) * ((planetE.getPosition().y - planetW.getPosition().y) / distanceWE)) + ((-speed / pow(2, distanceEM)) * ((planetE.getPosition().y - mospos.y) / distanceEM));
				
			if (distanceWE <= 1.55f)
			{
				speedxyWx = 0;
				speedxyWy = 0;
				speedxEx = 0;
				speedxEy = 0;
			}
			if (distanceQW <= 1.55f)
			{
				speedxyQy = 0;
				speedxyQx = 0;
				speedxyWy = 0;
				speedxyWx = 0;
			}
			if (distanceQE <= 1.55f)
			{
				speedxEx = 0;
				speedxEy = 0;
				speedxyQy = 0;
				speedxyQx = 0;
			}


		}
	
	
		

		if (Mouse::isButtonPressed(Mouse::Right))
		{
			planetQ.move(speedxyQx / 100, speedxyQy / 100);
			planetW.move(speedxyWx / 100, speedxyWy / 100);
			planetE.move(speedxEx / 100, speedxEy / 100);
		}

		Event event;
		while (window.pollEvent(event)) { if (event.type == Event::Closed)  window.close(); }

		window.clear(Color(0,0,0));



		if (Mouse::isButtonPressed(Mouse::Right))
		{

			for (int c = 0; c <= 199; c++)
			{


				pointlineW[tim].setPosition(planetW.getPosition().x, planetW.getPosition().y);

				pointlineE[tim].setPosition(planetE.getPosition().x, planetE.getPosition().y);

				pointlineQ[tim].setPosition(planetQ.getPosition().x, planetQ.getPosition().y);


				window.draw(pointlineQ[c]);
				window.draw(pointlineW[c]);
				window.draw(pointlineE[c]);
			}
		
		}
		else
		{

			for (int c = 0; c <= 199; c++)
			{
				pointlineQ[c].setPosition(-10, -10);
				pointlineW[c].setPosition(-10, -10);
				pointlineE[c].setPosition(-10, -10);
			}
		}



		window.draw(planetQ);
		window.draw(planetW);
		window.draw(planetE);
		
	
		
		
	
			

		window.display();
	}
	return 0;
}
