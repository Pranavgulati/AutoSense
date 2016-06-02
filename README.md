# AutoSense
A standalone BLE enabled sensor connected to the car which publicly broadcasts information about the car.
Synopsis:
Our BLE device basically transmits vital data which can be analysed to come up with useful information. We have come up with a solution that reduces traffic jams, makes the road travelling experience of people better, gives useful insights on road conditions for the government, and makes parking and toll tax payments easier and cash-free.

  * Key Parameters Broadcasted:
   - Plate no./ Vehicle registration no.
   - Current road condition status in a 4 point graded scale
   
#Key Features:
   - The broadcasted information can be picked up by any BLE device which will be logged on a central server. This server will continuously run data analysis algorithms on the dataset and provide useful geo-tagged information. This information can be used in various ways for improvements. 
     - Users would avoid bad roads and areas with traffic jams.
     - Knowledge is power. Government will be able to make better decisions and policies.
     - Any vehicle’s location can be tracked almost in real-time.

- Pre-programmed receivers installed in the parking lots will also be able to pick this broadcast information which can be used to **locate the position of the vehicle in a parking lot**. Additional information like emptiness of a level of a parking lot can be calculated which will be of immense help to a person who is entering a parking lot. Additionally, the user will also be able to top-up his wallet from within our app which would make his parking experience smooth and cash-free. **No more standing in a queue for generating a parking ticket, hassle-free cash-free payments, no more trouble remembering where you parked you car**.

- In the situation when a vehicle is involved in an accident, our device would be able to **trigger a call to an emergency contact** and at the same time this broadcast would be transmitted to other nearby cars. Hence, all the **cars in the vicinity** would be **pre-warned of an accident ahead** and can thereby change their route to prevent the aggravation of the situation and at the same time clear the way for emergency services. Overall, this would ensure lesser chaos and on-time delivery of emergency services to those who need it.

- Toll tax collection can happen with a breeze with BLE beacons that are tracked  at both the entry and exit points thereby giving the system significant time to process the transaction and direct the already paid users to a faster lane. No more standing in long queues and again, lesser traffic jams.

#HARDWARE required:
  - Programmable low power BLE beacon (nrf24L01+)
  - Low Power MCU (ATmega88/168/328)
  - Accelerometer (ADXL335)

TOTAL retail cost of parts : Rs.150 (3$)

APP is free with an in app purchase of the beacon and is under construction
#APP features:
-	Complete travel planning from selection of route based on road condition data and transit times to cheapest parking at the destination
-	Tells about the nearest parking facilities
-	Parking rates in nearest areas
-	Real road condition at the selected route of travel
-	Beacon communications 
-	Accident trigger to emergency services

