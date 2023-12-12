#include "libs/dino/include/dino.hpp"
#include "libs/nn/include/MLP.hpp"
#include <string>

#ifndef Bot_H
#define Bot_H

namespace DinoAI {
/**
 * Bot class
 **/
class Bot : public Dino {
public:
  /**
   * Class constructor that takes the same parameters
   * as the superclass
   *
   * @see DinoAI::Dino
   **/
  NN::MLP *brain;
  Bot(int floorHeight, DinoTextures *textures);

  /**
   * Class constructor that takes a parent
   * object as reference
   *
   * @param parent The parent object
   */
  Bot(const Bot &parent);

  /**
   * Class constructor that takes the same parameters
   * as the superclass, and two filenames - those files being
   * both matrices of its brain.
   *
   * @param hiddenFile Filename of the hidden layer file
   * @param outFile Filename of the output layer file
   * @see DinoAI::Bot
   */
  Bot(std::string hiddenFile, std::string outFile, int floorHeight,
      DinoTextures *textures);

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