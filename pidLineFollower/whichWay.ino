//hitWall – checks if the path in front of the robot is clear
boolean hitWall(uint8_t dir, uint8_t room)
{
  switch(dir){ // a numerical variable of positive values
  case 0x00:  // south 
    return (room & 0x11)& 0x08; //comparing room to 1000
    break;
  case 0x01: // east 
    // Do something here…
    return (room & 0x11)& 0x02;  //comparing room to 0010
    break;
  case 0x02:  // west 
    // Do something here…
    return (room & 0x11)& 0x04;  //comparing room to 0100
    break;
  case 0x03:  // north 
    // Do something here…
    return (room & 0x11)& 0x01;  //comparing room to 0001
    break;   
  // Add more cases as necessary
  default: // Catches all non-defined cases
    // All cases must be defined, or default case included
    // to avoid error)
    break;
    }
};  // end hitWall

//leftPaw – checks if the path to the left of the robot is clear
boolean leftWall(uint8_t dir, uint8_t room)
{
  switch(dir){ // a numerical variable of positive values
  case 0x00:  // south 
    return (room & 0x11)& 0x02; //comparing room to 0010
    break;
  case 0x01: // east 
    // Do something here…
    return (room & 0x11)& 0x01;  //comparing room to 0001
    break;
  case 0x02:  // west 
    // Do something here…
    return (room & 0x11)& 0x08;  //comparing room to 1000
    break;
  case 0x03:  // north 
    // Do something here…
    return (room & 0x11)& 0x04;  //comparing room to 0100
    break;   
  // Add more cases as necessary
  default: // Catches all non-defined cases
    // All cases must be defined, or default case included
    // to avoid error)
    break;
    }
};  // end leftPaw

//rightPaw – checks if the path to the right of the robot is clear
boolean rightWall(uint8_t dir, uint8_t room)
{
  switch(dir){ // a numerical variable of positive values
  case 0x00:  // south 
    return (room & 0x11)& 0x04; //comparing room to 0100
    break;
  case 0x01: // east 
    // Do something here…
    return (room & 0x11)& 0x08;  //comparing room to 1000
    break;
  case 0x02:  // west 
    // Do something here…
    return (room & 0x11)& 0x01;  //comparing room to 0010
    break;
  case 0x03:  // north 
    // Do something here…
    return (room & 0x11)& 0x02;  //comparing room to 0010
    break;   
  // Add more cases as necessary
  default: // Catches all non-defined cases
    // All cases must be defined, or default case included
    // to avoid error)
    break;
    }
};  // end rightPaw


//inForest – checks if the robot is still in the maze

boolean inForest ( Coord stepp)
{
  if ((stepp.row == 0xFF) && (stepp.col = 0x14))
  return true;
  else return false; 
}


//whichWay – translates room code into intersection type and then return turning action
uint8_t whichWay(uint8_t dir, uint8_t room)
{
  boolean front = hitWall(dir, room);
  boolean leftt = leftWall(dir, room);
  boolean rightt = rightWall(dir, room);
  uint8_t roomType =  ((front << 2) + (leftt << 1) + rightt); //<-- Prelab Question

  switch(roomType)
  {
    case 0x00:
    //4-way intersection (All directions open)
      return 0x00; // Define turning action
    // Add additional cases for every type of intersection
    case 0x01: // front blocked 
      return 0x01; //turn right, left, or around 
    case 0x02:  // right side blocked 
      return 0x00;  //no turn, turn left, or turn around 
    case 0x03: // right corner 
      return 0x02; // left turn only 
    case 0x04: //left side blocked 
      return 0x00; //no turn, turn right, or turn around
    case 0x05:  //left-corner
      return 0x01; // turn right 
    case 0x06: //Hallway
      return 0x00; // no turn 
    case 0x07:  // Dead-end
      return 0x03;  // turn around only 
  } 
}
