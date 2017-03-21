#include <SFML/Graphics.hpp>
#include <iostream>
#include "atom.h"

int main(int argc, char* argv[]) {
    // require one argument
    if (argc != 2) {
        std::cout << "usage: hello_atom [atomic number]\n";
        return 1;
    }

    unsigned int Z = atoi(argv[1]);  // number of protons

    // main window
    sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode()),
                            "Atom", sf::Style::Fullscreen);
    // the center of the main window
    const sf::Vector2f center =
        sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2);

    // atom settings
    const float radius = window.getSize().y / 4;
    Atom* atom = new Atom(Z, radius, center);

    // repeat until closed
    while (window.isOpen()) {
        // process events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }

        window.clear();                    // clear everything
        atom->update();                    // update electrons positions
        window.draw(atom->get_nucleus());  // render nucleus
        // render electrons
        for (Electron* e : atom->electrons) window.draw(e->get());

        window.display();  // show frame
    }

    delete atom;

    return 0;
}