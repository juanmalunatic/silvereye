//http://www.phanderson.com/arduino/arduino_display.html

void print_binary(int v, int num_places)
{
    int mask=0, n;

    for (n=1; n<=num_places; n++)
    {
        mask = (mask << 1) | 0x0001;
    }
    v = v & mask;  // truncate v to specified number of places

    while(num_places)
    {

        if (v & (0x0001 << num_places-1))
        {
             Serial.print("1");
        }
        else
        {
             Serial.print("0");
        }

        --num_places;
        if(((num_places%4) == 0) && (num_places != 0))
        {
            Serial.print("_");
        }
    }
}



// Nada que use bno. funciona por scope en .h externos :$

/*
 *  allCalibrated 
 *  true si todo está calibrado
 */
/*
 bool allCalibrated(void)
{
  // 0 = sin calibrar
  // 3 = calibrado totalmente
  
  uint8_t sistema, gyro, accel, mag;
  sistema = gyro = accel = mag = 0;
  
  bno.getCalibration(&sistema, &gyro, &accel, &mag);

  // Se ignora todo hasta que sistema sea distinto a cero.
  Serial.print("\t");
 
  
  if( (gyro == 3) && (accel == 3) && (mag == 3) )
  {
    
    return true;
    
  } else {

      // Se muestran los valores 
      
      Serial.print("Sys:");
      Serial.print(sistema, DEC);
      Serial.print(" G:");
      Serial.print(gyro, DEC);
      Serial.print(" A:");
      Serial.print(accel, DEC);
      Serial.print(" M:");
      Serial.print(mag, DEC);
      
  }
  
  return false;
  
}*/

/*void printCalibration(void)
{
	// 0 = sin calibrar
	// 3 = calibrado totalmente

	uint8_t sistema, gyro, accel, mag;
	sistema = gyro = accel = mag = 0;

	bno.getCalibration(&sistema, &gyro, &accel, &mag);

	// Se muestran los valores 
	
	Serial.println("");
	Serial.print("Sys:");
	Serial.print(sistema, DEC);
	Serial.print(" G:");
	Serial.print(gyro, DEC);
	Serial.print(" A:");
	Serial.print(accel, DEC);
	Serial.print(" M:");
	Serial.print(mag, DEC);
	
}*/