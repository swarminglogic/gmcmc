#ifndef MARKOV_MARKOVGENERATORINTERFACE_H
#define MARKOV_MARKOVGENERATORINTERFACE_H

#include <memory>
#include <vector>


/**
 * MarkovGeneratorInterface class.
 *
 * This is the common interface for all classes made from the class
 * templates using this interface, e.g. MarkovGenerator
 *
 * MarkovGeneratorFactory creates appropriate type from dynamic values.
 *
 * @author SwarmingLogic (Roald Fernandez)
 */
template<typename T>
class MarkovGeneratorInterface
{
 public:
  virtual void addInputData(const std::vector<std::vector<T> >& data) = 0;
  virtual void prepare() = 0;
  virtual std::vector<T> generate() const = 0;
  virtual bool isInputData(const std::vector<T>& data) const = 0;
  virtual ~MarkovGeneratorInterface(){}
};

template<typename T>
using MarkovGeneratorPtr = std::unique_ptr<MarkovGeneratorInterface<T> >;


#endif  // MARKOV_MARKOVGENERATORINTERFACE_H
