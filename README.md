# Training Heart Rate Zone Monitor

 This project was created on 4/25/2018
 By Ashley Hah and Marissa Kuhns
 Biosensor Project
 ENGR375 Bioinstrumentation and Measurement
 Messiah College Department of Engineering
 
This code collects heart rate data from the Adafruit Pulse Sensor and catagorizes them into 5 heart rate zones.  
The heart rate zones includes fatburning, cardio, intense and maximum heart rate zone. 
This zones are calculated based on the Maximum Heart Rate of an individual.  
The maximum heart rate can be calculated by substracting the individual's age from 220. 
The zones are specficied in terms of percentage of the maximum heart rate. 
For instance,  
Fatburning = 60-70% of Max HR;  
Cardio = 70-80% of Max HR;  
Intense = 80-90% of Max HR;  
Maximum = 90-100% of Max HR;  

When the individual's HR falls into the specific zones, it will cause the Neopixel ring to light up according to the zone he/she is in. 
When individual's HR is close to maximum HR, the Neopixel will color wipe in red and the vibrating motor will be activated indicating the HR is in a dangerous zone and individual needs to slow down. 
