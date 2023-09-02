# Codewarriors2k22

## MINIMAX Algorithm - 
* Minimax is a kind of **backtracking** algorithm.
* It is widely used in two player turn-based games such as Tic-Tac-Toe, Backgammon, Mancala, Chess, etc.
* In Minimax the two players are called **maximizer** and **minimizer**. The maximizer tries to get the highest score possible while the minimizer tries to do the opposite and get the lowest score possible.
* Time Complexity: **O(b^d)**,  Space Complexity: **O(b*d)**; where b is the branching factor and d is the maximum depth of the tree.
* **Branching Factor -** It is the number of children that each node has.

* **Limitations of Minimax algorithm -**
  *  Because of the huge branching factor, the process of reaching the goal is **slower**.
  *  Evaluation and search of all possible nodes and branches degrades the performance and efficiency of the engine.
  *  oth the players have too many choices to decide from.
  *  If there is a restriction of time and space, it is not possible to explore the entire tree.
 
* The limitation of the minimax algorithm can be improved from **alpha-beta pruning**.

## ALPHA BETA Pruning -
* Alpha-beta pruning is a modified version of the minimax algorithm. It is an optimization technique for the minimax algorithm.
*  It reduces the computation time by a huge factor (averagely upto 25%) .
*  **Alpha:** The best (highest-value) choice we have found so far at any point along the path of Maximizer. The initial value of alpha is -∞.
*  **Beta:** The best (lowest-value) choice we have found so far at any point along the path of Minimizer. The initial value of beta is +∞.
*  **Condition for Alpha-beta pruning(When we prune the tree?):** α>=β
*  The Max player will only update the value of alpha and the Min player will only update the value of beta.
*  In case of Ideal pruning, time complexity become O(b^(m/2)) [earlier it was O(b^m)].

## Heuristic Algorithm - 
* To produce a working solution within a reasonable time frame.
* Instead of looking for a perfect solution, heuristic strategies look for a **quick** solution that falls within an acceptable range of accuracy.

![code_warriors_Info_page-0001](https://github.com/kaptan0428/Codewarriors2k22/assets/78855349/f9e40cda-d71f-435a-9e6e-e2c7ded6c1c2)

![code_warriors_Info_page-0002](https://github.com/kaptan0428/Codewarriors2k22/assets/78855349/5dfb785c-f565-4232-92c0-f85224ee3457)


![code_warriors_Info_page-0003](https://github.com/kaptan0428/Codewarriors2k22/assets/78855349/f61d8131-0bce-4d21-b3d4-cb6e58c40c59)

![code_warriors_Info_page-0004](https://github.com/kaptan0428/Codewarriors2k22/assets/78855349/8a851391-9dd8-46fa-b3eb-7b2e1f1ed2b1)


![code_warriors_Info_page-0005](https://github.com/kaptan0428/Codewarriors2k22/assets/78855349/4b124f9b-d046-48f1-b424-9f496d7ea1b0)

![code_warriors_Info_page-0006](https://github.com/kaptan0428/Codewarriors2k22/assets/78855349/e2bf937a-299e-445d-bb73-8045ad6e7f99)
