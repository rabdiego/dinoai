#include "libs/dino/include/dino.hpp"
#include "libs/nn/include/MLP.hpp"

#ifndef Bot_H
#define Bot_H

namespace DinoAI {
class Bot : public Dino {
private:
  NN::MLP* brain;

public:
  Bot(int floorHeight);
  Bot(const Bot &parent);

  void update(arma::mat input);
};
}; // namespace DinoAI

#endif