# Blackjack
Simple Blackjack game in C++.
Used C++ because it's the language that I'm the most familiar with.

Run the game:

g++ -Wall -W -o main main.cpp

./mian seed

Test Cases:
1.
base) ScarlettdeMacBook-Pro-6:Blackjack scarlett$ ./main 10

Welcome! Let's play blackjack together!

My Hand Cards: ? 2-S

Your Hand Cards: 5-H 5-C 

Please enter 'h' to hit and 's' to stay: h

Your Hand Card: 5-H 5-C 9-C 

Oh I Bust! My current score is 22

You Win! Cngratulations!

You score is 19

Do you want to start again? y/n: y

My Hand Cards: ? K-S

Your Hand Cards: 10-H A-C 

You Win! Cngratulations!

You score is 21

Do you want to start again? y/n: n

Thank you for playing blackjack with me! Bye~

2.
(base) ScarlettdeMacBook-Pro-6:Blackjack scarlett$ ./main 99

Welcome! Let's play blackjack together!

My Hand Cards: ? 8-H

Your Hand Cards: 6-C Q-H 

Please enter 'h' to hit and 's' to stay: s

I Win!

My score is 21

Do you want to start again? y/n: y

My Hand Cards: ? 2-C

Your Hand Cards: 10-S 8-H 

Please enter 'h' to hit and 's' to stay: s

You Win : )

Your score is 18

My score is 17

Do you want to start again? y/n: n

Thank you for playing blackjack with me! Bye~


Algorithm:
Used Fisher-Yates / Durstenfeld shuffle algorithm to shuffle card.
