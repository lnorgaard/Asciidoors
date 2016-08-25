/* Asciimation.h
   =========
   Written/Edited: cs70 and Lee Norgaard
   Interface definition for the Asciimation class, which handles the main screen
   and coordination of an asciimation.
*/

#ifndef ASCIIMATION_H_INCLUDED
#define ASCIIMATION_H_INCLUDED = 1;

#include "Sprite.h"

/**
 * \class Asciimation
 * 
 * \brief 
 * Holds the contents of an ASCIImation
 *
 * \details
 * Stores an array of characters that will be displayed to the screen, and
 * a Sprite that will be added to the screen.
 *
 */
class Asciimation {
public:
  static const size_t SCREEN_WIDTH = 80;
  static const size_t SCREEN_HEIGHT = 40;
  static const size_t SCREEN_AREA = SCREEN_WIDTH * SCREEN_HEIGHT;

  /**
   * \brief 
   * Displays a sprite on the screen until the user enters "q"
   * Moves the bird up and down with "w" and "s"
   * 
   * \post The screen is destroyed.
   */
  void show();
  
  /**
   * \brief 
   * Returns the height of the sprite
   */
   size_t getSpriteHeight(Sprite* aSprite);
   
  /**
   * \brief 
   * Returns the width of the sprite
   */
   size_t getSpriteWidth(Sprite* aSprite);
  
  /**
   * \brief 
   * places characters into the buffer
   * 
   * \details
   * Clears the Asciimation's character buffer, then copies characters
   * from the stored Sprite to the character buffer using the Sprite's 
   * getCharAt member function. It should place each character at the 
   * right spot in the Asciimation's character buffer.
   * 
   * \post Asciimation object is updated desired characters
   */
  void prepareBufferForDisplay(); 

  /**
   * \brief 
   * Copies the current buffer contents to ncurses
   * 
   * \post 
   * No change to the Asciimation object
   */
  void copyBufferToNcurses();
  
  /*
  * \brief 
  * Adds a sprite
  *
  * \details
  * Takes in a reference to a Sprite and stores it in the appropriate 
  * data member of the Asciimation object
  */
  void addSprite1(Sprite* oneSprite);
  void addSprite2(Sprite* twoSprite);
  void addSprite3(Sprite* threeSprite);
  void addSprite4(Sprite* fourSprite);
  void addPerson(Sprite* you);
  void createLibrary(std::string mid, std::string low, std::string high);

private:

   /*
   * \brief 
   * Data member that holds the characters
   *
   * \details
   * A buffer of characters of length SCREEN_WIDTH * SCREEN_HEIGHT 
   * that holds all of the currently-displayed characters for the 
   * entire screen.
   */
   char screenStored_[SCREEN_AREA];

   /*
   * \brief 
   * An array of Sprite objects that will be drawn to the screen.
   */
   Sprite* doors_[3];

   /*
   * \brief 
   * This is the main character
   */
   Sprite* you_;

   /*
   * \brief
   * An array of potential Sprite objects
   * 
   * \details 
   * Unlike the array doors_[], doorLibrary[] doesn't change.
   * It stores all the possible doors (in this case only 3) so that
   * we can choose one from the array later to display on the screen next!
   */
   std::string doorLibrary_[3];

   /*
   * \brief
   * Keeps score
   */
   size_t score_ = 0;
   int lives_ = 5;


};

#endif // ifndef ASCIIMATION_H_INCLUDED
