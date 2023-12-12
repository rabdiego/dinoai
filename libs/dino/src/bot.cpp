#include "libs/dino/include/bot.hpp"

using namespace DinoAI;

Bot::Bot(int floorHeight, DinoTextures *textures)
    : Dino(floorHeight, textures) {
  brain = new NN::MLP(7, 16, 3);
}

Bot::Bot(const Bot &parent) : Dino(parent.floorHeight, parent.textures) {
  brain = new NN::MLP(*parent.brain);
  brain->mutation(0.5);
}

Bot::Bot(std::string hiddenFile, std::string outFile, int floorHeight,
         DinoTextures *textures)
    : Bot(floorHeight, textures) {
  this->brain->load(hiddenFile, outFile);
}

void Bot::update(arma::mat input) {
  Dino::update();
  int action = brain->feedForward(input);

  if (isAlive) {
    switch (action) {
    case 0:
      if (!isJumping && !isSneaking) {
        jump();
      }
      break;
    case 1:
      if (!isJumping) {
        sneak();
      }
      break;
    case 2:
      if (isSneaking) {
        standUp();
      }
      break;
    default:
      break;
    }
  }
}