#include <armadillo>

#ifndef MLP_H
#define MLP_H

namespace NN {
class MLP {
private:
  int num_input_neurons;
  int num_hidden_neurons;
  int num_output_neurons;

  arma::mat hidden_weights;
  arma::mat output_weights;

  arma::mat sigmoid(arma::mat input) const;

public:
  MLP(int num_input_neurons, int num_hidden_neurons, int num_output_neurons);
  MLP(const MLP &parent);

  void mutation(double factor);
  double feedForward(arma::mat input) const;

  arma::mat getHiddenWeights() const;
  arma::mat getOutputWeights() const;

  int getNumInputNeurons() const;
  int getNumHiddenNeurons() const;
  int getNumOutputNeurons() const;
};
}; // namespace NN

#endif