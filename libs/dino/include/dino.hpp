#include "libs/nn/include/MLP.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

#ifndef Dino_H
#define Dino_H

namespace DinoAI {
/**
 * Auxiliar struct to storage textures
 **/
typedef struct {
  sf::Texture walking1;
  sf::Texture walking2;
  sf::Texture sneaking1;
  sf::Texture sneaking2;
  sf::Texture dead;
} Textures;

/**
 * Auxiliar struct to storage sprites
 **/
typedef struct {
  sf::Sprite walking1;
  sf::Sprite walking2;
  sf::Sprite sneaking1;
  sf::Sprite sneaking2;
  sf::Sprite dead;
} Sprites;

/**
 * Auxiliar struct to storage texture dimensions
 **/
typedef struct {
  sf::Vector2u walking;
  sf::Vector2u sneaking;
  sf::Vector2u dead;
} Dimensions;

/**
  * Player class
  *
  * The AI bot will inherit this class, and override
  * the update function
  **/
class Dino {
private:
  Textures textures;
  Sprites sprites;
  Dimensions dimensions;

  sf::Vector2f position;
  float velocity;
  float acceleration;

  int floorHeight;

public:
  bool isAlive;
  bool isSneaking;
  bool isJumping;

  /**
  * Class constructor, that takes the floor y coordinate as its only parameter
  *
  * @param floorHeight scene's floor y coordinate
  */
  Dino(int floorHeight);

  /**
  * Update method - this method will be called in every frame during the game loop
  */
  void update();

  /**
  * Draw method
  *
  * Taking the game window as a parameter, it will render the dino's sprite on the screen.
  * The animation is made by checking the current frame
  *
  * @param window the game window
  * @param frame the current frame
  */
  void draw(sf::RenderWindow &window, int frame);

  // The following methods are the dino's actions
  void jump();
  void sneak();
  void standUp();
  void die();
};
}; // namespace DinoAI

#endif