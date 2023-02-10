#pragma once
#include <iostream>
#include <vector>
#include <map>
class Utils 
{
	public:
	static std::vector<std::string> split(std::string data, std::string delimiter) 
	{
		size_t index = 0;
		std::vector<std::string> results;
		while(true)
		{
			
			size_t delindex = data.find(delimiter);
			if (delindex == std::string::npos)
			{
				results.push_back(data);
				break;
			}
			std::string temp = data.substr(0, delindex);
			results.push_back(temp);
			data = data.substr(delindex + delimiter.length(), data.length() - delindex + delimiter.length());
			index += delindex;
		
		}
		return results;
	}

	static void coutBytes(unsigned char* data, int lnt) 
	{
		std::cout << "\n\n----------------BYTE DATA------------------\n\n";
		for (int a = 0; a < lnt; a++) 
		{

			int c = (int)data[a];
			std::cout << c<< " ";
		}
		std::cout << "\n\n----------------BYTE DATA------------------\n\n";
	}


	static std::map<std::string, std::string> stringToMap(std::string data, std::string delimiter) 
	{
		std::map<std::string, std::string> result;
		std::vector<std::string> splitted = split(data, "\r\n");
		for (int a = 0; a < splitted.size(); a++)
		{
			std::vector<std::string> tempsplit = split(splitted.at(a), delimiter);
			if (tempsplit.size() == 2) {
				
				result.insert(std::pair<std::string, std::string>(tempsplit.at(0), tempsplit.at(1)));
			}
		}
		return result;
	}



};