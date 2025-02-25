#ifndef GETCOUNTRIES_HPP
#define GETCOUNTRIES_HPP

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <curl/curl.h>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

// Function to handle HTTP response data
size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* s);

// Function to fetch data from the API
string fetchData(const string& url);

// Function to extract country names by region
// map<string, vector<string>> extractCountriesByRegion(const string& jsonData);
pair<map<string, vector<string>>, map<string, string>> extractCountriesByRegion(const string& jsonData) ;

vector<string> getRandomCountries(const map<string, vector<string>>& countriesByRegion, int count = 100);

#endif // GETCOUNTRIES_HPP
