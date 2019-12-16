
//
//static MyRobot robot{0x03,0x00,0x00,0x00,0x13,0x00};
//  int * LFSensor = readSensor();
//  
//  //Error for PID  
//  error = returnError(LFSensor); 
//
//  // Intersection 
//  if (intersection)
//  {
//    // updates numIntersection
//    countIntersection(); 
//    // updates turn
//    robot.turn = pgm_read_byte_near(turn_map + numIntersection);
//    //updates dir 
//    robot.dir = turnInMaze(robot.dir, robot.turn);
//    // physical turning 
//    switch (robot.turn) 
//    {
//    case 0x00:
//      forward(); 
//      break;
//    case 0x01:
//      // statements
//      stepUp();
//      turnRight(); 
//      break;
//    case 0x02:
//      // statements
//      stepUp();
//      turnLeft();
//      break;
//    case 0x03:
//      // statements
//      turnAround(); 
//      break;
//    } //end switch  
//    // updates new coordinates 
//    robot.maze =  stepInMaze (robot.dir, robot.maze);
//    // updates room  
//    robot.room = roomInMaze(robot.maze);
//    // no more intersection
//    intersection = false; 
//  } // end if 
// 
// // PID Calculation 
// PIDvalue = calcPID(error, previousError);
// previousError = error;
// // Set motor speeds based on error 
// setLeftRightSpeed(PIDvalue); 
// // Turn off all leds 
// ledOff();
