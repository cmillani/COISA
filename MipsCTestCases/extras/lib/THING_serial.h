/*Serial Comm*/

void send_byte(unsigned char byte); //Defined on ARCH
char read_byte(void);
void serial_configure(unsigned int baudrate);
