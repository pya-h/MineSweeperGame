# MineSweeper Game (A Different Take!)

This is a console-based implementation of the classic MineSweeper game, developed in C++, but with a unique twist on the scoring system.

## About the Game

MineSweeper is a single-player puzzle game where the objective is to clear a rectangular board containing hidden "mines" or bombs without detonating any of them. Unlike the traditional game, here the numbers shown on empty cells represent points, and your goal is to accumulate as many points as possible without hitting a mine.

## Rules of Play

1.  **The Board:** The game is played on a grid of cells. Some cells contain mines, others do not.
2.  **Starting the Game:** The game starts with all cells covered.
3.  **Revealing Cells & Scoring:** You select a cell to reveal it.
    *   If you reveal a mine, the game ends, and you lose.
    *   If you reveal an empty cell, it will display a number (0-8). This number *is your score for that cell*. You gain these points immediately; It also automatically opens all non-bomb cells adjacent to it.
    *   The total score is the sum of points from all non-mine cells you successfully reveal.
4.  **Winning the Game:** The game is won when all non-mine cells have been revealed. Your final score is the total accumulated points.

## Coding Features

This implementation showcases several fundamental C++ programming concepts and design considerations:

*   **Dynamic Game Dimensions:** The game is designed with dynamic dimensions, allowing developers to easily modify the board size (rows and columns) and the number of mines without significant code changes. The program automatically adapts its table structure and game logic accordingly.
*   **Object-Oriented Programming (OOP):** The game logic is structured using classes and objects (e.g., `Board`, `Cell`, `Game`), promoting modularity, reusability, and maintainability through a clean object-oriented design.
*   **Clean Coding Practices:** Emphasis has been placed on writing clear, concise, and well-structured code, adhering to best practices for readability and ease of understanding.
*   **Console-Based UI:** The entire game, including the drawing of the game board, cell states, and user interactions, is meticulously crafted within the command-line interface (CMD), providing a fully text-based graphical experience.
*   **Cross-Platform Compatibility:** The codebase is designed to be highly portable, ensuring seamless integration and execution across various operating systems, including Windows, macOS, and Linux.
*   **Data Structures:** Arrays or vectors are used to represent the game board and efficiently store cell states.
*   **Input/Output Handling:** Standard C++ I/O streams are used for robust user interaction (getting moves) and displaying the game board.
*   **Game Logic Implementation:** Includes sophisticated algorithms for revealing cells, accurately counting adjacent mines, handling win/loss conditions, managing flags, and calculating the player's score.
*   **Utility Functions:** Separate utility functions are employed for common tasks such as printing the board, validating user input, and other helper operations, further contributing to code organization.
