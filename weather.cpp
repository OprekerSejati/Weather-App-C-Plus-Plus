#include <iostream>  
#include <curl/curl.h>  
#include <string>  
  
using namespace std;  
  
// Function to handle the response from the API  
size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {  
    ((string*)userp)->append((char*)contents, size * nmemb);  
    return size * nmemb;  
}  
  
// Function to get weather data  
void getWeather(const string& city, const string& apiKey) {  
    CURL* curl;  
    CURLcode res;  
    string readBuffer;  
  
    // Construct the API URL  
    string url = "http://api.openweathermap.org/data/2.5/weather?q=" + city + "&appid=" + apiKey + "&units=metric";  
  
    curl = curl_easy_init();  
    if (curl) {  
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());  
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);  
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);  
        res = curl_easy_perform(curl);  
        curl_easy_cleanup(curl);  
  
        // Output the weather data  
        cout << "Weather data for " << city << ":\n" << readBuffer << endl;  
    }  
}  
  
int main() {  
    string city;  
    string apiKey = "your_actual_api_key_here"; // Use your active API key here  
  
    cout << "Enter the city name: ";  
    getline(cin, city);  
  
    getWeather(city, apiKey);  
  
    return 0;  
}  
