#include <iostream>
#include <set>
#include <string>
#include <vector>

	typedef std::set<std::pair<std::string,std::string> > set_of_word_pairs;


bool common(const std::string &a, const std::string &b);
void common(set_of_word_pairs &answer, const std::vector<std::string>& words, int a, int b);
void common(set_of_word_pairs &answer, const std::vector<std::string>& words, int a);
set_of_word_pairs common(const std::vector<std::string>& words);

int main(){



	std::vector<std::string> words={"apple", "boat", "cat","dog", "egg", "fig"};

	set_of_word_pairs wordPairs=common(words);

	for(set_of_word_pairs::iterator iter=wordPairs.begin();iter!=wordPairs.end();iter++){
		std::cout<<iter->first<<", "<<iter->second<<"\n";
	}

}


bool common(const std::string &a, const std::string &b) {
		for (int i = 0; i < a.size(); i++)
			for (int j = 0; j < b.size(); j++)
				if (a[i] == b[j]) return true;
					return false;
}




void common(set_of_word_pairs &answer, const std::vector<std::string>& words, int a, int b) {
	if(b < words.size()) {
		if(common(words[a], words[b])) {
			std::pair<std::string, std::string> pair;
			pair.first = words[a];
			pair.second = words[b];
			answer.insert(pair);
		}
		common(answer, words, a, b + 1);
	}
}


void common(set_of_word_pairs &answer, const std::vector<std::string>& words, int a) {
	if(a < words.size()) {
		common(answer, words, a, a + 1);
		common(answer, words, a + 1);
	}
}


set_of_word_pairs common(const std::vector<std::string>& words) {
	set_of_word_pairs setPair;
	common(setPair, words, 0);
	return setPair;
}

