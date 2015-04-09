#ifndef UTIL_RANDOM_H
#define UTIL_RANDOM_H

#include <ctime>
#include <random>
#include <thread>

#include <util/Assert.h>


/**
 * Random class, for generating random values.
 * Currently not thread safe.
 *
 * @author SwarmingLogic (Roald Fernandez) (Roald Fernandez)
 */
class Random
{
 public:
  static float get() {
    return dist_(device_);
  }

  static float get(float min, float max) {
    std::uniform_real_distribution<float> dist(min, max);
    return dist(device_);
  }

  static bool getBool() {
    return get() > 0.5f;
  }

  static int getInt(int min, int max) {
    assert(min <= max);  // LCOV_EXCL_LINE
    std::uniform_int_distribution<int> dist(min, max);
    return dist(device_);
  }

  static void seed(const std::vector<size_t>&  s) {
    seed_ = s;
    std::seed_seq tmp(seed_.begin(), seed_.end());
    device_.seed(tmp);
  }

  static const std::vector<size_t>& seed() {
    return seed_;
  }

  static void init() {
    const auto time_seed = static_cast<size_t>(std::time(0));
    const auto clock_seed = static_cast<size_t>(std::clock());
    const size_t pid_seed =
        std::hash<std::thread::id>()(std::this_thread::get_id());
    seed({time_seed, clock_seed, pid_seed });
  }


  template<typename T>
  static typename T::value_type& getRandomElement(T& container) {
    return const_cast<typename T::value_type&>(
        getRandomElement(const_cast<const T&>(container)));
  }

  template<typename T>
  static const typename T::value_type& getRandomElement(const T& container) {
    assert(!container.empty());
    const int randomIndex =
        Random::getInt(0, static_cast<int>(container.size()) - 1);
    return container[randomIndex];
  }

 private:
  Random(){}
  ~Random();

  static std::mt19937 device_;
  static std::uniform_real_distribution<float> dist_;
  static std::vector<size_t> seed_;

  // NonCopyable
  Random(const Random& c);
  Random& operator=(const Random& c);
};

#endif  // MATH_RANDOM_H
