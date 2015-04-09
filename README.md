`gmcmc` General N-order Markov Chain Monte Carlo
--------------------------------------------------------------

A `C++` demonstration/implementation of a type-agnostic markov chain table generator,
together with random sampling to generate similar data (the monte carlo part).

This is designed to be completely agnostic to the data type it represents and
generates, and to be very easily extended to handle any custom type.

The concept is as following:

  1. I have set of data element sequences (e.g. set of letter-sequences (i.e. words))
  2. Generate more sequences that are similar (i.e. new words)

Keywords **`elements`** and **`sequences`** can be anything, as long as the following is true:

1. A sequence can be broken up into elements.
1. Elements can be put together to form a sequence.

To extend the code to support your own custom data type `T`, you only need to
write the logic for `sequence->{elements}`, and `{elements}->sequence`
transitions, where elements are of type `T`.


#### Examples

**Random sentence generator**

    (sequences, elements) = (sentences, words).

**Random word generator**

    (sequences, elements) = (words, letters)

However, by parsing syllables, it could also be:

    (sequences, elements) = (words, syllables)

**Random arpeggio generator**

    (sequences, elements) = (arpeggios, music-notes)


### Features

`N`-order: Supports any order (1, 2, ...). This is the size of the N-grams in
each markov chain node. In other words 'N previous elements should matter when
determining the next transition'.

`N_init`-order: Since many sequences have special starting properties, it us
possible specify that, when generating new random data, the first `N_init`
elements should match that of an input data sequence. As such, `N_init <= N`.


### Complexity

Assuming fixed average length of input sequences, perparing the markov chain
table from input data is `O(K lg K)`, where `K` is the number of input
sequences.

Generating a new sequence is `O(1)` average case.


### Compiling

Requirements:  `boost` headers, can be installed with your favourite package manager, e.g.:

`sudo apt-get install libboost-all-dev`

The basic example program is a word generator, and can be built with `SCons`:

First make sure scons will find boost by first calling `. scripts/initialize.sh` from the root
directory.

After that call `scons` from the root directory.

To cross-compile for windows, call `scons --win64`.

See other options with `scons --help`.

---

Alternatively:

```
g++ -o wordgen -std=c++11 -Wall src/wordgen.cpp src/markov/*.cpp \
    src/util/*.cpp -Isrc/ -isystem [BOOST_HEADER_PATH]
```