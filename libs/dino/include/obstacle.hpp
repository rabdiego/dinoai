#include "libs/dino/include/dino.hpp"
#include "libs/dino/include/structures.hpp"
#include <SFML/Graphics.hpp>

#ifndef Obstacle_H
#define Obstacle_H

namespace DinoAI {
/**
 * Obstacle class
 **/
class Obstacle {
private:
  ObstacleTextures* textures;
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
  Obstacle(int id, int floorHeight, int skyHeight, ObstacleTextures* textures);

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
  bool collidedWithDino(DinoAI::Dino dino) const;

  /**
  * Method used to get the obstacle's position
  *
  * @returns the obstacle's position
  */
  sf::Vector2f getPosition() const;
};
}; // namespace DinoAI

#endif