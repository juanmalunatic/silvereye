# Silverapp's current version includes:
(TO-DO update this list frequently)

## Core features


### Serial communication

- Serial communication running in own thread.
	- Fixed threading exit on MinGW and MSVC2013 (thanks stackoverflow)
- Exiting app frees port correctly
  -Destructors are now called in order and correctly.
- Detect if valid frames (last bytes), else don't upd
  -Added a size parameter to decodeFrame
  
  
- Added serial panel to manage serial connections
	- Ability to change serial port during runtime
	- Error description on panel
		- Fixed default switch statement for other serial errors. 
		- TO-DO notify on disconnect /
				notify data is being fed
### Data formatting

- Sensor data array contains 7 sensors
  - Stored in private var of mainWindow.
  - Passed by const T&
- Formatting is done by the main thread.
 - Implemented status
- Updates array each 7 serial cycles
- Fixed issues with formatting in 32 bit windows
- Cross checked all libraries to provide same data

## Panels:

### Main

- Branding (Silvereye and icon)
- QPanel class to manage signal linking and unlinking
  from main window (to save resources when a panel is hidden)

	- Stores an executed connection 
	when the corresponding button is pressed
   
	- Emits a signal on close that destroys the
	saved connection cleanly.

- TO-DO implement "duplicate last received" strategy to handle missing data packets.

### Serial settings

- Show status of current COM data feed
- Change or reload current serial connection
- Update the list of the avaliable ports

### System status

- Created all the label fields
- Loop to iterate fields dynamically
- Decoding of all values and formatting

### Model control

- Save references and execute calibration procedure
- Save only frontal (virtual) reference
- Save only sensor mounting (old virtual reference remains)
- Save compensation <- remains of an unsuccessful test.
	TO-DO: Remove button Save compensation and referencing functions
- Camera control to switch between initial and sagittal views

### Human model

- Show 3D human model which updates live from the sensor stream. 
	Be sure to save references prior to showing the model, or else.
- TO-DO Fix CPU rendering lag when the system is left running for 2minutes>. 

### Sagittal angles

- Plot the sagittal angles using QCustomplot.

### Record kinematics

- Record the processed sagittal angles, and/or the involved quaternions.

### Record raw signals

- Record the unaltered data feed obtained from the sensors.