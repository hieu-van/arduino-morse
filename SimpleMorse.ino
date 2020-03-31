const byte pinNum = 2;
// Dot duration in milliseconds
const unsigned long dur = 80;
const String msg = "SOS";

String charToMorse(const char ch) {
	String chStr = String(ch);
	chStr.toUpperCase();

	switch (chStr[0]) {
		case 'A':
			return ".-";
		case 'B':
			return "-...";
		case 'C':
			return "-.-.";
		case 'D':
			return "-..";
		case 'E':
			return ".";
		case 'F':
			return "..-.";
		case 'G':
			return "--.";
		case 'H':
			return "....";
		case 'I':
			return "..";
		case 'J':
			return ".---";
		case 'K':
			return "-.-";
		case 'L':
			return ".-..";
		case 'M':
			return "--";
		case 'N':
			return "-.";
		case 'O':
			return "---";
		case 'P':
			return ".--.";
		case 'Q':
			return "--.-";
		case 'R':
			return ".-.";
		case 'S':
			return "...";
		case 'T':
			return "-";
		case 'U':
			return "..-";
		case 'V':
			return "...-";
		case 'W':
			return ".--";
		case 'X':
			return "-..-";
		case 'Y':
			return "-.--";
		case 'Z':
			return "--..";
		case '0':
			return "-----";
		case '1':
			return ".----";
		case '2':
			return "..---";
		case '3':
			return "...--";
		case '4':
			return "....-";
		case '5':
			return ".....";
		case '6':
			return "-....";
		case '7':
			return "--...";
		case '8':
			return "---..";
		case '9':
			return "----.";
	}
}

String strToSignal(const String msg) {
	String signal;

	for (unsigned long i = 0; i < msg.length(); i++) {
		if (msg[i] == ' ') {
			signal += "0000000";
		}
		else if (isAscii(msg[i])) {
			String ch = charToMorse(msg[i]);
			for (unsigned long j = 0; j < ch.length(); j++) {
				switch (ch[j]) {
					case '.':
						signal += "1";
						break;
					case '-':
						signal += "111";
						break;
				}
				signal += "0";
			}
			if (i != (msg.length() - 1))
				signal += "000";
		}
	}

	return signal;
}

void emitMorse(const String msg) {
	String morse = strToSignal(msg);
	
	for (unsigned long i = 0; i < morse.length(); i++) {
		if (morse[i] == '1') {
			// Signal on
			digitalWrite(pinNum, HIGH);
			delay(dur);
			digitalWrite(pinNum, LOW);
		} else {
			// Signal off
			digitalWrite(pinNum, LOW);
			delay(dur);
		}
	}
}

void setup() {
	pinMode(pinNum, OUTPUT);
	digitalWrite(pinNum, LOW);

	emitMorse(msg);
}

void loop() {
}
