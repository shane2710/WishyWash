# WishyWash
Observe serial communications among a network of washers and dryers.  Utilize silent time on the low-speed UART to join in on the conversation!  talk dirty to devices designed to clean.

Using a logic analyzer and some intellectual logic, I tapped into the laundry network in my dorm.  After collecting and studying information and probing signal responses with a PIC24 board with code I developed, I was able to decipher a useful command set for laundry machine control.  This command set includes the ability to check which machines are currently washing / drying, enable or disable them, and spoof a washer / dryer's start signal to start the load.  fun stuff!!
