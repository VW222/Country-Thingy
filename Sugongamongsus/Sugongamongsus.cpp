#include "Header.h"

int main()
{
    sf::ContextSettings confSett;
    confSett.antialiasingLevel = 8.0;
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!", sf::Style::Default, confSett);
    Country hun = Country::parse("Hungolia.geo222");
    Country svk = Country::parse("Slovakia.geo222");
    Country rom = Country::parse("Romania.geo222");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        for (int i = 0; i < hun.subdivisions.size(); i++) {
            sf::ConvexShape t = hun.subdivisions[i]->getShape();
            t.setFillColor(hsv((360 / hun.subdivisions.size()) * i, 1.f, 1.f));
            window.draw(t);
        }

        for (int i = 0; i < svk.subdivisions.size(); i++) {
            sf::ConvexShape t = svk.subdivisions[i]->getShape();
            t.setFillColor(hsv((360 / svk.subdivisions.size()) * (i + 1), 1.f, 1.f));
            window.draw(t);
        }

        for (int i = 0; i < rom.subdivisions.size(); i++) {
            sf::ConvexShape t = rom.subdivisions[i]->getShape();
            t.setFillColor(hsv((360 / rom.subdivisions.size()) * (i + 1), 1.f, 1.f));
            window.draw(t);
        }
        window.display();
    }

    return 0;
}