/*

This version is used in production, with 
stats_mode = false.

*/

// RF24 dependencies
#include <SPI.h>
#include "RF24.h"
//#include "nRF24L01.h"

// IMU dependencies
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

// src/ required per https://github.com/arduino/arduino-builder/pull/172
// undocumented, found out by searching the github issues ._.
#include "src/frame_utils/createFrame.h"

/************* User config **********************/
byte module_id = 7; /// !!!!!!!!!!

bool stabilize_framerate        = true;
unsigned long time_loop_desired = 1420; // Desired time of the whole loop [us] (1.4ms*7 = 9.8ms)

const bool stats_mode = false;
const unsigned long report_stats_time = 10000; // 10 min = 10*60*1000

const bool master_debug = false;
const bool slave_debug  = false; // slaves have not been flashed yet!
/************************************************/

bool is_master;
byte module_polling = 1; // starts with module1
byte total_slaves   = 7; // total slaves (shocking, I know)
byte bt_rst = 4;
byte bt_cs  = 8;  
unsigned long led_time;
bool led_on;
unsigned long time_loop_start;

RF24 radio(5,6); // CE,CSN pins on the RF24
Adafruit_BNO055 bno = Adafruit_BNO055(55); 
uint8_t addresses[][6] = {"1Addr", "2Addr", "3Addr", "4Addr", "5Addr", "6Addr", "7Addr", "8Addr"};

//----------------------
// Stats
//----------------------

// Master
unsigned long failed_writes    = 0;
unsigned long empty_acks       = 0;
unsigned long correct_payloads = 0;
unsigned long corrupt_payloads = 0;
unsigned long stats_timer      = 0;
unsigned long elapsed_total_ms = 0;

// Slave
// TO-DO

void setup(void)
{
	delay(1000); // Delay the start just to see the first serial messages
	if ( module_id == 0 ) // Set master flag for code readability
	{
		is_master = true;
	}
	if( is_master || slave_debug ) // Serial should not be started in slaves for performance
	{
		Serial.begin(38400); // Minimum standard rate > 21000
		Serial.println(F("System startup."));
	}
	
	pinMode(bt_rst, OUTPUT); // Hold BLE_RST pin on LOW to reset the BLE module (preventing it from working).
	digitalWrite(bt_rst, LOW);
	delay(10);
	
	bool radio_begin = radio.begin();	// Start the radio
	if ( radio_begin && is_master )
	{
		Serial.println(F("RF24 began correctly."));
	};
	
	radio.setDataRate( RF24_2MBPS  );     // Radio options must be activated after radio.begin // Max speed
	radio.setPALevel( RF24_PA_MAX );      // Max power
	radio.setCRCLength( RF24_CRC_16 ) ;   // !!!! Changed CRC and this fixed freezings. DON'T MOVE.
	radio.maskIRQ(1,1,1);                 // Turn off interrupts to pin
	radio.setAddressWidth(3); 			  // Shortest address
	radio.setChannel( 2 );                // Default is 76. Maybe helps with BT interference.
	radio.setRetries(1,1);               // Minimum combination that works with HW in use is (1,0)
	radio.enableAckPayload();             // Enable ACK payloads in pipes 0 and 1.
	radio.enableDynamicPayloads();        // Enable ACK payloads in all pipes (both lines are required!)
	delay(1000);
	
	if ( is_master )
	{
		radio.openReadingPipe(1, addresses[7]);  // Master's address is [7] on the list
		radio.openWritingPipe( addresses[0] );   // Master begins polling 1Addr
	} 
	else 
	{
		radio.openReadingPipe(1, addresses[module_id - 1] );
		radio.openWritingPipe( addresses[7] );
	}
	
	radio.startListening();     // Necessary for all, even if disabled afterwards in master.
	if( is_master )
	{
		radio.stopListening();  // Master stops listening (listening is the default slave behaviour).
	}
	
	if( !is_master ) // IMU setup just for slaves
	{
		if( !bno.begin() ) // Check the sensor initializing it implicitly
		{
			Serial.begin(9600);
			Serial.println(F("There's another I2C device in SDA/SCL, but not a BNO055!"));
			Serial.println(F("This sketch will not continue from here."));
			while(1);
		}
		delay(1000);                 // Set a delay for the BNO055
		bno.setExtCrystalUse(true);  // Use the (on-board) external crystal.
		
		// !!! preload frame to do	
		
	}
	pinMode(13, OUTPUT); // Activity detection [2/3]
	led_on = false;
	digitalWrite(13, LOW);
	
	led_time = millis();
	stats_timer = millis();
	
}
void loop(void)
{
	if( is_master )	// Times the master loop.
	{
		time_loop_start = micros();
	}
	if ( ( millis() - led_time ) >= 500 ) 	// Activity detection [3/3]
	{
		if ( led_on )
		{
			led_on = false;
			digitalWrite(13, LOW);
		}
		else
		{
			led_on = true;
			digitalWrite(13, HIGH);
		};
		led_time = millis();
	}
	/////////////////////////////////////////////
	if (is_master) {
		
		byte ack_payload[28];
		radio.openWritingPipe( addresses[module_polling - 1] ); // Switch target
		unsigned long polling_begins = micros();
		
		bool write_ok = false;
		byte polling_byte = 1;
		write_ok = radio.write(&polling_byte, 1);
		
		bool send_blank_frame = false;
		
		if ( write_ok )
		{
			if( radio.isAckPayloadAvailable() ) // ack available since write
			{
				if(master_debug)
				{
					Serial.print(module_polling);
					Serial.println(F(" sent me a payload."));
				}
				
				if(radio.getDynamicPayloadSize() < 1) // Auto checks: if(dynpayload > 32) -> ret 0;
				{
					// Corrupt payload has been auto flushed
					if( master_debug )
						Serial.println(F("Corrupt payload"));
					
					send_blank_frame = true;
					if(stats_mode)
						++corrupt_payloads;
				}
				else
				{
					radio.read( ack_payload, 28 );   // if not receiving an array &dereference the var
					byte serial_tx[30] = {0};
					memcpy(serial_tx, ack_payload, sizeof ack_payload);	
					serial_tx[28] = 0xFF;
					serial_tx[29] = 0x0A;
					
					if( !stats_mode )
					{
						Serial.write(serial_tx, 30); // Write output as binary data.
					}
					
					if(stats_mode)
					{
						delayMicroseconds(250); // simulate the delay of writing to serial (w.c. measured)
						++correct_payloads;
					}
				}
			}
			else // wrote but no ack payload
			{	
				if(master_debug)
				{
					Serial.print(F("Wrote to "));
					Serial.print(module_polling);
					Serial.print(F(", but didn't receive a payload."));
				}
				
				send_blank_frame = true;	
				
				if(stats_mode)
					++empty_acks;
			}			
		}
		else // couldn't write
		{
			if( master_debug )
			{
				Serial.print(module_polling, DEC);
				Serial.println(F(" couldn't be written."));
			}			
			send_blank_frame = true;
			
			if(stats_mode)
				++failed_writes;
		}
		
		if( send_blank_frame )
		{
			byte serial_tx[30] = {0};
			serial_tx[0] = serial_tx[0] | (module_polling << 4);
			serial_tx[28] = 0xFF;
			serial_tx[29] = 0x0A;
			Serial.write(serial_tx, 30);
		}

		if( stabilize_framerate )
		{
			unsigned long time_loop_end = micros() - time_loop_start;
			if( time_loop_end < time_loop_desired )
			{
				delayMicroseconds( time_loop_desired - time_loop_end );	
			};
		};
		
		if( master_debug )
		{
			Serial.print( module_polling );
			Serial.print(F("took: "));
			Serial.print( micros() - time_loop_start );
			Serial.println(F("--------------------------------"));
			
		}
		
		if ( module_polling < total_slaves )
		{
			module_polling = module_polling + 1;
		}
		else
		{
			module_polling = 1;
		}
		
		if( stats_mode ) // Spit stats after a while
		{
			if( (millis() - stats_timer) >= report_stats_time )
			{
				
				unsigned long curr_time  = millis();
				unsigned long elapsed_ms = curr_time - stats_timer;
				
				elapsed_total_ms += elapsed_ms;
				
				Serial.println(F("***************************************"));
				
				unsigned long total_packages = correct_payloads + corrupt_payloads + failed_writes;
				
				Serial.print(F("Total packages:"));
					Serial.println( total_packages );	
					// corrupt_payloads will register both >32 and <1
				Serial.print(F("Correct payloads: "));
					Serial.print( correct_payloads );
					Serial.print(F(". %: "));
					Serial.println( (correct_payloads*100.0)/total_packages , 5 );
					
				Serial.print(F("Failed writes: "));
					Serial.print(failed_writes);
					Serial.print(F(". %: "));
					Serial.println( (failed_writes*100.0)/total_packages , 5 );
					
				Serial.print(F("Empty ACKs: "));
					Serial.print(empty_acks);
					Serial.print(F(". %: "));
					Serial.println( (empty_acks*100.0)/total_packages , 5 );
					
				Serial.print(F("Corrupt payloads: "));
					Serial.print( corrupt_payloads );
					Serial.print(F(". %: "));
					Serial.println( (corrupt_payloads*100.0)/total_packages , 5 );
					
				Serial.println(F("-----------------------------------------"));
				Serial.print(F("Master data rate: "));
												// 30*8*1000
					Serial.print( (total_packages*240000.0)/(elapsed_total_ms) , 4);
					Serial.println(F(" bit/sec"));
					
				Serial.print(F("Frequency per sensor: "));
					Serial.print( (total_packages/7.0)/(elapsed_total_ms/1000.0) , 4 );
					Serial.println(F(" Hz"));
					
				Serial.print(F("Elapsed time this round: "));
					Serial.print( elapsed_ms );
					Serial.println(F(" ms"));
				
				Serial.print(F("Total elapsed time : "));
					Serial.print( elapsed_total_ms );
					Serial.println(F(" ms"));
				
				Serial.println(F("***************************************"));
				
				stats_timer = millis();	
				
			}
		} // end stats
		
	} // end if master module
	else
	{   // SLAVE
		byte pipeNo, gotByte;
		byte frame_imu[28];
		
		if( slave_debug )
		{
			Serial.print( module_id );
			Serial.println(F(" out of loop [1]"));
		}
		
		while( !radio.available() ) // ! Wait while i'm available
		{
			if( slave_debug )
			{
				Serial.println("Wait [2]");
			}
		};
		
		while( radio.available(&pipeNo) ) //pipeNo stores the pipe used in the tx
		{  
			radio.read( &gotByte , sizeof(gotByte) ); // ! cambiee size
			
			if( slave_debug )
			{
				Serial.println("In loop. 2xMe = stuck or 2+ pcks [3]");
				
				if( radio.rxFifoFull() ) // In older tests FIFO wouldn't clean. Report if happens
				{
					Serial.println("rxFifoFull [3.5]."); // "If the RX FIFOs are full, the received packet is discarded." -Datasheet
				}

				Serial.print("Rcvd byte: ");
				Serial.print(gotByte);
				Serial.println("[4]");
			}

			createFrame( module_id , frame_imu );	
			if( slave_debug )
				Serial.println("Created frame [5]");
			
			radio.writeAckPayload(pipeNo, frame_imu, 28 );
			if( slave_debug )
				Serial.println("ACK payload set [6]");			
		};
		
		if( slave_debug )
			Serial.println("Exited loop [7]");
		
	};
};
