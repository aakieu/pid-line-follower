uint8_t turnInMaze(uint8_t dir, uint8_t turn)
{
  uint8_t index = (turn << 2) + dir;
  uint8_t curr_dir = pgm_read_byte_near(turn_table + index);
  return curr_dir; 
}  //end turnInMaze


// Compass  S    E    W    N
// dir     00   01   10   11
Coord stepInMaze (uint8_t dir, Coord stepp) 
{//updates new row and column 
  switch (dir) {
    case 0x00: // south
      // increment row by 1 
      stepp.row += 1; 
      break;
      
    case 0x01:  // east 
        // increment column 
        stepp.col += 1; 
      break;
      
    case 0x02:  // west 
      //do something when var equals 1
      stepp.col -= 1; 
      break;
      
    case 0x03:  // north 
      //do something when var equals 2
      stepp.row -= 1; 
      break;
    default:
      // if nothing else matches, do the default
      // default is optional
      break;
  }
  return stepp; //returns Coord Ojbect
}


uint8_t roomInMaze(Coord stepp)
{
  //returns room value in theMaze[] based on colunm robot.maze (Coord object)
  uint16_t index = 21*(stepp.row) + (stepp.col); 
  uint8_t roomValue = pgm_read_byte_near(theMaze + index);
  return roomValue; 
}
