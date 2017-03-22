#include <SFML/Graphics.hpp>
#include "atom.h"
#include "elements.h"

// draw nucleus and all electrons
void draw(Atom *atom, sf::RenderWindow &window);
// update origin to be at the center
void center_origin(sf::Text &text);
// change the origin to center bottom
void bottom_origin(sf::Text &text);

int main() {
    int Z = 8;  // initial atomic number

    // main window
    sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode()),
                            "Atom", sf::Style::Fullscreen);
    // the center of the main window
    const sf::Vector2f center =
        sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2);

    // atom settings
    const float radius = window.getSize().y / 4;
    Atom *atom = new Atom(Z, radius, center);

    // labels
    sf::Font font;
    sf::Text title, symbol, help;

    // set labels only it font is properly loaded
    if (font.loadFromFile("fonts/GlacialIndifference-Bold.otf")) {
        // title
        title = sf::Text(elements::name[Z - 1], font, radius / 5);
        // symbol
        symbol = sf::Text(elements::symbol[Z - 1], font,
                          atom->get_nucleus().getRadius() * 0.6);
        symbol.setColor(sf::Color::Black);
        center_origin(symbol);
        symbol.setPosition(center);
        // help
        help =
            sf::Text("up/down - switch elements, q - quit\n", font, radius / 6);
        bottom_origin(help);
        help.setPosition(window.getSize().x / 2, window.getSize().y);
        sf::Color temp(255, 255, 255, 50);
        help.setColor(temp);
    }

    // repeat until closed
    while (window.isOpen()) {
        // process events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed) {
                // update atomic number (or quit on q)
                switch (event.key.code) {
                    case sf::Keyboard::Up:
                        Z = ++Z > 110 ? 1 : Z;
                        break;
                    case sf::Keyboard::Down:
                        Z = --Z < 1 ? 110 : Z;
                        break;
                    case sf::Keyboard::Q:
                        window.close();
                    default:
                        continue;
                }
                // recreate the atom
                delete atom;
                atom = new Atom(Z, radius, center);
                // update title
                title.setString(elements::name[Z - 1]);
                // update symbol
                symbol.setString(elements::symbol[Z - 1]);
                symbol.setCharacterSize(atom->get_nucleus().getRadius() * 0.6);
                center_origin(symbol);
            }
        }

        window.clear();  // clear everything

        draw(atom, window);  // render atom

        window.draw(title);   // render title
        window.draw(symbol);  // render label
        window.draw(help);    // render help

        window.display();  // show frame
    }
    delete atom;

    return 0;
}

void draw(Atom *atom, sf::RenderWindow &window) {
    // render nucleus
    window.draw(atom->get_nucleus());
    // update electrons positions
    atom->update();
    // render electrons
    for (Electron *e : atom->get_electrons()) window.draw(e->get());
}

void center_origin(sf::Text &text) {
    sf::FloatRect text_rect = text.getLocalBounds();
    text.setOrigin(text_rect.left + text_rect.width / 2.0f,
                   text_rect.top + text_rect.height / 2.0f);
}

void bottom_origin(sf::Text &text) {
    sf::FloatRect text_rect = text.getLocalBounds();
    text.setOrigin(text_rect.left + text_rect.width / 2,
                   text_rect.top + text_rect.height);
}