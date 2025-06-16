/*
 * File: Sierpinski.cpp
 * --------------------------
 * Name: Luka Rapava
 * Section: Andria Kobaidze
 * This file is the starter project for the Sierpinski problem
 * on Assignment #3.
 */

#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>

#define DEFAULT_ORDER 5
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

// Draws triangle at a given location
void drawTriangle(sf::RenderWindow& window, sf::Vector2f a, sf::Vector2f b, sf::Vector2f c) {
	sf::VertexArray triangle(sf::Triangles, 3);
	triangle[0].position = a;
	triangle[1].position = b;
	triangle[2].position = c;
	triangle[0].color = triangle[1].color = triangle[2].color = sf::Color::White;
	window.draw(triangle);
}

// Draws Sierpinski triangle on window with verticies a, b, and c
void sierpinski(sf::RenderWindow& window, sf::Vector2f a, sf::Vector2f b, sf::Vector2f c, int order) {

	if (order == 0) {
		drawTriangle(window, a, b, c);
		return;
	}

	sf::Vector2f ab = (a + b) / 2.f;
	sf::Vector2f bc = (b + c) / 2.f;
	sf::Vector2f ca = (c + a) / 2.f;

	sierpinski(window, a, ab, ca, order - 1);
	sierpinski(window, ab, b, bc, order - 1);
	sierpinski(window, ca, bc, c, order - 1);
}


int main() {

	// window creation
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Sierpinski Triangle");

	// points for the main triangle
	sf::Vector2f a(WINDOW_WIDTH / 2, 50);
	sf::Vector2f b(50, WINDOW_HEIGHT - 50);
	sf::Vector2f c(WINDOW_WIDTH - 50, WINDOW_HEIGHT - 50);

	auto currentTime = std::chrono::steady_clock::now();
	auto previousTime = currentTime;
	auto deltaTime = std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - previousTime);

	sf::Font dejavu_sans;
	if (!dejavu_sans.loadFromFile("DejaVuSans.ttf")) {
		return -1;
	}

	int order = DEFAULT_ORDER;

	// making sure deltaTime is not zero
	std::this_thread::sleep_for(std::chrono::milliseconds(1));

	while (window.isOpen()) {

		currentTime = std::chrono::steady_clock::now();
		deltaTime = std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - previousTime);

		long long FPS = 1e9 / (deltaTime.count());
		sf::Text fps_label(std::to_string(FPS) + " FPS\n" + "ord: " + std::to_string(order)+ "\n", dejavu_sans, 30);
		fps_label.setFillColor(sf::Color::Green);
		fps_label.setPosition(10, 10);
		
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Equal) {
					order++;
				}
			}
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Hyphen) {
					order = std::max(0, order-1);
				}
			}
		}

		window.clear(sf::Color::Black);
		sierpinski(window, a, b, c, order);
		window.draw(fps_label);
		window.display();

		previousTime = currentTime;
		
	}

	return 0;
}
