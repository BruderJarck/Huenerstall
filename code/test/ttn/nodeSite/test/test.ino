// counter
static int cnt = 0;
// log text to USART and toggle LED
static void initfunc (osjob_t* job) {
 // say hello
 debug_str("Hello World!\r\n");
 // log counter
 debug_val("cnt = ", cnt);
 // toggle LED
 debug_led(++cnt & 1);
 // reschedule job every second
 os_setTimedCallback(job, os_getTime()+sec2osticks(1), initfunc);
}
