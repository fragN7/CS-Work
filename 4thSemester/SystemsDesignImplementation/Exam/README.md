### 13.07.2023 - Retake session

**Theory exam (`10 minutes`)**: [Click here](https://forms.gle/kYUceVot1aWTDUeH6).

**Practical exam (`3 hours`):**

You have to write a full stack application that people can use to play Hangman.

Recall that each functionality is worth **1 snowflake**. Your snowflakes are then converted to **points**. For the retake session, your points will be computed as: `min(3, your_total_snowflakes / 7)`.

Please implement **exactly** what is asked, **nothing more** and **nothing less**. You need to present the functionalities in the order that they are listed in and each one has to be perfectly implemented for you to receive the snowflake for it. 

If something is ambiguous then you are expected to make the best decision according to what was discussed during the lectures and labs. If things are still ambiguous, then any decision will be accepted.

You should have persistence to a database for all added data, so restarting the application should keep the data. You must commit and push everything to the github repository created by accepting the assignment (link on Teams and on the "Examination" repository) in order for it to be considered.

1. Display the following table in plain HTML when visiting the `/` route. You do not need to color the rows, but the borders must look like they do here, as does the text:

    |  **#**  | **Game ID** | **Letters** | **Lives** | **Result** |  
    |---------|-------------|-------------|-----------|------------|  
    | **1** |               |             |           |            |  
    | **2** |               |             |           |            |  
    
2. Add an `h1` tag above the table with the content **Hangman** and a button below with the content **Create game**.

3. When clicking on the **Create game** button, you should see a popup / dialog that asks for: the game ID (string), the word (string) and the number of lives (integer). There should be a **Save** button that does nothing at this point and a **Cancel** button that only closes the popup / dialog.

4. When clicking the **Save** button from requirement `3`, validate that the game ID has exactly `6` alphanumerical characters and that it is unique. Validate that the word has at least `3` characters `a-z` (case insensitive) and that the number of lives is an integer higher than `1`. If any of these are invalid, show an appropriate error message. Otherwise, save the word with uppercase letters and redirect the user to `/game/<GID>`, where `<GID>` is the game ID that the user entered. We will call this the **Game Play Page**, or `GPP`. 

5. When someone accesses the `GPP`, validate that the `<GID>` is valid and display an error if not. Otherwise, display an `h1` with the content **Playing a game with `<num_characters>` letters.**. Below it, display an `h2` with as many space-separaters `_` characters as there are characters in the chosen word. Below it, have a `2 x 13` table in which each cell has a button. The buttons should have as contents, in order, the letters `A-Z`. Below it, have an `h3` with the contents: **Remaining lives: `<num_lives>`**.

6. On the `GPP`, when the user clicks a button, if the letter on it is part of the word, reveal each occurrence of it in the `h2` contents, disable the button and make its background color green. Otherwise, update the number of lives of remaining, disable the button and make its background color red. You do not need to implement any victory / lose conditions at this point (it's all right if the number of lives can become negative). The page should maintain its state on refresh.

7. If the number of lives reaches `0`, display an alert message saying you lost the game, change the `h1` contents to **Played a game with `<num_characters>` letters. You lost, the word was `<word>`.** and make the text color red. If all letters are revealed, display an alert message saying you won the game, change the `h1` contents to **Played a game with `<num_characters>` letters. You won.** and make the text color green. The page should maintain its state on refresh.

8. Dockerize your application. Running the docker container should start the frontend, the backend and anything else that you need. Everything should be started with a single docker or docker-compose command. If you have done this from the start, you will receive the snowflake now.

9. Add `swagger` for your backend. If you have done this from the start, you will receive the snowflake now.

10. Populate the table on `/` as follows:
    - The **Game ID** column should contain game IDs hyperlinked to the respective games.
    - The **Letters** column should contain the number of letters of the word.
    - The **Lives** column should contain the text **`<remaining_lives>` / `<initial_lives>`**.
    - The **Result** column should be empty if the game is still ongoing or contain the word if the game has been either lost or won. Show the word in red if lost and green if won.

11. On `/`, below the table, add percentages for games won, lost and still going.

12. On the `GPP`, below everything, add a button with the contents **Give up**. On click, it should ask for confirmation and if confirmed it should reveal the word, set the game as lost (lives to 0, all letter buttons disabled and red background color).
