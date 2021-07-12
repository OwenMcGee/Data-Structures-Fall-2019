#ifndef __jagged_Array_h_
#define __jagged_Array_h_

#include <string>

template <class T> class JaggedArray{
	private:
		int bins;
		int* counts;
		T** unpacked_values;
		int* offsets;
		T* packed_values;
		bool packed;
	public:
		//constructors and destructor
		JaggedArray(int size);
		JaggedArray(const JaggedArray & array);
		~JaggedArray();
		//ALSO I NEED A DESTRUCTOR APPARENTLY

		//accessors
		int numElements() const;
		int numBins() const;
		int numElementsInBin(const int bindex) const;		//does this const matter if I'm passing bin by copy???
		T getElement(const int binIndex, const int elementIndex) const;
		bool isPacked() const;
		std::string print() const;

		//mutators
		void addElement(const int binIndex, const T & element);
		void removeElement(const int binIndex, const int elementIndex);
		void clear();

		void pack();
		void unpack();
};

#endif