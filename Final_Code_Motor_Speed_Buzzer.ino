#include <LiquidCrystal.h> // Library for controlling the LCD
#include <Servo.h> // Library for controlling the servo motor

LiquidCrystal lcd(7, 6, 5, 4, 3, 2); // Set up the LCD's pins
Servo myServo; // Create a Servo object

#define BuzzerPin 12 // Define the pin for the buzzer

// Define motor control pins
#define Motor_ENB 11
#define Motor_IN4 10
#define Motor_IN3 9
#define ServoPin 8 // Define the pin for the servo

int speedValue = 0; // Motor speed (0-255)
int motorState = 0; // Motor state (1, 2, 3 for different speeds)
bool direction = true; // Motor direction (true = anticlockwise, false = clockwise)
bool oscState = false; // Oscillation state (true = oscillate, false = don't oscillate)
int currentPos = 90; // Initial servo position (0-180 degrees)

unsigned long lastLCDUpdateTime = 0; // Timestamp for the last LCD update
const unsigned long lcdUpdateInterval = 500; // Time between LCD updates in milliseconds

void setup() {
  Serial.begin(9600); // Begin serial communication at 9600 baud rate

  // Set motor pins as outputs
  pinMode(Motor_ENB, OUTPUT);
  pinMode(Motor_IN4, OUTPUT);
  pinMode(Motor_IN3, OUTPUT);
  pinMode(BuzzerPin, OUTPUT); // Set buzzer pin as output

  lcd.begin(16, 2); // Initialize the LCD (16 columns, 2 rows)
  lcd.setCursor(0, 0);
  lcd.print(" Speed Control ");
  lcd.setCursor(0, 1);
  lcd.print("  DC Motor  ");
  
  unsigned long startMillis = millis(); // Record the start time
  
  playWelcomeSound(); // Play welcome sound while displaying the welcome message

  while (millis() - startMillis < 2000) {
    // Wait for 2 seconds while the welcome message and sound are being played
  }
  
  lcd.clear(); // Clear the LCD after the welcome message
  myServo.attach(ServoPin); // Attach the servo to the pin
  myServo.write(currentPos); // Move the servo to the initial position

  updateLCD(true); // Update the LCD display with initial values
}

void loop() {
  checkBluetoothCommands(); // Check for incoming Bluetooth commands
  updateMotor(); // Update motor speed and direction
  updateServo(); // Update servo position
}

// Function to check and process Bluetooth commands
void checkBluetoothCommands() {
  if (Serial.available()) { // If data is available to read
    char command = Serial.read(); // Read the incoming command

    // Process the command
    switch (command) {
      case '1':
        playBuzzer(); // Play buzzer sound
        speedValue = 75; // Set speed to 75
        motorState = 1; // Set motor state to 1
        break;

      case '2':
        playBuzzer(); // Play buzzer sound
        speedValue = 140; // Set speed to 140
        motorState = 2; // Set motor state to 2
        break;

      case '3':
        playBuzzer(); // Play buzzer sound
        speedValue = 240; // Set speed to 240
        motorState = 3; // Set motor state to 3
        break;

      case 'F': // Set direction to clockwise
        playBuzzer(); // Play buzzer sound
        direction = false; // Clockwise
        break;

      case 'B': // Set direction to anticlockwise
        playBuzzer(); // Play buzzer sound
        direction = true; // Anticlockwise
        break;

      case 'N': // Start motor at speed 1 in clockwise direction
        playBuzzer(); // Play buzzer sound
        speedValue = 75;
        motorState = 1;
        direction = false;
        break;

      case 'H': // Start motor at speed 1 in anticlockwise direction
        playBuzzer(); // Play buzzer sound
        speedValue = 75;
        motorState = 1;
        direction = true;
        break;

      case 'S': // Stop the motor
        playBuzzer(); // Play buzzer sound
        motorState = 0;
        speedValue = 0;
        oscState = false; // Stop oscillation when motor stops
        break;

      case 'O': // Start oscillation
        playBuzzer(); // Play buzzer sound
        if (motorState > 0) {
          oscState = true;
        }
        break;

      case 'T': // Stop oscillation
        playBuzzer(); // Play buzzer sound
        oscState = false;
        break;

      default:
        Serial.println("Invalid Command"); // Print error for invalid commands
        break;
    }
  }
}

// Function to update motor control and LCD display
void updateMotor() {
  analogWrite(Motor_ENB, speedValue); // Set motor speed

  // Set motor direction
  if (direction) {
    digitalWrite(Motor_IN4, HIGH);
    digitalWrite(Motor_IN3, LOW);
  } else {
    digitalWrite(Motor_IN4, LOW);
    digitalWrite(Motor_IN3, HIGH);
  }

  // Update the LCD display less frequently
  if (millis() - lastLCDUpdateTime >= lcdUpdateInterval) {
    updateLCD(false); // Update the LCD display
    lastLCDUpdateTime = millis(); // Reset the timestamp
  }
}

// Function to control the servo motor for oscillation
void updateServo() {
  static int pos = currentPos; // Current servo position
  static bool increasing = true; // Direction of oscillation

  if (oscState && motorState > 0) { // If oscillation is enabled and motor is running
    if (increasing) {
      pos += 1; // Increase position
      if (pos >= 180) {
        pos = 180; // Limit to 180 degrees
        increasing = false; // Change direction to decreasing
      }
    } else {
      pos -= 1; // Decrease position
      if (pos <= 0) {
        pos = 0; // Limit to 0 degrees
        increasing = true; // Change direction to increasing
      }
    }
    currentPos = pos; // Update current position
    myServo.write(currentPos); // Set the servo to the new position
    delay(9); // Adjust speed of oscillation
  } else {
    myServo.write(currentPos); // Maintain last position when not oscillating
  }
}

// Function to update the LCD display
void updateLCD(bool forceUpdate) {
  static int lastMotorState = -1; // Last motor state
  static bool lastDirection = !direction; // Last direction
  static bool lastOscState = !oscState; // Last oscillation state

  if (forceUpdate || motorState != lastMotorState || direction != lastDirection || oscState != lastOscState) {
    lcd.clear(); // Clear the LCD
    lcd.setCursor(0, 0);

    if (motorState == 0) {
      lcd.print("Speed: 0"); // Display speed
      lcd.setCursor(0, 1);
      lcd.print("Stopped"); // Display stopped state
    } else {
      lcd.print("Speed: ");
      lcd.print(motorState); // Display motor state
      lcd.setCursor(0, 1);
      lcd.print(direction ? "AntiClockwise" : "Clockwise"); // Display direction
    }

    lcd.setCursor(12, 0);
    if (oscState) {
      lcd.print("OSC"); // Display oscillation
    } else {
      lcd.print("-"); // Display no oscillation
    }
  }
  lastMotorState = motorState; // Update last motor state
  lastDirection = direction; // Update last direction
  lastOscState = oscState; // Update last oscillation state
}

// Function to play buzzer sound
void playBuzzer() {
  digitalWrite(BuzzerPin, HIGH); // Turn on the buzzer
  delay(100); // Wait for 100 milliseconds
  digitalWrite(BuzzerPin, LOW); // Turn off the buzzer
}

// Function to play welcome sound
void playWelcomeSound() {
  tone(BuzzerPin, 659, 300); // Play E5 note for 300 milliseconds
  delay(400);
  tone(BuzzerPin, 523, 300); // Play C5 note for 300 milliseconds
  delay(400);
  tone(BuzzerPin, 440, 700); // Play A4 note for 700 milliseconds
  delay(700);
  noTone(BuzzerPin);
}
