//encoder position reader

task main ()
{
  long RobIsFat = 0;
  while(true)
  {
    RobIsFat = nMotorEncoder[motorA];
    nxtDisplayTextLine(2, "%d", RobIsFat);
    sleep(100);
  }
}

//lol, rob is like a tank
//servo?
//this is an encoder reader
//why don't you do this:

/*
task main ()
{
  while(true)
  {
    nxtDisplayTextLine(2, "%d", nMotorEncoder[motorA]);
  }
}
*/