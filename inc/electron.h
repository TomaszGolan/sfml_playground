#ifndef ELECTRON_H
#define ELECTRON_H

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
             const sf::Vector2f center = sf::Vector2f(), const float angle = 0)
        : r(r), R(R), angle(angle), center(center) {
        // create an electron
        electron = new sf::CircleShape(r);
        // set initial position
        electron->setOrigin(0, 0);
        set_position();
    }

    //! Electron destructor
    ~Electron() { delete electron; }

    //! update an electron radius
    inline void set_electron_r(const float radius) { r = radius; }
    //! update a circle radius
    inline void set_circle_r(const float radius) { R = radius; }
    //! update the center of a circle
    inline void set_origin(const sf::Vector2f c) { center = c; }
    //! update the position of an electron
    inline void set_position() {
        electron->setPosition(center.x + R * cos(angle),
                              center.y + R * sin(angle));
    }
    //! update an electron position
    inline void move() {
        angle += step;
        set_position();
    }
    //! get an electron
    inline sf::CircleShape get() { return *electron; }

   private:
    float r;              //!< the radius of an electron
    float R;              //!< the radius of a cricle electron is moving around
    float angle;          //!< the current position of an electron
    sf::Vector2f center;  //!< the center of a circle electron is moving around
    sf::CircleShape *electron;  //!< the circle shape representing an electron

    static float step;  //!< the angle increase in each step
};

#endif