/*Distance Sensor*/
#define CM 1 //Used to configure the ultrassonic read
#define IN 0
#define register_us_handler(A,B,C,D) register_handler(A, B, C, D)
void init_ultrasonic(void);
unsigned int read_ultrasonic(void); //Defined on ARCH
void configure_ultrasonic(unsigned int mode);
