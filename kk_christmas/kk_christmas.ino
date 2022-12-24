// In arduino language, all variables and their types have to be declared before they are used. This is done here.
// int stands for integer and bool stand for boolean.

int micIN = A0; // Define A0 as the pin the microphone is connected to
int amplitude; // Amplitude of sound in each measurement
int prev_amplitude; // Amplitude of the sound in the previous iteration
int zero_crossings=0; // Number of zero crossings
bool clap; // Is the clap registerd or not


int relayPin = 10; // The pin used to control the relay
int offset = 0; // Microphone offset for silence

int amplitude_threshold = 10; // Amplitude threshold for registering a clap 
int zero_crossings_threshold = 5; // Threshold for the number of zero crossings that define a clap
int block_size = 80; // Define the length of each processed block.

#define sign(x) ( (x>=0) ? +1 : -1 ) // Define a sign(x) function that returns the sign of x as +1 or -1


/*
 * Function that waits until clap has been detected and then exits.
 * 
 */
void waitForClap() {
  clap=false;
  
  do {
    // Initialize values for number of zero_crossings and high_amplitude points to zero
    zero_crossings=0;
    high_amplitude=0;

    // Read current value microphone amplitude and save it in prev_amplitude variable
    // Value of 512 corresponds to 0, or silence.
    prev_amplitude = analogRead(0) - 512;
   
    // Depending on the value of relayPin, certain offset needs to be added to the measurement.
    // Do not worry about this too much and just leave it as is.
    offset = digitalRead(relayPin) ? 10 : -10;

    // In 1ms, the loop will be executed about 8 times
    for (int i=0; i<=block_size; i++) {
        // Get current amplitude
        amplitude = analogRead(0) - 512 + offset;

        // Uncomment the next two lines and go tools -> Serial Monitor to print debug information.
        // Whenever the amplitude is larger than 10, you will see current amplitude.
        // This is very useful to determine the correct amplitude threshold.
        //if (amplitude > 10)
        //  Serial.println(amplitude);


        // If current amplitude is above the amplitude threshold, then there is some 'meaningful' sound coming in, and not random noise.
        if (abs(amplitude) > <insert variable here>){
          // If the sign of current amplitude is different from the previous amplitude, increace the zero_crossing counter
          if (sign(amplitude) != sign(<insert variable here>)){ 
            zero_crossings++;
          }
        }       

        // Save current amplitude measurement as prev_amplitude
        prev_amplitude = amplitude;
      }

    // Uncomment the next two lines and go tools -> Serial Monitor to print debug information.
    // Whenever the number of zero_crrossings is larger than 5, you will see how many zero crossings happened in the last processed block.
    // This is very useful to determine the correct zero_crossings threshold.
    //if (zero_crossings > 5)
    //  Serial.println(zero_crossings);

    // Clap is registered if number of high_amplitude measurements and zero_crossings is above the threshold.
    clap = (zero_crossings > <insert variable here>); 

     
  }
  // Stop the loop and exit the function when clap == true
     while (clap == <insert true or false here>);
}


/*
 * This function gets run once when the arduino turns on
 */
void setup() {
    Serial.begin(9600);
    pinMode(relayPin, OUTPUT);
    digitalWrite(relayPin, HIGH);
}


/*
 * This function is continuously run in a loop until arduino powers down
 */
void loop() {
    // Wait until a clap is detected
    waitForClap();

    // Toggle the relay pin
    digitalWrite(relayPin, !digitalRead(relayPin));

    // Wait a bit, so that same clap doesn't toggle the pin multiple times
    delay(100);
}
