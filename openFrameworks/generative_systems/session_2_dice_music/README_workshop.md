# Generative_systems
Generative Systems for Art and Design course materials
 ©2020 Dan Buzzo
 www.buzzo.com

## 2 Dice music - Mozart and beyond

### Workshop 

* 1) roll a dice (d12) to choose 4 notes.
* 2) choose a measure length/tempo and arrange notes into this measure
* 3) make 3 new measures using the notes selected in 1) in any variation you choose.
* 4) make a probability matrix showing the probability of each measure being chosen after another one ( see the example matrix below)
* 5) play through your generative music rules for a randomly selected number of measures to see how your music sounds.

|  measure | A  |  B | C  |  D |
|---|---|---|---|---|
| A  | 0.25  | 0.25  | 0.25  |  0.25 |
| B  | 0.25  | 0.5  |  0.2 |  0.05 |
| C  |  1 |  0 |  0 |  0 |
| D  | 0.5  | 0.5  | 0  |  0 |



 * Each row in the matrix will equal 1.0, read next-measure probability across each row, depending upon current measure.

 ** in this example any measure is equally probably to follow measure A,
 measure B is most likely to follow measure b (50% of the time) with measure A next likely (25% and measure D least likely (5%)
 measure A will always follow measure C (100%)
 measure A or B will always follow measure D (50% each)
