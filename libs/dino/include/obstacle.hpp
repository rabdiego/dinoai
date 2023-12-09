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

  /**
  * Class constructor
  * 
  * The id will determine which type of obstacle the object is, being:
  * 0 - Small Cactae
  * 1 - Medium Cactae
  * 2 - Large Cactae
  * 3 - Pterossaurus
  *
  * @param id The object id
  * @param floorHeight The y coordinate of the game's floor
  * @param skyHeight The height in which the pterossaurus objects will be above the ground
  *
  */
  Obstacle(int id, int floorHeight, int skyHeight);

  /**
  * Update method
  *
  * @param gameVelocity Current game velocity
  */
  void update(float gameVelocity);

  /**
  * Draw method
  *
  * @param window Game window
  * @param frame Current frame
  */
  void draw(sf::RenderWindow &window, int frame);

  /**
  * Method used to check collision with a Dino class object
  *
  * @param dino Dino object
  * @returns boolean telling if the obstacle collided with the dino
  */
  bool collidedWithDino(DinoAI::Dino dino);

  /**
  * Method used to get the obstacle's position
  *
  * @returns the obstacle's position
  */
  sf::Vector2f getPosition();
};
}; // namespace DinoAI

#endif