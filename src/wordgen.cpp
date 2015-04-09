#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/clamp.hpp>

#include <markov/MarkovGenerator.h>
#include <markov/WordGeneratorFactory.h>


std::vector<std::string> trimSplit(const std::string &text,
                                   char delimiter = '\n')
{
  std::vector<std::string> elements;
  std::stringstream ss(text);
  std::string token;
  while (std::getline(ss, token, delimiter)) {
    boost::trim(token);
    if (!token.empty())
      elements.push_back(token);
  }
  return std::move(elements);
}


std::string readfile(const std::string& filename) {
  std::ifstream file(filename);
  if (!file.good()) {
    std::cerr << "Failed to open file: " << filename << std::endl;
    throw std::string("Aborted");
  }

  std::stringstream buffer;
  buffer << file.rdbuf();
  return std::move(buffer.str());
}


int main(int argc, char **argv)
{
  if (argc != 5) {
    std::cerr << "Invalid parameters." << std::endl
              << "Usage: "
              << argv[0] << " WORDFILE N N_init #GEN" << std::endl;
    std::cerr << "" << std::endl;
    std::cerr << "Max supported N is "
              << WordGeneratorFactory::MAX_ORDER << std::endl;
    return EXIT_FAILURE;
  }

  std::vector<std::string> args(argv, argv + argc);

  assert(args.size() == 5);
  int N = 0;
  int N_init = 0;
  int wordToGen = 0;
  try {
    N = boost::algorithm::clamp(static_cast<int>(std::atol(argv[2])),
                                1, WordGeneratorFactory::MAX_ORDER);
    N_init = static_cast<int>(std::atol(argv[3]));
    wordToGen = static_cast<int>(std::atol(argv[4]));
  } catch (...) {
    std::cerr << "Bad argument?" << std::endl;
  }

  // Create WordGenerator from factory
  Random::init();
  auto wg = WordGeneratorFactory::create(N, N_init);
  if (!wg) {
    std::cerr << "Failed to create WordGenerator object." << std::endl;
    std::cerr << "Bad paramters?" << std::endl;
    return EXIT_FAILURE;
  }

  wg->addInputWords(trimSplit(readfile(args[1])));
  wg->prepare();

  int tries = 0;
  int count = 0;

  std::unordered_set<std::string> newWords;
  while (count < wordToGen && tries < wordToGen * 10) {
    ++tries;
    std::string word = wg->generate();
    auto localListIt = newWords.find(word);
    if (!wg->isInputWord(word) && (localListIt == newWords.end())) {
      newWords.insert(word);
      word[0] = static_cast<char>(std::toupper(word[0]));
      std::cout << word << std::endl;
      ++count;
    }
  }
  return EXIT_SUCCESS;
}
