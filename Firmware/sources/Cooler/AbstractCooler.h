#ifndef AbstractCooler_h
#define AbstractCooler_h

#define OFF		0
#define ON		1

class AbstractCooler
{
	public:
		virtual bool switchOn() = 0;
		virtual bool switchOff() = 0;
		virtual bool setIntensivity(int _intensivity) = 0;
		virtual int getIntensivity() = 0;
		virtual int getState() = 0;
	protected:
		int state;
		int intensivity;
};

#endif

