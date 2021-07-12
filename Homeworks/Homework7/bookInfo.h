#ifndef _bookInfo_h_
#define _bookInfo_h_

#include<list>
#include<string>

class BookInfo{
	public:
		BookInfo(){numAvailable=0; numOut=0;};

		void addNumOut(int num){numOut+=num;};
		void addNum(int num){numAvailable+=num;};
		void addPatron(std::string newPatron){patrons.push_back(newPatron);};
		void removePatron(std::string newPatron){for(std::list<std::string>::iterator iter=patrons.begin();iter!=patrons.end();iter++)if(*iter==newPatron){patrons.erase(iter);break;}};

		std::list<std::string> getList(){return patrons;};
		int getNumOut(){return numOut;};
		int getNum(){return numAvailable;};
	private:
		int numAvailable;
		int numOut;
		std::list<std::string> patrons;
};

#endif