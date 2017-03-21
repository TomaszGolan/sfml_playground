#include <SFML/Graphics.hpp>
#include "electron.h"

float Electron::step = 0.001;

int main() {
    // main window
    sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode()),
                            "Atom", sf::Style::Fullscreen);
    // the center of the main window
    const sf::Vector2f center =
        sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2);

    // electron settings
    const float radius = window.getSize().x / 50;
    Electron *e = new Electron(radius, 10*radius, center);

    // repeat until closed
    while (window.isOpen()) {
        // process events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }

        window.clear();         // clear everything
        e->move();              // update electron position
        window.draw(e->get());  // render electron
        window.display();       // show frame
    }

    return 0;
}