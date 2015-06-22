/*Encoder Sensor*/

#define RIGHT 1
#define LEFT 0

unsigned int read_encoder_counter(int side); //Defined on ARCH
unsigned int read_encoder_time(int side);
void start_encoder(void);
