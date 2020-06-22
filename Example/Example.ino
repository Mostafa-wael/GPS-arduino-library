#include <GPS.h>
GPS* Pgps=new GPS;

void setup() {
  

}

void loop() {
 Pgps->Read_data();
 Pgps->Serial_print_data();
}
