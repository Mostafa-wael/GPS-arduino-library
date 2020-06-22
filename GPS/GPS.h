#pragma once
#include "Arduino.h"

class GPS  // for Latitude,Longitude,Altitude,timing , etc...
{
  private :
		char mess_id[6];
		char Latitude[10];
		char Longitude[11];
		char satallite[3];
		char Random[4];
		char Position[2];
		char Altitude[7];
		char timing[11];
		char EW[2];
		char NS[2];
//===========================================
		double longitude_doub;
		double latitude_doub;

		double longitude;
		double latitude;
		char* altitude;
		char* NS_indicator;
		char* EW_indicator;
		char* psition_fix;
		char* UTC_position;
		char* satallites;
//===========================================
		void char_noise(char identifiers[],int end);
		char*get_data_of_char_noise(char identifiers[],int end);
//===========================================
		void set_longitude(double);
		void set_latitude(double);
   public : 
		GPS ();
		
		double  get_longitude();
		double  get_latitude();
		void Read_data();//should be used before getting any data
		void Serial_print_data ();
    
};


