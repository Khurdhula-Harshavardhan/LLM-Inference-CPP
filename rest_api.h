//rest_api.h
#ifndef REST_API_H
#define REST_API_H
#include <string>
#include <curl/curl.h>

class RestClient {
public:
    RestClient();
    ~RestClient();

    //function to make a GET request
    std::string get(const std::string& url);
    //function to make a POST request with data
    std::string post(const std::string& url, const std::string& data);
    //function to make a PUT request with data
    std::string put(const std::string& url, const std::string& data);
    //function to make a DELETE request
    std::string del(const std::string& url);

private:
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);
    CURL* curl;
    CURLcode res;
};

#endif // REST_API_H
