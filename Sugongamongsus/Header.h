#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <SFML/Graphics.hpp>

using std::vector;
typedef std::string str;
typedef sf::Vector2f vec2;

sf::Color hsv(int hue, float sat, float val)
{
	// https://en.sfml-dev.org/forums/index.php?topic=7313.0
	hue %= 360;
	while (hue < 0) hue += 360;

	if (sat < 0.f) sat = 0.f;
	if (sat > 1.f) sat = 1.f;

	if (val < 0.f) val = 0.f;
	if (val > 1.f) val = 1.f;

	int h = hue / 60;
	float f = float(hue) / 60 - h;
	float p = val * (1.f - sat);
	float q = val * (1.f - sat * f);
	float t = val * (1.f - sat * (1 - f));

	switch (h)
	{
	default:
	case 0:
	case 6: return sf::Color(val * 255, t * 255, p * 255);
	case 1: return sf::Color(q * 255, val * 255, p * 255);
	case 2: return sf::Color(p * 255, val * 255, t * 255);
	case 3: return sf::Color(p * 255, q * 255, val * 255);
	case 4: return sf::Color(t * 255, p * 255, val * 255);
	case 5: return sf::Color(val * 255, p * 255, q * 255);
	}
}

str readFile(str name) {
	std::ifstream t(name);
	std::stringstream buffer;
	buffer << t.rdbuf();
	return buffer.str();
}

void print(vec2 v) {
	printf("%.2f, %.2f\n", v.x, v.y);
}

vec2 scale(vec2 in) {
	return vec2(in.x * 217.14 - 3074, 1200 - (in.y * 260 - 11600));
}

class Subdivision {
public:
	str name;
	vector<vec2> vertices;
	Subdivision(str name) : name(name)
	{

	}
	~Subdivision() {

	}
	sf::ConvexShape getShape() {
		sf::ConvexShape convex;
		convex.setPointCount(vertices.size());

		for (int i = 0; i < vertices.size(); i++) {
			convex.setPoint(i, scale(vertices[i]));
			//print(convex.getPoint(i));
		}

		return convex;
	}
};

class Country {
public:
	str name;
	vector<Subdivision*> subdivisions;
	Country() {

	}
	~Country() {
		
	}
	static Country parse(str name) {
		std::istringstream content(readFile(name));
		Country result = Country();
		Subdivision* buffer = nullptr;

		for (str line; std::getline(content, line); )
		{
			int pos = line.find(":");
			str p1 = line.substr(0, pos);
			str p2 = line.substr(pos + 1);

			if (p1 == "sub") {
				if (buffer != nullptr) { // if another subdiv is buffered, put it in
					result.subdivisions.push_back(buffer);
				}
				buffer = new Subdivision(p2);
				buffer->name = p2;
			}
			else if (p1 == "end") {
				result.name = p2;
				result.subdivisions.push_back(buffer); // push the last one in
			}
			else {
				auto v = vec2(std::stof(p1), std::stof(p2));
				buffer->vertices.push_back(v);
			}
		}
		return result;
	}
};