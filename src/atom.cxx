#include "atom.h"
#include <random>

int Atom::max_orbits = 5;
int Atom::orbit_size[] = {2, 8, 18, 32, 50};
int Atom::orbit_sums[] = {2, 10, 28, 60, 110};
sf::Color Atom::colors[] = {sf::Color(255, 255, 157), sf::Color(190, 235, 159),
                            sf::Color(121, 189, 143), sf::Color(0, 163, 136),
                            sf::Color(0, 99, 83),     sf::Color(255, 97, 56)};

Atom::Atom(const unsigned int Z, const float R, const sf::Vector2f center)
    : Z(Z) {
    // the size of the nucleus based on the number of electrons (orbits)
    // so it the whole atom fit within R
    const float nucleus_radius = R / (nof_orbits() + 1);

    // create a nucleus and put in the center
    nucleus = new sf::CircleShape(nucleus_radius, 64);
    nucleus->setOrigin(nucleus_radius, nucleus_radius);
    nucleus->setPosition(center);
    nucleus->setFillColor(colors[max_orbits]);

    int nof_electrons = Z;
    int current_orbit = 0;

    while (nof_electrons > 0) {
        const int N = std::min(nof_electrons, orbit_size[current_orbit]);
        fill_orbit(N, current_orbit);
        nof_electrons -= N;
        current_orbit++;
    }
}

int Atom::nof_orbits() {
    // check if the number of electrons is large enough to fill several orbits
    for (int i = max_orbits - 2; i >= 0; i--)
        if (Z > orbit_sums[i]) return i + 2;
    // no, it is not
    return 1;
}

void Atom::fill_orbit(const int N, const int orbit_id) {
    // init random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 360);

    const float R = nucleus->getRadius() * (orbit_id + 2);  // orbit radius
    const float angle_step = 360.0 / N;    // distance between electrons
    const float initial_angle = dis(gen);  // the position of the first electron
    const float electron_r = nucleus->getRadius() / 5;  // electron radius
    const int direction = orbit_id % 2 ? 1 : -1;        // just for fun

    for (unsigned int i = 0; i < N; i++) {
        Electron* e = new Electron(electron_r, R, nucleus->getPosition(),
                                   initial_angle + i * angle_step,
                                   direction / (orbit_id + 1.));
        e->set_color(colors[orbit_id]);
        electrons.push_back(e);
    }
}
