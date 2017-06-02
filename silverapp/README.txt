Includes:

TO-DO update this list
also include:




--------------------
Serial communication
--------------------

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
--------------------
Data formatting
--------------------
- Sensor data array contains 7 sensors
  - Stored in private var of mainWindow.
  - Passed by const T&
- Formatting is done by the main thread.
 - Implemented status
- Updates array each 7 serial cycles
- Fixed issues with formatting in 32 bit windows
- Cross checked all libraries to provide same data

--------------------
Panels:
--------------------
Main (alpha)

- TO-DO: Branding
- Has image placeholder

- QPanel class to manage signal linking and unlinking
  from main window (to save resources when a panel is hidden)
	
	-Stores an executed connection 
	when the corresponding button is pressed
   
	-Emits a signal on close that destroys the
	saved connection cleanly.

Status (beta)

- Created all the label fields
- Loop to iterate fields dynamically
- Decoding of all values and formatting

Serial settings panel (to-do description)

Raw recording panel (to-do description)
