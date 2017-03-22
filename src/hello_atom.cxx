#include <SFML/Graphics.hpp>
#include <cassert>
#include <iostream>
#include "atom.h"
#include "elements.h"

int main(int argc, char *argv[]) {
    // require one argument
    if (argc != 2) {
        std::cout << "usage: hello_atom [atomic number]\n";
        return 1;
    }

    unsigned int Z = atoi(argv[1]);  // number of protons

    assert(Z <= 110 and Z > 0);  // make sure atomic number is within the limit

    // main window
    sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode()),
                            "Atom", sf::Style::Fullscreen);
    // the center of the main window
    const sf::Vector2f center =
        sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2);

    // atom settings
    const float radius = window.getSize().y / 4;
    Atom atom(Z, radius, center);

    // labels
    sf::Font font;
    sf::Text title, symbol;

    // set labels only it font is properly loaded
    if (font.loadFromFile("fonts/GlacialIndifference-Bold.otf")) {
        title = sf::Text(elements::name[Z - 1], font, radius / 5);
        symbol = sf::Text(elements::symbol[Z - 1], font,
                          atom.get_nucleus().getRadius() * 0.6);
        symbol.setColor(sf::Color::Black);
        // center symbol
        sf::FloatRect symbol_rect = symbol.getLocalBounds();
        symbol.setOrigin(symbol_rect.left + symbol_rect.width / 2.0f,
                         symbol_rect.top + symbol_rect.height / 2.0f);
        symbol.setPosition(center);
    }

    // repeat until closed
    while (window.isOpen()) {
        // process events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }

        window.clear();  // clear everything

        window.draw(atom.get_nucleus());  // render nucleus

        atom.update();  // update electrons positions

        // render electrons
        for (Electron *e : atom.get_electrons()) window.draw(e->get());

        window.draw(title);   // render title
        window.draw(symbol);  // render label

        window.display();  // show frame
    }

    return 0;
}