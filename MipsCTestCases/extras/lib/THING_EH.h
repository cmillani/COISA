/*Event Handler*/

void eh_init(void);
short int register_handler(short int event_id, void (*handler)(void), char * evname, ...);
short int remove_handler(short int event_id, void (*handler)(void), char * evname);