/**
 * \file showAsciimation.cc
 * \author cs70 Provided Code and Lee Norgaard
 *
 * \brief Provides the main() function for running an asciimation
 *
 */

#include "Asciimation.h"
#include "Sprite.h"

int main() {
  
  // Create the 3 doors 
  Sprite Door1_("sprites/door.txt", 3, 10);
  Sprite Door2_("sprites/door.txt", 3, 20);
  Sprite Door3_("sprites/door.txt", 3, 30);

  // Create the main character
  Sprite Person_("sprites/person.txt", 8, 23);
  
  // Create an Asciimation, add the sprites to the asciimation,
  // and show the asciimation!
  Asciimation doorAsciimation_;

  // Insert a normal door, a safe door, and a monster door into the library
  doorAsciimation_.createLibrary("sprites/door.txt", "sprites/okdoor.txt", "sprites/baddoor.txt");

  doorAsciimation_.addSprite1(&Door1_);
  doorAsciimation_.addSprite2(&Door2_);
  doorAsciimation_.addSprite3(&Door3_);

  doorAsciimation_.addPerson(&Person_);

  doorAsciimation_.show();
  
  return 0;
}
