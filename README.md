# Wordle guesser
 A program that guesses wordle words by brute forcing a list of given words and certain patterns and saves them in a file.  
 The first argument has to be the file with the list of the words. It can be a previous solution file.  
 Flags have to be followed by a sequence of characters. If the character is a '.' (dot) the program will interpret it as any character:  
 - -g (green). The letters following this flag are in the word in the order specified. For example, "f..es" is in "files".
 - -y (yellow). The letters following this flag are in the word but not in the positions specified. For example, "tsreo" identifies "store".
 - -b (black). The letters following this flag are not in the word. For example, "pkjql" identifies "words".
 - -p (print). Print the output of the solution to the console.
 
 Not putting enough characters in the pattern does not matter. "rig" is the same as "rig..".  
 Compile with "gcc guess.c -lunac".  
 "words.txt" is a list of (supposedly, I haven't checked) all spanish words that are 5 letters long.  
