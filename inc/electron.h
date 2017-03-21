#ifndef ELECTRON_H
#define ELECTRON_H

#define PI 3.14159265

#include <SFML/Graphics.hpp>
#include <cmath>

/*! @brief A circulating electron
 *
 * An electron is represented by a circle of a radius r
 * moving around a circle of a radius R.
 */
class Electron {
   public:
    /*! @brief Electron contructor
     *
     *  Setup initial values for an electron radius, a circle radius and the
     *  center of the circle. Create a circle representing the electron.
     *
     *  @param r The radius of an electron
     *  @param R The radius of a circle
     *  @param center The center a circle
     *  @param angle The initial position of an electron
     */
    Electron(const float r, const float R,
             const sf::Vector2f center = sf::Vector2f(), const float angle = 0,
             const float speed = 1)
        : R(R), angle(angle), center(center), speed(speed) {
        // create an electron
        electron = new sf::CircleShape(r);
        // set initial position
        electron->setOrigin(r, r);
        set_position();
    }

    //! Electron destructor
    ~Electron() { delete electron; }

    //! update a circle radius
    inline void set_circle_r(const float radius) { R = radius; }
    //! update the center of a circle
    inline void set_origin(const sf::Vector2f c) { center = c; }
    //! update the position of an electron
    inline void set_position() {
        electron->setPosition(center.x + R * cos(angle * PI / 180),
                              center.y + R * sin(angle * PI / 180));
    }
    //! update an electron position
    inline void move() {
        angle += speed * 0.1;  // so speed=1 is optimal TODO: use frame time
        set_position();
    }
    //! change color
    inline void set_color(sf::Color c) { electron->setFillColor(c); }
    //! get an electron
    inline sf::CircleShape get() { return *electron; }

   private:
    float R;              //!< the radius of a cricle electron is moving around
    float angle;          //!< the current position of an electron
    float speed;          //!< factor to multiply angle when move
    sf::Vector2f center;  //!< the center of a circle electron is moving around
    sf::CircleShape *electron;  //!< the circle shape representing an electron
};

#endif