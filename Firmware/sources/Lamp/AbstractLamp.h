#ifndef AbstractLamp_h
#define AbstractLamp_h

#define OFF		0
#define ON		1

class AbstractLamp {
public:
	virtual bool switchOn(void) = 0;
	virtual bool switchOff(void) = 0;
	virtual unsigned long getCount(void) = 0;
	int getState(void);

protected:
	int state;
};

#endif

