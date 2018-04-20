#include <iostream>
#include <math.h>
#include <algorithm>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;
#define int long double

const int sq = 1.73205080757;
class Vector {
public:
	int x, y;
	Vector(int _x = 0, int _y = 0) {
		x = _x;
		y = _y;
	}
	Vector operator *(int a) {
		return Vector(x * a, y * a);
	}
	int len() {
		return sqrt(x * x + y * y);
	}
	Vector operator +(Vector a) {
		return Vector(x + a.x, y + a.y);
	}
	Vector operator -(Vector a) {
		return Vector(x - a.x, y - a.y);
	}
	Vector operator /(int a) {
		return Vector(x / a, y / a);
	}
};

signed main() {
	RenderWindow window(VideoMode(1680, 1050), "Koch Snowflake");
	VertexArray table(LinesStrip, 4);
	table[0].position = Vector2f(200, 200);
	table[1].position = Vector2f(600, 200);
	table[2].position = Vector2f(400, 546);
	table[3] = table[0];
	window.draw(table);
	window.display();
	int table_sz = 4;
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape)) {
				window.close();
			}
			if (Keyboard::isKeyPressed(Keyboard::N)) {
				window.clear();
				VertexArray table2(LinesStrip, table_sz * 5 - 4);
				for (int i = 0; i < table_sz - 1; i++) {
					int x1 = table[i].position.x;
					int y1 = table[i].position.y;
					int x2 = table[i + 1].position.x;
					int y2 = table[i + 1].position.y;
					Vector A(x1, y1);
					Vector B(x2, y2);
					Vector C = A * 2 + B;
					C = C / 3;
					int x3 = C.x;
					int y3 = C.y;
					C = A + B * 2;
					C = C / 3;
					int x4 = C.x;
					int y4 = C.y;
					Vector a = Vector(x3, y3);
					Vector b = Vector(x4, y4);
					Vector p = a + b;
					p = p / 2;
					Vector ab = b - a;
					swap(ab.x, ab.y);
					ab.x *= -1;
					p = p - ab*sq / 2;
					int x5 = p.x;
					int y5 = p.y;
					table2[i * 5].position = Vector2f(x1, y1);
					table2[i * 5].color = Color::Cyan;
					table2[i * 5 + 1].position = Vector2f(x3, y3);
					table2[i * 5 + 1].color = Color::Blue;
					table2[i * 5 + 2].position = Vector2f(x5, y5);
					table2[i * 5 + 2].color = Color::Green;
					table2[i * 5 + 3].position = Vector2f(x4, y4);
					table2[i * 5 + 3].color = Color::Red;
					table2[i * 5 + 4].position = Vector2f(x2, y2);
					table2[i * 5 + 4].color = Color::Yellow;
				}
				for (int i = 0; i < 1e8; i++) {

				}
				table_sz = table_sz * 5 - 4;
				table2[table_sz - 1] = table2[0];
				window.draw(table2);
				table = table2;
				window.display();
			}
		}
	}
	return 0;
}