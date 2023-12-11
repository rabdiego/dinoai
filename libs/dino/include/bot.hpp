#include "libs/dino/include/dino.hpp"
#include "libs/nn/include/MLP.hpp"

#ifndef Bot_H
#define Bot_H

namespace DinoAI {
/**
 * Bot class
 **/
class Bot : public Dino {
private:
  NN::MLP *brain;

public:
  /**
  * Class constructor that takes the same parameters
  * as the superclass
  *
  * @see DinoAI::Dino
  **/
  Bot(int floorHeight, DinoTextures *textures);

  /**
  * Class constructor that takes a parent
  * object as reference
  *
  * @param parent The parent object
  */
  Bot(const Bot &parent);

  /**
  * The update method, modified to take a vector
  * of information about the game as an input
  *
  * @param input A vector
  * @see DinoAI::Dino::update()
  **/
  void update(arma::mat input);
};
}; // namespace DinoAI

#endif