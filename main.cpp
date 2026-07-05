#include <Arduino.h>

// --- Button Definition ---
const int BUTTON_PIN = 2; // Connected to the 'S' pin on the blue header

// --- L298P Motor Shield Pin Definitions ---
const int E1 = 10; // Speed control (PWM) for Motor A (Left)
const int M1 = 12; // Direction control for Motor A (Left)
const int E2 = 11; // Speed control (PWM) for Motor B (Right)
const int M2 = 13; // Direction control for Motor B (Right)

// --- Calibration Settings ---
const int MOTOR_SPEED = 200;    
const int FORWARD_TIME = 1500;  
const int TURN_TIME = 800;      
const int PAUSE_TIME = 1000;     

// Function Declarations
void moveForward();
void turnRight();
void stopMotors();

void setup() {
    // Initialize motor control pins
    pinMode(M1, OUTPUT);
    pinMode(M2, OUTPUT);
    pinMode(E1, OUTPUT);
    pinMode(E2, OUTPUT);
    
    // Initialize button pin with internal pull-up resistor
    // Pin will read HIGH normally, and LOW when pressed
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    
    // Ensure motors start in a stopped state
    stopMotors();
}

void loop() {
    // Check if the button is pressed (reads LOW because it connects to Ground)
    if (digitalRead(BUTTON_PIN) == LOW) {
        
        // Short debounce delay to avoid accidental double-triggers
        delay(50); 
        
        // 1. Move Forward 0.5 meters
        moveForward();
        delay(FORWARD_TIME);
        
        stopMotors();
        delay(PAUSE_TIME);

        // 2. Execute Turn
        turnRight();
        delay(TURN_TIME);
        
        stopMotors();
        delay(PAUSE_TIME);
        
        // Wait here until you release the button so it doesn't immediately repeat
        while(digitalRead(BUTTON_PIN) == LOW) {
            delay(10);
        }
    }
}

// --- Helper Functions ---
void moveForward() {
    digitalWrite(M1, HIGH); 
    digitalWrite(M2, HIGH); 
    analogWrite(E1, MOTOR_SPEED);
    analogWrite(E2, MOTOR_SPEED);
}

void turnRight() {
    digitalWrite(M1, HIGH);
    digitalWrite(M2, LOW);
    analogWrite(E1, MOTOR_SPEED);
    analogWrite(E2, MOTOR_SPEED);
}

void stopMotors() {
    analogWrite(E1, 0);
    analogWrite(E2, 0);
}
