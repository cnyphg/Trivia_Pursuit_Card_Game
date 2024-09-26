# Trivia Pursuit Card Game

## Introduction
This project is about a virtual game simulator developed to simulate a modified Trivial Pursuit Card Game. This will be used to enhance the learning of students taking up Data Structures and Algorithms at a university in Malaysia. The virtual game simulator is designed to emulate the actual game's functionality, where students answer questions to collect points over several rounds of play. The virtual version introduces some digital concepts: automatic scoring, leaderboards, and searches, while retaining the actual gameplay, to offer a seamless and interactive learning platform. The project is written in C++ programming language in the translation of all the necessary data structures and algorithms to support and deliver fast gameplay. 


## Assumptions
The design of the virtual card game simulator for Trivial Pursuit is based on a few vital assumptions to make its development closer to the actual functionality during the physical game session or class and meet the student learning-related objectives for the development of the game.
- The first assumption made to design the simulator is that the game can generally be played in most classrooms and conferences where approximately 70 to 100 students can attend the lecture or class each time.
- The general understanding is the total number of 300 data structures and algorithm questions to be readied and stored in the simulator, which mimics the structure of the physical game.
- The mechanics of the physical game will be replicated in the virtual game: three decks of cards: not answered, answered, and discarded. Three chances will be given to all hypothetical players to answer questions, hence the freedom of choice to either draw from the not yet answered deck or from the discarded. The scoring system will still be as it is in the physical game, except that total points will be awarded for the unanswered cards at stake and 80% of the points for answered cards thrown aside.
- A leaderboard in the simulator will show individual scores and a winner’s chart of the top 30 overall performers. Sorting and searching functionalities will aid in the quick reckoning of the best and poorest performers in the class to both students and Professor Melinda. The interface should be intuitive and easy for the student to use the simulator and to navigate without much knowledge of technology. Such a simulator can be developed with the working assumption that it must run effectively on standard university computer hardware to allow peak interactivity with ease. Therefore, these strong assumptions take care of the requirement to develop a virtual game simulator that is made practical and accessible in helping to enhance student engagement with learning and teaching data structures and algorithms

## Game Rules
> 1. You will be participating in three rounds of the game.</li>
> 2. In each round, you will have the opportunity to answer one question.</li>
> 3. You can choose to draw a question card from the deck of unanswered questions or select from the pile of discarded cards.</li>
> 4. If you answer a question correctly, you will receive the full score stated on the card.</li>
> 5. If you answer a question from a discarded card, you will receive 80% of the overall score.</li>
> 6. After answering a question, you must place the answered question card on top of the answered card deck.</li>
> 7. If you choose not to answer a question, the card will be discarded to the end of the deck of discarded cards.</li>
> 8. After three rounds or when all questions are answered, the top 30 winners will be announced and displayed in a hierarchical chart.</li>
> 9. Additionally, your scores from each round, along with the questions answered, will be displayed on a leaderboard.</li>
> 10. Use the search function to find your name in the winners' chart and to identify your scores and performance in the leaderboard.</li>

