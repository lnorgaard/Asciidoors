/**
 * \file Asciimation.cc
 * \author cs70 Provided Code and Lee Norgaard
 *
 * \brief Implements the Asciimation class
 *
 * \details Takes a sprite and shows the asciimation
 *
 */

#include "Asciimation.h"
#include "Sprite.h"

#include <iostream>
#include <ncurses.h>
#include <unistd.h>
#include <random>

using std::cout;
using std::endl;

/**
 * \brief 
 * Shows the Asciimation
 * 
 * \details 
 * Initializes the screen for ncurses, then repeatedly 
 * updates the screen until the user exits by pressing 'q'.
 */
void Asciimation::show() {

  const int PAUSE_TIME_IN_MICROSECONDS = 60000;

  // Initialize the screen
  initscr();

  // Don't echo characters entered by the user
  noecho();

  // Make the cursor invisible
  curs_set(0);

  // Tell ncurses not to block waiting for user input on getch() calls.
  nodelay(stdscr, TRUE);

  // We're not using the cursor, so tell ncurses to leave it wherever our
  // updates happen to put it.
  leaveok(stdscr, TRUE);

  // Leave the cursor on the bottom line of the screen instead of scrolling
  // if one of our updates would put it off-screen.
  scrollok(stdscr, FALSE);

  // Show the asciimation by refreshing the screen with new data, every so often
  bool weShouldContinueDisplaying = true;

  while (weShouldContinueDisplaying) {
    // Call the function to prepare new display contents
    prepareBufferForDisplay();

    // Call the function to copy display contents to ncurses
    copyBufferToNcurses();

    // Draw the screen with ncurses
    refresh();

    // Sleep between updates
    usleep(PAUSE_TIME_IN_MICROSECONDS);

    // Check to see if the user has entered 'q' to quit yet
    const char ch = getch();
    if (ch == 'q') {
      weShouldContinueDisplaying = false;
    }
    if (ch == 'a') {
      you_->chooseLeft();
      std::random_device rd;
      std::mt19937 gen(rd());
      std::uniform_int_distribution<> dis(0, 2);
      doors_[dis(gen)]->setString(doorLibrary_[2]);
      if (dis(gen) != 0) {
        ++score_;
      } else {
        --lives_;
      }
    }
    if (ch == 's') {
      you_->chooseMiddle();
      std::random_device rd;
      std::mt19937 gen(rd());
      std::uniform_int_distribution<> dis(0, 2);
      doors_[dis(gen)]->setString(doorLibrary_[2]);
      if (dis(gen) != 1) {
        ++score_;
      } else {
        --lives_;
      }
    }
    if (ch == 'd') {
      you_->chooseRight();
      std::random_device rd;
      std::mt19937 gen(rd());
      std::uniform_int_distribution<> dis(0, 2);
      doors_[dis(gen)]->setString(doorLibrary_[2]);
      if (dis(gen) != 2) {
        ++score_;
      } else {
        --lives_;
      }
    }
  }

  // Put the cursor back to beginning of the last row of the terminal, where
  // we expect it to be when the program exits.
  mvcur(0, COLS - 1, LINES - 1, 0);

  // Restore the saved shell terminal before exiting.
  endwin();
}

/**
 * \brief 
 * Takes in a reference to a sprite and stores it in the appropriate 
 * data member of the Asciimation object
 *
 * \details 
 * The following methods add desired sprites into...
 *  doors_[]: an array of the current door sprites on screen
 *  you_: a single sprite representing the main character
 *  doorLibrary_[]: an array of all potential door sprites
 */
void Asciimation::addSprite1(Sprite* oneSprite) {
  doors_[0] = oneSprite;
}
void Asciimation::addSprite2(Sprite* twoSprite) {
  doors_[1] = twoSprite;
}
void Asciimation::addSprite3(Sprite* threeSprite) {
  doors_[2] = threeSprite;
}
void Asciimation::addPerson(Sprite* you) {
  you_ = you;
}
void Asciimation::createLibrary(std::string normal, std::string ok, std::string bad) {
  doorLibrary_[0] = normal;
  doorLibrary_[1] = ok;
  doorLibrary_[2] = bad;
}

/**
 * \brief 
 * Returns the height of the sprite
 */
size_t Asciimation::getSpriteHeight(Sprite* aSprite) {
  return aSprite->getHeight();
}

/**
 * \brief 
 * Returns the width of the sprite
 */
size_t Asciimation::getSpriteWidth(Sprite* aSprite) {
  return aSprite->getWidth();
}

/**
 * \brief 
 * Places characters into the buffer
 * 
 * \details 
 * Clears the Asciimation's character buffer, then copies characters
 * from the stored Sprite to the character buffer using the Sprite's 
 * getCharAt member function. It should place each character at the 
 * right spot in the Asciimation's character buffer.
 */
void Asciimation::prepareBufferForDisplay() {
 
  // Clear all of screen buffer
  for (size_t i = 0; i < SCREEN_AREA; ++i) {
    // replace with empty char
    screenStored_[i] = ' '; 
  }

  // Display the score
  std::string scoreText = "Score: " + std::to_string(score_);
  size_t stringLength = scoreText.size();
  for (size_t i = 0; i <stringLength; ++i) {
    screenStored_[i] = scoreText[i];
  }

  // Display the lives
  std::string livesText = "Lives: " + std::to_string(lives_);
  size_t stringLength2 = livesText.size();
  for (size_t i = 0; i <stringLength2; ++i) {
    screenStored_[i + 15] = livesText[i];
  }

  // Insert the doors into the buffer
  for (size_t spriteRow = 0; spriteRow < getSpriteHeight(doors_[0]); ++spriteRow) {
    for (size_t spriteCol = 0; spriteCol < getSpriteWidth(doors_[0]); ++spriteCol) {
      for (size_t i = 0; i < 3; ++i) {
  
        // do math to get index in screenStored_ (used % to wrap around the screen)
        const size_t screenRow = (spriteRow + doors_[i]->getTopLeftRow()) % SCREEN_HEIGHT;
        const size_t screenCol = (spriteCol + doors_[i]->getTopLeftCol()) % SCREEN_WIDTH;
        const size_t indexIntoScreenBuffer = screenRow * SCREEN_WIDTH + screenCol;
        
        // place the character in the spot using getCharAt
        screenStored_[indexIntoScreenBuffer] = doors_[i]->getCharAt(spriteRow, spriteCol);
        
      }
    }
  }

  // Insert the person into the buffer
  for (size_t spriteRow = 0; spriteRow < getSpriteHeight(you_); ++spriteRow) {
    for (size_t spriteCol = 0; spriteCol < getSpriteWidth(you_); ++spriteCol) {

        // do math to get index in screenStored_ (used % to wrap around the screen)
        const size_t screenRow = (spriteRow + you_->getTopLeftRow()) % SCREEN_HEIGHT;
        const size_t screenCol = (spriteCol + you_->getTopLeftCol()) % SCREEN_WIDTH;
        const size_t indexIntoScreenBuffer = screenRow * SCREEN_WIDTH + screenCol;
        
        // place the character in the spot using getCharAt
        screenStored_[indexIntoScreenBuffer] = you_->getCharAt(spriteRow, spriteCol);
        
    }
  }
} 

/**
 * \brief 
 * Copies the current buffer contents to ncurses
 * 
 * \details 
 * Loop through all of the characters in the character buffer and
 * copy them to the right place on the screen, using the ncurses
 * function mvaddch. mvaddch(r, c, char) puts the character char at
 * row r, column c of the screen.
 */
void Asciimation::copyBufferToNcurses() {
  
  for (size_t screenRow = 0; screenRow < SCREEN_HEIGHT; ++screenRow) {
    for (size_t screenCol = 0; screenCol < SCREEN_WIDTH; ++screenCol) {
      
      size_t currentIndex = screenRow * SCREEN_WIDTH + screenCol;
      
      // display character at currentIndex to screen
      mvaddch(screenRow, screenCol, screenStored_[currentIndex]);
    }
  }
  
}
