#include "libs/dino/include/dino.hpp"
#include <SFML/Graphics.hpp>

#ifndef Obstacle_H
#define Obstacle_H

namespace DinoAI {
/**
 * Auxiliar struct to storage textures
 **/
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
/**
 * Obstacle class
 **/
class Obstacle {
private:
  ObstacleTextures textures;
  ObstacleSprites sprites;
  ObstacleDimensions dimensions;

  sf::Vector2f position;

  int floorHeight;
  int id;

public:
  sf::Rect<float> rect;
  Obstacle(int id, int floorHeight, int skyHeight);

  void update(float gameVelocity);
  void draw(sf::RenderWindow &window, int frame);
  bool collidedWithDino(DinoAI::Dino dino);

  sf::Vector2f getPosition();
};
}; // namespace DinoAI

#endif