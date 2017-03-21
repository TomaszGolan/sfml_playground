#include <SFML/Graphics.hpp>

int main() {
    // create the main window
    // RenderWindow(VideoMode mode, const String &title)
    // VideoMode(unsigned int modeWidth, unsigned int modeHeight)
    sf::RenderWindow window(sf::VideoMode(400, 400), "Hello World!");
    // create a rectangle
    // RectangleShape (const Vector2f &size=Vector2f(0, 0))
    sf::RectangleShape rect(sf::Vector2f(100, 100));
    // put the rectangle at the center of the window
    rect.setOrigin(50, 50);      // origin at the center of the rectangle
    rect.setPosition(200, 200);  // origin position at the center of the window

    // start the main loop
    while (window.isOpen()) {
        // create an event
        sf::Event event;
        // process the event
        while (window.pollEvent(event)) {
            // action depends on event type
            if (event.type == sf::Event::Closed) {
                window.close();  // close when closed
            } else if (event.type == sf::Event::MouseWheelScrolled) {
                rect.rotate(1);  // rotate the rectangle on moue wheel
            }
        }

        window.clear();     // clear everything
        window.draw(rect);  // render rectangle
        window.display();   // show frame
    }

    return 0;
}