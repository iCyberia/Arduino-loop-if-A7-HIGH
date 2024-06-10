bool flag = false;
bool wasHigh = false;
unsigned long time_start_ms;

void setup() {
  // Initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  // Set pin A7 as an input:
  pinMode(A7, INPUT);

  // Initialize the start time
  time_start_ms = millis();
}

void loop() {
  // Read the value from A7
  int sensorValue = digitalRead(A7);

  // If A7 reads HIGH and was not high before
  if (sensorValue == HIGH && !wasHigh) {
    // Alternate between two pieces of code
    if (flag) {
      // Code block 1
      Serial.println("Executing Code Block 1");
      // Add your code block 1 here

      flag = false; // Toggle flag
    } else {
      // Code block 2
      Serial.println("Executing Code Block 2");
      // Add your code block 2 here

      flag = true; // Toggle flag
    }
    wasHigh = true; // Update the state to indicate A7 is currently high
  }

  // If A7 reads LOW, update the state to indicate A7 is not high
  if (sensorValue == LOW) {
    wasHigh = false;
  }

  // Update the time and display it
  updateTimeAndDisplay();

  // Wait for a short time before checking again
  delay(100);
}

void updateTimeAndDisplay() {
  unsigned long time_now_s = (millis() - time_start_ms) / 1000;
  char time_string[] = {'0', '0', ':', '0', '0', '\0'};
  time_string[0] = time_now_s / 60 / 10 + '0';
  time_string[1] = time_now_s / 60 % 10 + '0';
  time_string[3] = time_now_s % 60 / 10 + '0';
  time_string[4] = time_now_s % 60 % 10 + '0';

  for (int i = 0; i < 5; i++) {
    paint.Clear(UNCOLORED);
    paint.DrawStringAt(20, 10, time_string, &Font16, COLORED);
    Serial.print("refresh------\r\n ");
    // epd.DisplayFrame_Partial(paint.GetImage(), 20, 100, 40, 120); // Width must be a multiple of 8
    /* Writes new data to RAM */
    epd.DisplayFrame_Part(paint.GetImage(), 40 + i * 40, 30, 80 + i * 40, 140, false); // Xstart must be a multiple of 8
    /* Displays and toggles the RAM currently in use */
    epd.TurnOnDisplay();
    /* Writes the last data to another RAM */
    epd.DisplayFrame_Part(paint.GetImage(), 40 + i * 40, 30, 80 + i * 40, 140, false); // Xstart must be a multiple of 8
    delay(500);
  }
}
