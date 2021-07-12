#include "jagged_Array.h"
#include <iostream>

	template <class T> JaggedArray<T>::JaggedArray(int size){
		bins=size;
		counts=new int[size];
		unpacked_values=new T*[size];
		offsets=NULL;
		packed_values=NULL;
		packed=false;
	}

	template <class T> JaggedArray<T>::JaggedArray(const JaggedArray & array){
		bins=array.bins;
		counts=array.counts;
		unpacked_values=array.unpacked_values;
		offsets=array.offsets;
		packed_values=array.packed_values;
		packed=array.packed;
	}

	template <class T> JaggedArray<T>::~JaggedArray(){
		delete counts;
		if(packed){
			delete unpacked_values;
			delete offsets;
		}
		else{
			for(int i=0;i<bins;i++){
				delete packed_values[i];
			}
			delete packed_values;
			delete counts;
		}

	}

	template <class T> int JaggedArray<T>::numElements() const{
		if(packed){
			//CHECK THIS LINE
			return packed_values.size();
		}
		else{
			int total=0;
			//unsigned?
			for(unsigned int i=0;i<bins;i++){
				total+=counts[i];
			}
			return total;
		}
	}

	template <class T> int JaggedArray<T>::numBins() const{
		return bins;
	}

	//consider doing some error checking here (make sure bin is less than the number of bins)
	template <class T> int JaggedArray<T>::numElementsInBin(const int bindex) const{	//bindex is hilarious and it's staying
		if(packed){
			//finish (and generally rehaul) this half of the method
			int currentBin=0;
			int currentBinIndex=0;
			for(int i=0;i<bins;i++){
				if(offsets[i]!=currentBinIndex){
					currentBin++;
					currentBinIndex=offsets[i];
				}
				if(currentBin==bindex){

				}
			}
		}
		else{
			return counts[bindex];
		}
	}

	//error check bin and element
	template <class T> T JaggedArray<T>::getElement(const int binIndex, const int elementIndex) const{
		if(packed){

		}
		else{
			return unpacked_values[binIndex][elementIndex];
		}
	}

	template <class T> bool JaggedArray<T>::isPacked() const{		//THIS CAN PROBABLY BE DONE IN THE .H FILE (figure it out, but keep it here actually)
		return packed;
	}

	//error check
	template <class T> void JaggedArray<T>::addElement(const int binIndex, const T & element){
		if(packed){
			std::cerr<<"Cannot add elements while the JaggedArray is packed";
		}
		//CHECK THIS NONSENSE HEAVILY
		T* temp=new T[unpacked_values[binIndex].size()+1];
		for(int i=0;i<temp.size()-1;i++){
			temp[i]=&unpacked_values[i];
		}
		//check using element like this is okay
		temp[temp.size()-1]=element;
		unpacked_values[binIndex]=temp;
		//make sure this is okay with element! Think I need to make a copy of it
		unpacked_values[binIndex].push_back(element);
	}

	template <class T> void JaggedArray<T>::removeElement(const int binIndex, const int elementIndex){
		if(packed){
			std::cerr<<"Cannot remove elements while the JaggedArray is packed";
		}
		T* temp=new T[unpacked_values[binIndex].size()-1];
		int j=0;
		for(int i=0;i<temp.size()+1;i++){
			if(j==elementIndex){
				j++;
			}
			temp[i]=unpacked_values[binIndex][j];
			j++;
		}
		unpacked_values[binIndex]=temp;
	}

	template <class T> void JaggedArray<T>::clear(){

		delete offsets;
		delete packed_values;
		if(!packed){
			for(int i=0;i<bins;i++){
				delete unpacked_values[i];
			}
		}
		counts=new int[bins];
		unpacked_values=new T*[bins];
		packed=false;
	}

	template <class T> void JaggedArray<T>::pack(){
		//make sure to check that this works
		//also make sure to well document it
		if(packed){
			return;
		}
		offsets=new int[bins];
		packed_values=new int[numElements];
		int k=0;
		for(int i=0;i<bins;i++){
			for(int j=0;j<counts[i];j++){
				//also figure out how to initialize the offsets array
				packed_values[i+j]=unpacked_values[i][j];

			}
		}

		packed=true;
		delete counts;
		delete unpacked_values;
	}

	template <class T> void JaggedArray<T>::unpack(){
		//make sure to check and well-document
		if(!packed){
			return;
		}

		


		packed=false;
		delete offsets;
		delete packed_values;
	}

