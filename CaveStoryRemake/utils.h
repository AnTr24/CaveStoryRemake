/*************************************************************************
File name:		utils.h
Description:	Utility class
**************************************************************************/

//#include guard.  Prevents double definitions
#ifndef UTILS_H
#define UTILS_H

//includes
#include <string>
#include <vector>
#include <algorithm>

//declarations

//Class definition
class Utils {
public:
	//unsigned int Split
	//split a string <txt> everywhere a certain character <ch> is found
	//store the resulting substrings in a vector <str>
	//other: clears <strs> of previous contents 
	//"dog,cat,bird" (split on ',')-> [dog][cat][bird]
	static unsigned int Split(const std::string &txt, std::vector<std::string> &strs, char ch) {
		int pos = txt.find(ch);	//position of first matching char
		int initialPos = 0;		//character position offset
		strs.clear();			//empty out vector to add new substrings

		//loop through string until there is no more matches
		while(pos != std::string::npos) {
			strs.push_back(txt.substr(initialPos, pos - initialPos));	//grab a substring between char matches to add to the vector
			initialPos = pos + 1;

			pos = txt.find(ch, initialPos);
		}
		//Add the last substirng after the final match
		if (initialPos < txt.size())
		{
				strs.push_back(txt.substr(initialPos, txt.size() - initialPos));
		}
		//strs.push_back(txt.substr(initialPos, std::min<int>(pos, txt.size() - (initialPos + 1))));
		
		return strs.size();
	}
private:
};
#endif	//end of #include guard