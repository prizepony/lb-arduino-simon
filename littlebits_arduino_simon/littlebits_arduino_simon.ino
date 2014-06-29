/***
 * littleBits Arduino Demo
 * Game of Simon clone
 * by Rory Nugent (rory@littlebits.cc)
 * Last updated: May 12, 2014
 *
 * Circuit:
 *
 *         Fork > Button > Arduino > LED
 * Power > Fork > Button > Arduino > LED
 *         Fork > Button > Arduino > LED
 ***/

// define the digital output LED pins
const int ledPins[] = {
  1, 5, 9};

// define the digital input button pins
const int buttonPins[] = { 
  0, A0, A1 };

// define the number of rounds of Simon
#define NUM_ROUNDS  5

// variables to control the flow of the game
int currentRound = 0;
int sequence[NUM_ROUNDS];
int gameStatus = -1;

void setup()
{
  // Enable serial
  Serial.begin(9600);

  Serial.println("Setting up inputs and outputs.");

  // set up output LEDs
  pinMode(ledPins[0], OUTPUT);
  pinMode(ledPins[1], OUTPUT);
  pinMode(ledPins[2], OUTPUT);

  // set up input buttons
  pinMode(buttonPins[0], INPUT);
  pinMode(buttonPins[1], INPUT);
  pinMode(buttonPins[2], INPUT);

  Serial.println("Setting up random number generator.");

  // seed the pseudo-random number generator with noise from an unconnected analog input pin
  randomSeed(analogRead(A4));
}

void loop()
{
  // randomly populate the game sequence
  Serial.println("Computing game sequence.");
  for(int i = 0; i < NUM_ROUNDS; i++)
  {
    sequence[i] = random(3);  // generate a number from 0-2
  }

  // flash LEDs to signify the start of the game
  digitalWrite(ledPins[0], HIGH);
  digitalWrite(ledPins[1], HIGH);
  digitalWrite(ledPins[2], HIGH);
  delay(1000);
  digitalWrite(ledPins[0], LOW);
  digitalWrite(ledPins[1], LOW);
  digitalWrite(ledPins[2], LOW);
  delay(1000);

  // main game loop
  Serial.println("Starting the game.");
  for(int i = 0; i < NUM_ROUNDS; i++)
  {
    // SHOW SEQUENCE
    showSequence(i);
    
    // USER RESPONDS TO SEQUENCE
    userResponse(i);
    
    delay(1000);  // pause between user response and next sequence
  }

  gameOver();     // game over sequence (forever loop)
}

void showSequence(int curRound)
{
  // display the LED sequence up to the current round
  Serial.println("Showing the game sequence.");
  
  for(int i = 0; i <= curRound; i++)
  {
    digitalWrite(ledPins[sequence[i]], HIGH);
    delay(1000);
    digitalWrite(ledPins[sequence[i]], LOW);
    
    if(i < curRound)
      delay(1000);
  }
}

void userResponse(int curRound)
{
  int currentState[] = {
    0, 0, 0    };
  int lastState[] = {
    0, 0, 0    };
  boolean waiting = true;

  // waiting for the user to respond to the sequence
  Serial.println("Tending to user response.");
  
  for(int i = 0; i <= curRound; i++)
  {
    while(waiting)
    {
      for(int j = 0; j < 3; j++)
      {
        currentState[j] = digitalRead(buttonPins[j]);

        // if the correct button was pressed
        if(currentState[j] == HIGH && lastState[j] == LOW && sequence[i] == j)
        {
          Serial.println("CORRECT BUTTON.");
          digitalWrite(ledPins[j], HIGH);
          
          while(digitalRead(buttonPins[j]) == HIGH) {}
          delay(250);
          
          digitalWrite(ledPins[j], LOW);

          waiting = false;
          break;
        }
        // if the wrong button was pressed
        else if(currentState[j] == HIGH && lastState[j] == LOW & sequence[i] != j)
        {
          Serial.println("WRONG BUTTON!");
          digitalWrite(ledPins[0], HIGH);
          digitalWrite(ledPins[1], HIGH);
          digitalWrite(ledPins[2], HIGH);
          delay(1000);
          digitalWrite(ledPins[0], LOW);
          digitalWrite(ledPins[1], LOW);
          digitalWrite(ledPins[2], LOW);
          delay(1000);

          waiting = false;
          showSequence(curRound);  // show sequence again
          i = -1;                  // reset round
          break;
        }

        lastState[j] = currentState[j];
      }
    }
    waiting = true;
  }
}

void gameOver()
{
  Serial.println("WINNER. GAME OVER.");
  
  while(1)
  {
    // flash LEDs in a certain sequence
    digitalWrite(ledPins[0], LOW);
    digitalWrite(ledPins[1], HIGH);
    digitalWrite(ledPins[2], LOW);
    delay(500);
    digitalWrite(ledPins[0], HIGH);
    digitalWrite(ledPins[1], LOW);
    digitalWrite(ledPins[2], HIGH);
    delay(500);
  }
}









