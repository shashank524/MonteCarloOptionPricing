#include <iostream>
#include <curl/curl.h>

// Callback function to receive the response from the web API
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}

int main() {
    CURL* curl;
    CURLcode res;
    std::string url = "https://query1.finance.yahoo.com/v7/finance/download/XYZ?period1=1640995200&period2=1672444800&interval=1d&events=history";
    std::string response;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        // Set the URL to fetch historical data from Yahoo Finance
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        // Set the callback function to receive the response
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        // Perform the request
        res = curl_easy_perform(curl);

        // Check for errors
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        } else {
            // Process the response
            std::cout << "Historical data response: " << response << std::endl;
        }

        // Clean up
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();

    return 0;
}