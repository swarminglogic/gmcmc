#ifndef MARKOV_WORDGENERATORFACTORY_H
#define MARKOV_WORDGENERATORFACTORY_H

#include <markov/WordGeneratorInterface.h>


/**
 * WordGeneratorFactory class.
 *
 * @author SwarmingLogic (Roald Fernandez)
 */
class WordGeneratorFactory
{
 public:

  /**
   * Create a word generator with specified depth N, and initial-key depth of
   * N_init.
   *
   * Requirements:
   *   1 <= N <= WordGeneratorInterface::MAX_ORDER
   *   1 <= N_init <= N
   */
  static WordGeneratorPtr create(int N, int N_init);

  static const int MAX_ORDER = 6;

  // TODO swarminglogic, 2015-03-21:
  // /**
  //  * Uses a provided input list and generates a prepared word generator list
  //  * with good values for N and N_init, based on the number of input word
  //  * entries, and average entry length.
  //  */
  // static WordGeneratorPtr create(const std::vector<std::string>& words);

 private:
  // Static class
  WordGeneratorFactory();
};

#endif  // MARKOV_WORDGENERATORFACTORY_H
