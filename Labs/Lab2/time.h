class Time{
	public:
		//constructors
		Time();
		Time(int hr, int min, int sec);
		Time(const Time &timeToCopy);

		//accessors
		int getHour() const;
		int getMinute() const;
		int getSecond() const;

		//mutators
		void setHour(int hr);
		void setMinute(int min);
		void setSecond(int sec);

		//output
		void PrintAMPM() const;
	private:
		int hour;
		int minute;
		int second;
};

bool IsEarlierThan(const Time& t1, const Time& t2);