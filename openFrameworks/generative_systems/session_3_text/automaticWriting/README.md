# Generative_systems
Generative Systems for Art and Design course materials
 ©2020 Dan Buzzo
 www.buzzo.com

 Examples built in C++ using openFrameworks (openframeworks.cc)

## 3 Text and narrative
## automatic writing: a very simple linguistic parsing tree example

* Techniques: text sorting, automatic and generative poetry, interactive story structure
* Ideas: Grammar and variation
* Demo: tree parsing text

this simple example loads lexicons of parts of speech (noun, verb, adjective etc) and constructs gramatically correct (sometimes...) sentences based upon a simple set of sentence construction rules.

This system is similar to much more complex ones used in areas of 'computational linguistics' and is often used in reverse with text analysis of existing writing or speech to generate hidden markov models from corpuses of speech. Lexicons are stored in a 2D vector 'textParts' that we parse based upon orders of 'parts of speech' in a vector of sentence structures 'textStructure'


### controls

'space' to process lexicons into sentences and generate new text

* https://en.wikipedia.org/wiki/Phrase_structure_grammar
* https://www.linkedin.com/pulse/introduction-language-modeling-n-grams-markov-chains-john-backes


### dependencies
* ofxTextSuite https://github.com/Furkanzmc/ofxTextSuite

![screenshot](screenshot-automaticWriting.png)