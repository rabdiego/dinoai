#include "libs/nn/include/MLP.hpp"

using namespace NN;

arma::mat MLP::sigmoid(arma::mat input) const {
  return 1 / (1 + arma::mat(-input));
}

MLP::MLP(int num_input_neurons, int num_hidden_neurons,
         int num_output_neurons) {
  this->num_input_neurons = num_input_neurons;
  this->num_hidden_neurons = num_hidden_neurons;
  this->num_output_neurons = num_output_neurons;

  arma::arma_rng::set_seed_random();

  this->hidden_weights =
      arma::mat(num_hidden_neurons, num_input_neurons).randn();
  this->output_weights =
      arma::mat(num_output_neurons, num_hidden_neurons).randn();
}

MLP::MLP(const MLP &parent) {
  this->num_input_neurons = parent.getNumInputNeurons();
  this->num_hidden_neurons = parent.getNumHiddenNeurons();
  this->num_output_neurons = parent.getNumOutputNeurons();

  this->hidden_weights = parent.getHiddenWeights();
  this->output_weights = parent.getOutputWeights();
}

void MLP::mutation(double factor) {
  arma::mat hidden_mutation =
      factor *
      arma::mat(this->num_hidden_neurons, this->num_input_neurons).randn();
  arma::mat output_mutation =
      factor *
      arma::mat(this->num_output_neurons, this->num_hidden_neurons).randn();

  this->hidden_weights += hidden_mutation;
  this->output_weights += output_mutation;
}

int MLP::feedForward(arma::mat input) const {
  arma::mat hidden_vector = this->sigmoid(this->hidden_weights * input);
  arma::mat output_vector = this->output_weights * hidden_vector;
  return (int)output_vector(output_vector.index_max());
}

arma::mat MLP::getHiddenWeights() const { return this->hidden_weights; }

arma::mat MLP::getOutputWeights() const { return this->output_weights; }

int MLP::getNumInputNeurons() const { return this->num_input_neurons; }

int MLP::getNumHiddenNeurons() const { return this->num_hidden_neurons; }

int MLP::getNumOutputNeurons() const { return this->num_output_neurons; }

void MLP::load(std::string hiddenFile, std::string outFile) {
  this->hidden_weights.load(hiddenFile);
  this->output_weights.load(outFile);
}

void MLP::save(std::string hiddenFile, std::string outFile) {
  this->hidden_weights.save(hiddenFile);
  this->output_weights.save(outFile);
}