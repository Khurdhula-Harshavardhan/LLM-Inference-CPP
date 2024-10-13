#include "rest_api.h"
#include <iostream>
#include <sstream>

RestClient::RestClient() { //constrcutor
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
}

RestClient::~RestClient() { //destructor
    if (curl) {
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
}

size_t RestClient::WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
} //handle call back

//wrapper for get
std::string RestClient::get(const std::string& url) {
    std::string readBuffer;
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        
        if (res != CURLE_OK) {
            std::cerr << "GET request failed: " << curl_easy_strerror(res) << std::endl;
        }
    }
    return readBuffer;
}

//wrapper for post
std::string RestClient::post(const std::string& url, const std::string& data) {
    std::string readBuffer;
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "POST request failed: " << curl_easy_strerror(res) << std::endl;
        }
    }
    return readBuffer;
}

//rwapper for put
std::string RestClient::put(const std::string& url, const std::string& data) {
    std::string readBuffer;
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr<<"PUT request failed: "<< curl_easy_strerror(res)<<std::endl;
        }
    }
    return readBuffer;
}

//wrapper for delete
std::string RestClient::del(const std::string& url) {
    std::string readBuffer;
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        
        if (res != CURLE_OK) {
            std::cerr << "DELETE request failed: " << curl_easy_strerror(res) << std::endl;
        }
    }
    return readBuffer;
}
