#include "SFML/Graphics/Rect.hpp"
#include "libs/dino/include/structures.hpp"
#include "libs/nn/include/MLP.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

#ifndef Dino_H
#define Dino_H

namespace DinoAI {
/**
 * Player class
 *
 * The AI bot will inherit this class, and override
 * the update function
 **/
class Dino {
private:
  DinoSprites sprites;
  DinoDimensions dimensions;

  sf::Vector2f position;
  float velocity;
  float acceleration;

public:
  DinoTextures* textures;
  sf::Rect<float> rect;

  bool isAlive;
  bool isSneaking;
  bool isJumping;
  int floorHeight;

  /**
   * Class constructor, that takes the floor y coordinate as its only parameter
   *
   * @param floorHeight scene's floor y coordinate
   */
  Dino(int floorHeight, DinoTextures* textures);
  Dino();

  /**
   * Update method - this method will be called in every frame during the game
   * loop
   */
  virtual void update();

  /**
   * Draw method
   *
   * Taking the game window as a parameter, it will render the dino's sprite on
   * the screen. The animation is made by checking the current frame
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
  void reborn();
};
}; // namespace DinoAI

#endif