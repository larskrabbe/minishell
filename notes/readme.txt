Hey this folder is for planing and keeping notes and links related to this project

the allowed funktion is just a list of funktion we can use with a basic  explanation about them 

download the vs extension draw.io and pdf viewer to use the files inside of this folder
also i use the better comments extension for my comments

Good entry information about the project (its  the pdf inside of this folder)
https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf

shell syntax ( could be useful for the tokenizer(didn't read it yet))
https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html

The dargon book (could be useful but will only look in to it if i get stuck)
Compilers: Principles, Techniques, and Tools


< -> uses a file as import 
<< STR -> uses multipel lines input until the  STR is used as  a input 
	NOTE: can't have whitespace or any other char infront of it. anly the STR itself.
	The "-" flag (<<-) ignores whitespace in this cae 
> -> creates or overwrite a file as a output
>> -> creates or appends a file as a ouput


some ideas for diffrent ways to 'tokenize'(maybe combi with parser )
-simple string change: change the str or a dubversion of it  where at the start and end of every token there will be a special char like < and >  or "" etc
-location saving: simple  save the start maybe the end of  each token in a array(int or struct). can stored in the stack or heap once and be reused for multipel execution
-store in struct: for each token create use a new struct to safe the string of the token. uses a array or pointer inside of the token to "chain" them together. easy to expent later o. most likely best incase of empty cat and *wildcard, easy to add the chain 
-don't tokenize at all: simple at the beginning but can get harder after


inside of the parser i will check for wildcards and envar
the parser will allocated a string take care of it 


to care for
!! leaks : no reason to say why
multiple flags : need to takare of invaleach flaggs ("echo -n -n -n hello "-> just "hello" and the -n flag once)
flags are tested in the builtins not in the parser 
empty cat : ask for valid file also look for cat and | combination
wildcards in tokenizer: 
executable and builins and flag inside of Qutationmarks: so there is a order of tokentypes (for example "exe" "flag" "arg1" "arg2")
cat execute one file after another: example "cat" "file1" "file2" first file1 will be printed the file2
capilisation for executable and builtins