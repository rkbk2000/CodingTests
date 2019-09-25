Problem:

This is a Natural Language Processing (NLP) problem. Below is the algorithm used:
1. Read the inputs as a paragraph - a list of sentences
2. A set of 5 questions, and
3. A set of 5 answers

Now the paragraph is searched for the answers and the appropriate closest matching sentences are assigned to each answer.
Now the keywords are extracted (after removing stopwords) from the question and are matched with the complete answer sentence found previously.


Running the program

java wiki.Wiki <Input file>

For E.g.
java wiki.Wiki wiki/input.txt

A sample output generated from the execution:
Grévy's zebra and the mountain zebra
aims to breed zebras that are phenotypically similar to the quagga
horses and donkeys
the plains zebra, the Grévy's zebra and the mountain zebra
subgenus Hippotigris

