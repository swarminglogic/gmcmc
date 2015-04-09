#ifndef MARKOV_WORDGENERATOR_H
#define MARKOV_WORDGENERATOR_H

#include <boost/algorithm/string.hpp>

#include <markov/MarkovGenerator.h>
#include <markov/WordGeneratorInterface.h>


/**
 * WordGenerator class.
 *
 * This is a specialization of the MarkovGenerator for generating random words.
 * It functions as a mapping between vector<char> and string, as well as the
 * logic for sanitizing input data.
 *
 * @author SwarmingLogic (Roald Fernandez)
 */
template<int N>
class WordGenerator : public WordGeneratorInterface
{
 public:
  explicit WordGenerator(int N_init = 0) : markov_(N_init) {}
  virtual ~WordGenerator(){}

  virtual void addInputWords(const std::vector<std::string>& words) {
    std::vector<std::vector<char> > inputWords;
    for (const auto& word : words)
      inputWords.push_back(prepareInputWord(word));
    markov_.addInputData(inputWords);
  }

  virtual void prepare() {
    markov_.prepare();
  }

  virtual std::string generate() const {
    const std::vector<char> word = markov_.generate();
    return std::string(word.begin(), word.end());
  }

  virtual bool isInputWord(const std::string& word) const {
    return markov_.isInputData(prepareInputWord(word));
  }

  WordGenerator(const WordGenerator& c) = delete;
  WordGenerator& operator=(const WordGenerator& c) = delete;

 private:
  std::vector<char> prepareInputWord(const std::string& word) const
  {
    auto trimmed = boost::trim_copy(word);
    return std::vector<char>(trimmed.begin(), trimmed.end());
  }

  MarkovGenerator<N, char> markov_;
};


#endif  // MARKOV_WORDGENERATOR_H
