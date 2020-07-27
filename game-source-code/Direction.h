#ifndef DIRECTION_H
#define DIRECTION_H
   /** 
     * An enum class to define the Centipede object's direction.
     */
enum class Direction{Up,/*!< The Centipede is moving upwards */
 Down,/*!< The Centipede is moving downwards */
 Left,/*!< The Centipede is moving to the left */
 Right,/*!< The Centipede is moving to the right */ 
 NoDir/*!< Default value */};

#endif