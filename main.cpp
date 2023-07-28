#include <iostream>
#include <future>
#include <string>
#include <curl/curl.h>

#include "Forecast.h"

static size_t writeStringCallback(char* ptr, size_t size, size_t nmemb, void* userdata) {
	std::string* str = (std::string*) userdata;
	size_t len = size * nmemb;
	str->append(ptr, len);
	return len;
}

template <typename T>
T downloadData(const char* url, T (*deserialize)(const std::string& jsonData)) {
    T forecast;
    CURL* curl = curl_easy_init();
    if (curl) {
        std::string response;

        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeStringCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        CURLcode res = curl_easy_perform(curl);

        if (res == CURLE_OK) {
            long httpCode = 0;
            curl_easy_getinfo (curl, CURLINFO_RESPONSE_CODE, &httpCode);
            if (httpCode == 200) {
                if (response.empty()) {
                    std::cerr << "Invalid request!" << std::endl;
                } else {
                    forecast = deserialize(response);

                    std::cout << forecast.timezone << ":" << forecast.latitude << ":" << forecast.longitude << std::endl;
                }
            } else {
                std::cerr << "Error http status code: " << httpCode << std::endl;
            }
        } else {
            std::cerr << "Curl error code: " << res << std::endl;
        }

        curl_easy_cleanup(curl);

    } else {
        std::cout << "Curl initialisation failed." << std::endl;
    }

    return forecast;
}

int main(int, char**){

    std::cout << "Before get" << std::endl;

    std::future<Forecast> fl = std::async(std::launch::async, []( ) -> Forecast {
        return downloadData<Forecast>("https://api.open-meteo.com/v1/forecast?latitude=52.52&longitude=13.41", forecastFromJson);
    });

    std::cout << "After get" << std::endl;
}
