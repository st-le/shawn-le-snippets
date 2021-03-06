
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <iostream>

using namespace std;

class CSource {
public:
	__event void MyEvent(int nValue);
};


class CReceiver {
public:
	void MyHandler1(int nValue) {
		printf_s("MyHandler1 was called with value %d.\n", nValue);
	}

	void MyHandler2(int nValue) {
		printf_s("MyHandler2 was called with value %d.\n", nValue);
	}

	void hookEvent(CSource* pSource) {
		__hook(&CSource::MyEvent, pSource, &CReceiver::MyHandler1);
		__hook(&CSource::MyEvent, pSource, &CReceiver::MyHandler2);
	}

	void unhookEvent(CSource* pSource) {
		__unhook(&CSource::MyEvent, pSource, &CReceiver::MyHandler1);
		__unhook(&CSource::MyEvent, pSource, &CReceiver::MyHandler2);
	}
};

int main() {
	CSource source;
	CReceiver receiver;

	receiver.hookEvent(&source);
	__raise source.MyEvent(123);
	getchar();
	receiver.unhookEvent(&source);


}