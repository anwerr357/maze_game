#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <curl/curl.h>   // For making HTTP requests
#include "json.hpp"      // For parsing JSON data
#include <random>        // For std::shuffle
#include <ctime>         // For seeding RNG

using json = nlohmann::json;
using namespace std;


// Function to handle HTTP response data
size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* s) {
    size_t newLength = size * nmemb;
    try {
        s->append((char*)contents, newLength);
    } catch (bad_alloc& e) {
        return 0;  // Handle memory issue
    }
    return newLength;
}

// Function to fetch data from the API
string fetchData(const string& url) {
    CURL* curl;
    CURLcode res;
    string readBuffer;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if (res != CURLE_OK) {
            cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;
            return "";
        }
    }
    return readBuffer;
}

// Function to extract country names by region & country-region map
pair<map<string, vector<string>>, map<string, string>> extractCountriesByRegion(const string& jsonData) {
    map<string, vector<string>> countriesByRegion;
    map<string, string> countryToRegion;  // NEW: Stores country -> region mapping
    
    try {
        json data = json::parse(jsonData);

        for (const auto& country : data) {
            string region = country["region"].is_null() ? "Unknown" : country["region"];
            string name = country["name"]["common"].is_null() ? "Unknown" : country["name"]["common"];
            
            countriesByRegion[region].push_back(name);
            countryToRegion[name] = region;  // Store mapping
        }
    } catch (const exception& e) {
        cerr << "Error parsing JSON: " << e.what() << endl;
    }
    
    return {countriesByRegion, countryToRegion};
}
// Function to get 100 random countries from the extracted data
vector<string> getRandomCountries(const map<string, vector<string>>& countriesByRegion, int count = 100) {
    vector<string> allCountries;

    // Flatten the country list
    for (const auto& [region, countries] : countriesByRegion) {
        allCountries.insert(allCountries.end(), countries.begin(), countries.end());
    }

    // If there are fewer than 'count' countries, return all available
    if (allCountries.empty()) return {"No countries available"};
    if (allCountries.size() <= count) return allCountries;

    // Seed the random generator
    random_device rd;
    mt19937 g(rd());

    // Shuffle using std::shuffle
    shuffle(allCountries.begin(), allCountries.end(), g);

    // Select the first 'count' countries
    return vector<string>(allCountries.begin(), allCountries.begin() + count);
}

// Function to find and print a country's region
void findRegion(const map<string, string>& countryToRegion, const string& country) {
    auto it = countryToRegion.find(country);
    if (it != countryToRegion.end()) {
        cout << country << " belongs to region: " << it->second << endl;
    } else {
        cout << "Country not found." << endl;
    }
}