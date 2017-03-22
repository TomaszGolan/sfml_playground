#ifndef ATOM_H
#define ATOM_H

#include <vector>
#include "electron.h"

/*! @brief An atom
 *
 * An atom is represented by a nucleus (CircleShape)
 * and the set of electrons moving around.
 */
class Atom {
   public:
    /*! @brief Atom constructor
     *
     *  Create a nucleus (CircleShape) and electrons moving around it.
     *
     *  @param Z mass number
     *  @param R atom radius
     *  @param center nucleus position
     */
    Atom(const unsigned int Z, const float R,
         const sf::Vector2f center = sf::Vector2f());

    ~Atom() {
        delete nucleus;
        for (Electron *e : electrons) delete e;
    }

    //! move electrons
    inline void update() {
        for (Electron *e : electrons) e->move();
    }

    //! get a nucleus
    inline sf::CircleShape get_nucleus() { return *nucleus; }

    //! get electrons
    inline const std::vector<Electron *> &get_electrons() const {
        return electrons;
    }

   private:
    const int Z;  //!< atomic number

    sf::CircleShape *nucleus;           //!< the nucleus of an atom
    std::vector<Electron *> electrons;  //!< electrons moving around nucleus

    static int max_orbits;      //!< the number of available orbits
    static int orbit_size[];    //!< the number of electrons on each orbit
    static int orbit_sums[];    //!< the sum of all electrons n first orbits

    //! get the number of orbits for this atom
    int nof_orbits();

    //! fill a single orbit with N electrons (uniformly distributed)
    void fill_orbit(const int N, const int orbit_id);
};

#endif