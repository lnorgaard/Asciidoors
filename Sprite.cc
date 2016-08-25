/**
 * \file Sprite.cc
 * \author cs70 Provided Code and Lee Norgaard
 *
 * \brief Implements the Sprite class (the obstacles and the bird)
 */

#include "Sprite.h"

#include <cstddef>
#include <cctype>
#include <iostream>
#include <string>

using std::ifstream;
using std::cout;
using std::cerr;
using std::endl;
using std::string;

/**
 * \brief 
 * Helper function for file stuff
 *
 * \details
 * Takes in a file and reads it in so that it can be 
 * displayed on the screen
 */
 void Sprite::fileHelper(const string& imageFile) {
  ifstream inputFile{imageFile};

  if (!inputFile.is_open()) {
    cerr << "couldn't open file at " << imageFile << endl;
    exit(1);
  }

  // Get the width and height of the sprite
  inputFile >> spriteWidth_;
  inputFile >> spriteHeight_;
  inputFile.get();
  
  // Allocate the memory for spriteStored_ since we now know the size.
  spriteStored_ = new char[spriteHeight_ * spriteWidth_];
  // Default numberofCharacterReadIn.
  size_t numberOfCharactersReadIn = 0;

  while (numberOfCharactersReadIn < spriteHeight_ * spriteWidth_) {
    // Read a character
    const char characterWeRead = inputFile.get();
    // If the file isn't "good" anymore, the file doesn't match our format
    if (!inputFile.good()) {
      // Uh-oh, something's wrong with the file
      cerr << "couldn't read character number "
           << numberOfCharactersReadIn << endl;
      exit(1);
    }
    // If it's not a newline, then it's a character we want
    if (characterWeRead != '\n') {
      // store characterWeRead into the right spot of your character array
      spriteStored_[numberOfCharactersReadIn] = characterWeRead;

      ++numberOfCharactersReadIn;
    }
    // else, if it is a newline, then we just keep reading
  }
  inputFile.close();
 }

/**
 * \brief 
 * Default constructor
 * 
 * \details
 * Takes in an image file, two size_t's representing the Sprite's 
 * top-left corner row and column, and a bool representing whether
 * the Sprite should scroll (move right). Constructs a sprite of 
 * the right size by reading the file that we give it.
 */
Sprite::Sprite(const string& imageFile, size_t topLeftCornerRow, 
  size_t topLeftCornerCol) : topLeftCornerRow_(topLeftCornerRow),
  topLeftCornerColumn_(topLeftCornerCol) {
    fileHelper(imageFile);
}

/*
* \brief 
* Sprite deconstructor
*/
Sprite::~Sprite() {
  delete[] spriteStored_;
  spriteStored_ = nullptr;
}

/*
* \brief 
* Return the Sprite's top-left corner row
*/
size_t Sprite::getTopLeftRow() {
  return topLeftCornerRow_;
}

/*
* \brief 
* Return the Sprite's top-left corner column
*/
size_t Sprite::getTopLeftCol() {
  return topLeftCornerColumn_;
}

/*
* \brief 
* Moves the sprite right
*/
void Sprite::chooseRight() {
  topLeftCornerColumn_ = 33;
  --topLeftCornerRow_;
  --topLeftCornerRow_;
}

/*
* \brief 
* Moves the sprite up
*/
void Sprite::chooseMiddle() {
  topLeftCornerColumn_ = 23;
  --topLeftCornerRow_;
  --topLeftCornerRow_;
}

/*
* \brief 
* Moves the sprite left
*/
void Sprite::chooseLeft() {
  topLeftCornerColumn_ = 13;
  --topLeftCornerRow_;
  --topLeftCornerRow_;
}

/**
 * \brief 
 * Returns the height of the sprite
 */
size_t Sprite::getHeight() {
  return spriteHeight_;
}

/**
 * \brief 
 * Returns the width of the sprite
 */
size_t Sprite::getWidth() {
  return spriteWidth_;
}

/**
 * \brief 
 * Changes the sprite file
 */
void Sprite::setString(const string& imageFile) {
  fileHelper(imageFile);
}

/*
* \brief 
* Gets the character at the desired spot
*
* \details
* Returns the col-th character in the row-th row of the Sprite’s 
* character array
*/
char Sprite::getCharAt(const size_t row, const size_t col) {
  // multiply the row by the sprite's width to access the row-th row
  const size_t endOfRow = row * spriteWidth_;
  
  //add the column to the row-th row to access the col-th character
  const size_t characterIndex = endOfRow + col;
  
  // now that we have the index, return the character at that index
  // in the sprite_stored array
  return spriteStored_[characterIndex];
}

