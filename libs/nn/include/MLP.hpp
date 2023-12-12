#include <armadillo>
#include <string>

#ifndef MLP_H
#define MLP_H

namespace NN {

/**
 * Representation of a Multi Layer Perceptron
 *
 */
class MLP {
private:
  int num_input_neurons;
  int num_hidden_neurons;
  int num_output_neurons;

  arma::mat hidden_weights;
  arma::mat output_weights;

  /**
   * Implementation of the sigmoid activation function
   *
   * Recall that the sigmoid function is defined as:
   * sigma(x) = 1/(1 + exp(-x))
   *
   * @param input an armadillo matrix A
   * @return the matrix A after the sigmoid operation
   */
  arma::mat sigmoid(arma::mat input) const;

public:
  /**
   * Class constructor by taking the number of input, hidden and output neurons.
   *
   * @param num_input_neurons the number of input neurons
   * @param num_hidden_neurons the number of hidden neurons
   * @param num_output_neurons the number of output neurons
   */
  MLP(int num_input_neurons, int num_hidden_neurons, int num_output_neurons);

  /**
   * Class constructor by taking another MLP object
   *
   * The object data will be copied from that MLP object,
   * which we call it parent
   *
   * @param parent the parent MLP object
   */
  MLP(const MLP &parent);

  /**
   * Mutation mechanism
   *
   * Recall that, for this project, what we call as
   * mutation is the random noise added to all of
   * the MLP weights
   *
   * @param factor a controlling factor of how much the noise will impact the
   * model's weight
   */
  void mutation(double factor);

  /**
   * Feed forward algorithm implementation
   *
   * @param input an armadillo matrix (that is conceptually a vector)
   */
  int feedForward(arma::mat input) const;

  // Getters and setters

  arma::mat getHiddenWeights() const;
  arma::mat getOutputWeights() const;

  int getNumInputNeurons() const;
  int getNumHiddenNeurons() const;
  int getNumOutputNeurons() const;

  /**
   * Save its information on two files:
   * One for the hidden layer, and the other
   * for the output layer.
   *
   * @param hiddenFile Filename of the hidden layer file
   * @param outFile Filename of the output layer file
   */
  void save(std::string hiddenFile, std::string outFile);

  /**
   * Loads its information from two files:
   * One for the hidden layer, and the other
   * for the output layer.
   *
   * @param hiddenFile Filename of the hidden layer file
   * @param outFile Filename of the output layer file
   */
  void load(std::string hiddenFile, std::string outFile);
};
}; // namespace NN

#endif