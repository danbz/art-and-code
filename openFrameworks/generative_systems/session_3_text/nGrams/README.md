# Generative_systems
Generative Systems for Art and Design course materials
 ©2020 Dan Buzzo
 www.buzzo.com

 Examples built in C++ using openFrameworks (openframeworks.cc)

## 3 Text and narrative
## nGram generator for text with Markov Chain text generator

* Techniques: text sorting, automatic and generative poetry, interactive story structure
* Ideas: Grammar and variation
* Demo: Markov chain text,

This example parses a body of text and generates ngrams of specified length, it then creates a 2D vector of grams and their following letters 

the system then generates a markov chain text of a specified length from a start gram.

### controls

'space' to process text into ngrams and generate new text
'l' to load text file of type .txt from disk as new source text
[!screenshot](screenshot-nGrams.png)