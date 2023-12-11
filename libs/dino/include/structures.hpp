#include <SFML/Graphics.hpp>

#ifndef Structures_H
#define Structures_H

namespace DinoAI {
typedef struct {
  sf::Texture walking1;
  sf::Texture walking2;
  sf::Texture sneaking1;
  sf::Texture sneaking2;
  sf::Texture dead;
} DinoTextures;

/**
 * Auxiliar struct to storage sprites
 **/
typedef struct {
  sf::Sprite walking1;
  sf::Sprite walking2;
  sf::Sprite sneaking1;
  sf::Sprite sneaking2;
  sf::Sprite dead;
} DinoSprites;

/**
 * Auxiliar struct to storage texture dimensions
 **/
typedef struct {
  sf::Vector2u walking;
  sf::Vector2u sneaking;
  sf::Vector2u dead;
} DinoDimensions;

typedef struct {
  sf::Texture cactae1;
  sf::Texture cactae2;
  sf::Texture cactae3;
  sf::Texture ptero1;
  sf::Texture ptero2;
} ObstacleTextures;

/**
 * Auxiliar struct to storage sprites
 **/
typedef struct {
  sf::Sprite cactae1;
  sf::Sprite cactae2;
  sf::Sprite cactae3;
  sf::Sprite ptero1;
  sf::Sprite ptero2;
} ObstacleSprites;

/**
 * Auxiliar struct to storage texture dimensions
 **/
typedef struct {
  sf::Vector2u cactae1;
  sf::Vector2u cactae2;
  sf::Vector2u cactae3;
  sf::Vector2u ptero;
} ObstacleDimensions;
};

#endif