/*! @file colors.h
 *  @brief Custom colors
 */
#ifndef COLORS_H
#define COLORS_H

#include <SFML/Graphics.hpp>

namespace colors {

static sf::Color orange(255, 97, 56);
static sf::Color grey(50, 50, 50);
// color used for electrons (5 orbits)
static sf::Color electrons[] = {sf::Color(255, 255, 157), sf::Color(190, 235, 159),
                         sf::Color(121, 189, 143), sf::Color(0, 163, 136),
                         sf::Color(0, 99, 83)};
}

#endif