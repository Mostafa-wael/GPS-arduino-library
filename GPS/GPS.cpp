#include "GPS.h"

GPS::GPS ()
{

}

/**************************-**********************************
*															 *
				   Utility functions							
*															 *
***************************-*********************************/
void GPS::char_noise(char identifiers[],int end)
{

  for(int i=0;i<=end;i++)
  {
    Serial.print(identifiers[i]);
  }

}
char* GPS::get_data_of_char_noise(char identifiers[],int end)
{
	char*data="9"; // data value will be overwritten in the next line
	data [0]=identifiers[0];
	char*tempo="9"; // tempo value will be overwritten in the next line
	tempo[0]=identifiers[0];//will be overwritten also
	
	for(int i=1;i<=end;i++)
  {
	tempo[0]=identifiers[i];
    strcat(data,tempo);
	delete[]tempo;

  }

}
/**************************-**********************************
*															 *
						Setters								
*															 *
***************************-*********************************/
void GPS::set_longitude(double l)
{
	longitude=l;
}
void GPS::set_latitude(double l)
{
	latitude=l;
}

/**************************-**********************************
*															 *
						Getters						
*															 *
***************************-*********************************/
//this function must be called in order to get data
void GPS::Read_data()
{
	longitude_doub=0;
    latitude_doub=0;

  while(1)
  {
	if (Serial.available())
	{
		if (Serial.read()=='$') /*to check, it is from GPS*/
		{

		Serial.readBytesUntil(',',mess_id,7);

		if (mess_id[2]=='G' && mess_id[3]=='G' && mess_id[4]=='A')
		{

        Serial.readBytesUntil(',',timing,12);
        Serial.readBytesUntil(',',Latitude,11);
        Serial.readBytesUntil(',',NS,3);
        Serial.readBytesUntil(',',Longitude,12);
        Serial.readBytesUntil(',',EW,3);
        Serial.readBytesUntil(',',Position,3);
        Serial.readBytesUntil(',',satallite,4);
        Serial.readBytesUntil(',',Random,5);
        Serial.readBytesUntil(',',altitude,8);

       
		latitude_doub = (Latitude[0]-48)*10+(Latitude[1]-48)+
                   ((Latitude[2]-48)*10+(Latitude[3]-48)+(Latitude[5]-48)*0.1+
                    (Latitude[6]-48)*0.01+(Latitude[7]-48)*0.001+(Latitude[8]-48)*0.0001+(Latitude[9]-48)*0.00001)/60.0;
		set_latitude(latitude_doub);

        longitude_doub = (Longitude[0]-48)*100+(Longitude[1]-48)*10+(Longitude[2]-48)+
                        ((Longitude[3]-48)*10+(Longitude[4]-48)+(Longitude[6]-48)*0.1+(Longitude[7]-48)*0.01+(Longitude[8]-48)*0.001+
                         (Longitude[9]-48)*0.0001+(Longitude[9]-48)*0.00001)/60.0;
		set_longitude(longitude_doub);
        
       
		}
	 else {}
     break;
      }
    }
  }
 }

double GPS::get_longitude()
{
	return longitude;
}
double GPS::get_latitude()
{
	return latitude;
}

void GPS::Serial_print_data ()
{
  longitude_doub=0;
  latitude_doub=0;

  while(1)
  {
if (Serial.available())
 {
    if (Serial.read()=='$') /*to check, it is from GPS*/
    {
      Serial.readBytesUntil(',',mess_id,7);

      if (mess_id[2]=='G' && mess_id[3]=='G' && mess_id[4]=='A'){

        Serial.readBytesUntil(',',timing,12);
        Serial.readBytesUntil(',',Latitude,11);
        Serial.readBytesUntil(',',NS,3);
        Serial.readBytesUntil(',',Longitude,12);
        Serial.readBytesUntil(',',EW,3);
        Serial.readBytesUntil(',',Position,3);
        Serial.readBytesUntil(',',satallite,4);
        Serial.readBytesUntil(',',Random,5);
        Serial.readBytesUntil(',',altitude,8);

        //Printing readings
        Serial.print("GPS");
        Serial.print(",");

        Serial.println("psition fix: ");
        char_noise(Position,1);
		
        Serial.println("UTC position: ");
        char_noise(timing,10);
       
        Serial.print("latitude: ");
        Serial.print(",");
		latitude_doub = (Latitude[0]-48)*10+(Latitude[1]-48)+(Latitude[2]-48)*10+((Latitude[3]-48)+(Latitude[5]-48)*0.1+(Latitude[6]-48)*0.01+(Latitude[7]-48)*0.001+(Latitude[8]-48)*0.0001+(Latitude[9]-48)*0.00001)/60;
		Serial.print(latitude_doub,5);

        Serial.print("longitude: ");
        longitude_doub = (Longitude[0]-48)*100+(Longitude[1]-48)*10+(Longitude[2]-48)+((Longitude[3]-48)*10+(Longitude[4]-48)+(Longitude[6]-48)*0.1+(Longitude[7]-48)*0.01+(Longitude[8]-48)*0.001+(Longitude[9]-48)*0.0001+(Longitude[9]-48)*0.00001)/60;
        Serial.print(",");
        Serial.print(longitude_doub,5);
        Serial.print(",");
        
        Serial.print("satallites: ");
        char_noise(satallite,2);
        Serial.print(",");

        Serial.println("altitude: ");
        char_noise(Altitude,6);
        Serial.print(",");
		
        Serial.println("NS indicator: ");
        char_noise(NS,1);
        Serial.print(",");

        Serial.println("EW indicator: ");
        char_noise(EW,1);
        Serial.print(",");
        Serial.println(" ");
        //=======================================
       
 }
 else {}
 break;
      }
    }
  }
}


