/*
 * This program was built to turn my Kappa Kappa Psi (honorary band service fraternity) paddle
 * into a music and lights show that would play our school's fight song, Buckeye Battle Cry,
 * using an Adafruit Trinket 5V (ATtiny85 @ 8MHz). This file also contains code to play Hang on
 * Sloopy, but it was not used in the final project.
 * 
 * By Colin A. Williams (2018)
 * www.github.com/ColinAWilliams
 * 
 * This project would not have been possible without the TrinketTone code by Bruce E. Hall, W8BH
 * http://w8bh.net/avr/TrinketTone.pdf
 */

/*****************************
 **  Vairable Declarations  **
 *****************************/

// include file containing note pitches mapped to their frequencies
#include "pitches.h"

// defines the output pins
#define light1Pin 0
#define buzzerPin 1
#define light2Pin 2
#define light3Pin 3

// the next LED light to be lit
int nextLitLight = 0;

// tempo variables
int tempo = 180; // 180 BPM
double millisecondsPerBeat = 1000.0 / (tempo / 60.0);

// note types
const double wholeNote = 4.0;              // 4 beats
const double halfNote = 2.0;               // 2 beats
const double dottedHalfNote = 3.0;         // 3 beats
const double quarterNote = 1.0;            // 1 beat
const double dottedQuarterNote = 1.5;      // 1.5 beats
const double eighthNote = 0.5;             // 0.5 beats
const double dottedEighthNote = 0.75;      // 0.75 beats
const double sixteenthNote = 0.25;         // 0.25 beats
const double singleTriplet = 1.0 / 3.0;    // 1/3 of a beat

// articulations
const double staccato = 0.25;     // note takes up 1/4 the length of whatever note type
const double normal = 0.5;        // note takes up 1/2 the length of whatever note type
const double tenuto = 0.85;       // note takes up almost full length of whatever note type

/****************************
 **     Main Execution     **
 ****************************/

/* 
 * Code executed at startup (after button is pressed on paddle).
 */
void setup() {
  // set up pins
  pinMode(buzzerPin, OUTPUT);
  pinMode(light1Pin, OUTPUT);
  pinMode(light2Pin, OUTPUT);
  pinMode(light3Pin, OUTPUT);

  // play Buckeye Battle Cry
  playBuckeyeBattleCry();
}

/* 
 * No loop code.
 */
void loop() {
}

/*****************************
 **  Function Declarations  **
 *****************************/

/*
 * Sets the tempo of the song in beats per minute (BPM).
 * 
 * Parameters:
 *     BPM: the tempo of the song in beats per minute
 *     
 * Requires:
 *     BPM > 0
 *     There is likely an upper limit, but I am not sure
 *       of the exact value.
 */
void setTempo(int BPM) {
  tempo = BPM;
  millisecondsPerBeat = 1000.0 / (tempo / 60.0);
}

/*
 * Plays a note given its frequency, and numbers representing
 * its note type, and articulation.
 * 
 * Parameters:
 *     noteFrequency: the frequency in hertz of the note to be played
 *          noteType: a number representing the note type
 *                      (half note = 2.0 beats, 8th note = 0.5 beats,
 *                      etc)
 *      articulation: how long to hold a note (1.0 is full length
 * Requires:
 *     noteFrequency > 0,
 *     noteType > 0,
 *     1 >= articulation > 0
 */ 
void playNote(int noteFrequency, double noteType, double articulation) {
  // the notes were out of tune; this multiplier fixes it
  noteFrequency *= 0.9735;

  // play the note using TrinketTone() becuase the normal Arduino tone() method does not work with the Trinket
  TrinketTone(noteFrequency, millisecondsPerBeat * noteType * articulation);

  // shine 1 of the 3 LEDs, then psuedo-randomly choose the next LED to shine (one that's not currently lit)
  if (nextLitLight == 0) {
    digitalWrite(light1Pin, HIGH);
    digitalWrite(light2Pin, LOW);
    digitalWrite(light3Pin, LOW);
    nextLitLight = random(1, 3);  // chooses either 1 or 2
  } else if (nextLitLight == 1) {
    digitalWrite(light1Pin, LOW);
    digitalWrite(light2Pin, HIGH);
    digitalWrite(light3Pin, LOW);
    do {
      nextLitLight = random(0, 3);
    } while (nextLitLight == 1);  // (loop until) chooses either 1 or 2
  } else {
    digitalWrite(light1Pin, LOW);
    digitalWrite(light2Pin, LOW);
    digitalWrite(light3Pin, HIGH);
    nextLitLight = random(0, 2);  // chooses either 0 or 1
  }

  // wait until current note is over to continue
  delay(millisecondsPerBeat * noteType);
}

/*
 * Plays 1 chorus of Buckeye Battle Cry, an Ohio State University fight song.
 */
void playBuckeyeBattleCry() {
  setTempo(180);
  
  playNote(NOTE_C5, halfNote, tenuto);
  
  playNote(NOTE_B4, quarterNote, tenuto);
  playNote(NOTE_C5, quarterNote, tenuto);

  playNote(NOTE_GS4, eighthNote, normal);
  playNote(NOTE_F4, eighthNote, normal);
  playNote(NOTE_DS4, dottedHalfNote, tenuto);
  
  playNote(NOTE_GS4, quarterNote, tenuto);
  playNote(NOTE_GS4, dottedEighthNote, tenuto);
  playNote(NOTE_GS4, sixteenthNote, normal);
  
  playNote(NOTE_AS4, eighthNote, normal);
  playNote(NOTE_GS4, quarterNote, tenuto);
  playNote(NOTE_AS4, eighthNote, normal);

  playNote(NOTE_CS5, wholeNote, tenuto);
  
  playNote(NOTE_CS5, halfNote, tenuto);
  
  playNote(NOTE_C5, quarterNote, tenuto);
  playNote(NOTE_CS5, quarterNote, tenuto);
  
  playNote(NOTE_AS4, eighthNote, normal);
  playNote(NOTE_G4, eighthNote, normal);
  playNote(NOTE_DS4, dottedQuarterNote, tenuto);

  playNote(NOTE_G4, eighthNote, normal);
  playNote(NOTE_F4, eighthNote, normal);
  playNote(NOTE_E4, eighthNote, normal);
  
  playNote(NOTE_DS4, quarterNote, tenuto);
  playNote(NOTE_AS4, quarterNote, tenuto);
  
  playNote(NOTE_A4, quarterNote, tenuto);
  playNote(NOTE_AS4, quarterNote, tenuto);
  
  playNote(NOTE_C5, quarterNote, staccato);
  playNote(NOTE_DS5, quarterNote, tenuto);
  
  playNote(NOTE_DS5, quarterNote, tenuto);
  playNote(NOTE_DS5, quarterNote, tenuto);
  
  playNote(NOTE_C5, halfNote, tenuto);
  
  playNote(NOTE_B4, quarterNote, tenuto);
  playNote(NOTE_C5, quarterNote, tenuto);
  
  playNote(NOTE_GS4, eighthNote, normal);
  playNote(NOTE_F4, eighthNote, normal);
  playNote(NOTE_DS4, halfNote, tenuto);

  playNote(NOTE_DS4, quarterNote, tenuto);
  
  playNote(NOTE_GS4, quarterNote, tenuto);
  playNote(NOTE_C5, quarterNote, tenuto);
  
  playNote(NOTE_AS4, quarterNote, tenuto);
  playNote(NOTE_GS4, quarterNote, tenuto);
  
  playNote(NOTE_CS5, dottedHalfNote, normal);
  
  playNote(NOTE_F4, eighthNote, normal);
  playNote(NOTE_G4, eighthNote, normal);
  
  playNote(NOTE_GS4, eighthNote, normal);
  playNote(NOTE_G4, quarterNote, tenuto);
  playNote(NOTE_GS4, eighthNote, normal);

  playNote(NOTE_B4, quarterNote, tenuto);
  playNote(NOTE_AS4, eighthNote, normal);
  playNote(NOTE_GS4, eighthNote, normal);

  playNote(NOTE_C5, eighthNote, normal);
  playNote(NOTE_B4, quarterNote, tenuto);
  playNote(NOTE_C5, eighthNote, normal);

  playNote(NOTE_DS5, quarterNote, normal);
  playNote(NOTE_F5, quarterNote, normal);

  playNote(NOTE_C5, halfNote, tenuto);
  
  playNote(NOTE_AS4, halfNote, tenuto);
  
  playNote(NOTE_GS4, dottedHalfNote, tenuto);
}

/*
 * Plays the short version of Hang On Sloopy, the state rock song of Ohio, as performed by the OSUMB.
 */
void playShortHangOnSloopy() {
  setTempo(136);
  
  playNote(NOTE_C5, eighthNote, normal);
  playNote(NOTE_C5, eighthNote, normal);
  playNote(NOTE_C5, eighthNote, normal);
  playNote(NOTE_C5, eighthNote, normal);
  playNote(NOTE_C5, eighthNote, normal);
  playNote(NOTE_C5, eighthNote, normal);
  playNote(NOTE_C5, eighthNote, normal);
  playNote(NOTE_CS5, eighthNote, normal);
  playNote(NOTE_CS5, eighthNote, normal);
  playNote(NOTE_CS5, eighthNote, normal);
  playNote(NOTE_CS5, eighthNote, normal);
  playNote(NOTE_F5, eighthNote, normal);
  playNote(NOTE_F5, eighthNote, normal);
  playNote(NOTE_F5, quarterNote, staccato);

  for (int i = 0; i < 2; i++) {
    playNote(NOTE_FS5, dottedHalfNote, tenuto);
    playNote(NOTE_FS5, quarterNote, tenuto);
    
    playNote(NOTE_F5, eighthNote, normal);
    playNote(NOTE_F5, dottedQuarterNote, tenuto);
    playNote(NOTE_DS5, eighthNote, tenuto);
    playNote(NOTE_DS5, eighthNote, tenuto);
    playNote(NOTE_DS5, eighthNote, tenuto);
    playNote(NOTE_CS5, dottedQuarterNote, tenuto);
  
    playNote(NOTE_FS5, singleTriplet, tenuto);
    playNote(NOTE_DS5, singleTriplet, tenuto);
    playNote(NOTE_CS5, singleTriplet, tenuto);
    playNote(NOTE_FS5, quarterNote, tenuto);
    playNote(NOTE_FS5, singleTriplet, tenuto);
    playNote(NOTE_DS5, singleTriplet, tenuto);
    playNote(NOTE_CS5, singleTriplet, tenuto);
    playNote(NOTE_FS5, quarterNote, tenuto);
    playNote(NOTE_FS5, singleTriplet, tenuto);
    playNote(NOTE_DS5, singleTriplet, tenuto);
    playNote(NOTE_CS5, singleTriplet, tenuto);
    playNote(NOTE_FS5, quarterNote, tenuto);
    playNote(NOTE_FS5, singleTriplet, tenuto);
    playNote(NOTE_DS5, singleTriplet, tenuto);
    playNote(NOTE_CS5, singleTriplet, tenuto);
  }
  
  playNote(NOTE_FS5, dottedHalfNote, tenuto);
  playNote(NOTE_FS5, quarterNote, tenuto);
    
  playNote(NOTE_F5, eighthNote, normal);
  playNote(NOTE_F5, dottedQuarterNote, tenuto);
  playNote(NOTE_DS5, eighthNote, tenuto);
  playNote(NOTE_DS5, eighthNote, tenuto);
  playNote(NOTE_DS5, eighthNote, tenuto);
  playNote(NOTE_CS5, eighthNote, normal);

  playNote(NOTE_FS2, eighthNote, tenuto);
  playNote(NOTE_CS5, eighthNote, normal);
  playNote(NOTE_CS5, eighthNote, normal);
  playNote(NOTE_FS2, eighthNote, normal);
  playNote(NOTE_FS2, eighthNote, tenuto);
  playNote(NOTE_DS5, eighthNote, normal);
  playNote(NOTE_DS5, eighthNote, normal);
  playNote(NOTE_FS2, eighthNote, normal);
  
  playNote(NOTE_FS2, eighthNote, tenuto);
  playNote(NOTE_F5, eighthNote, normal);
  playNote(NOTE_F5, eighthNote, normal);
  playNote(NOTE_FS2, eighthNote, normal);
  playNote(NOTE_FS2, eighthNote, tenuto);
  playNote(NOTE_DS5, eighthNote, normal);
  playNote(NOTE_DS5, quarterNote, tenuto);

  playNote(NOTE_FS5, quarterNote, normal);
}

/*************************************************
 **   TrinketTone code by Bruce E. Hall, W8BH   **
 **     http://w8bh.net/avr/TrinketTone.pdf     **
 *************************************************/

volatile uint32_t toggle_count;

/* TrinketTone:
 *  
 * Generate a square wave on a given frequency & duration
 * Call with frequency (in hertz) and duration (in milliseconds).
 * Uses Timer1 in CTC mode. Assumes PB1 already in OUPUT mode.
 * Generated tone is non-blocking, so routine immediately
 * returns while tone is playing.
 */
void TrinketTone(uint16_t frequency, uint32_t duration) {
  // scan through prescalars to find the best fit
  uint32_t ocr = F_CPU/frequency/2;
  uint8_t prescalarBits = 1;
  while (ocr>255) {
   prescalarBits++;
   ocr /= 2;
  }
  
  // CTC mode; toggle OC1A pin; set prescalar
  TCCR1 = 0x90 | prescalarBits;

  // Calculate note duration in terms of toggle count
  // Duration will be tracked by timer1 ISR
  toggle_count = frequency * duration / 500;
  
  OCR1C = ocr-1; // Set the OCR
  bitWrite(TIMSK, OCIE1A, 1); // enable interrupt
}


/* Timer1 Interrupt Service Routine:
 * Keeps track of note duration via toggle counter
 * When correct time has elapsed, counter is disabled
 */
ISR(TIMER1_COMPA_vect)
{
  if (toggle_count != 0) { // done yet?
    toggle_count--; // no, keep counting
  } else { // yes, 
    TCCR1 = 0x90; // stop the counter
  }
}

