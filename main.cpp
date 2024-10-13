#include "rest_api.h"
#include <iostream>
#include <string>
#include <map>
#include <regex>

using namespace std;

map<string, string> parseJsonWithRegex(const string& json) {
    map<string, string> result;
    regex pairRegex("\"(\\w+)\":\\s*(\"[^\"]*\"|\\w+)");
    smatch match;

    string::const_iterator searchStart(json.cbegin());
    while (regex_search(searchStart, json.cend(), match, pairRegex)) {
        //match1 is key match2 is
        string key = match[1].str();
        string value = match[2].str();

        //remove quotes
        if (value.front() == '"' && value.back() == '"') {
            value = value.substr(1, value.size() - 2);
        }

        result[key] = value;
        searchStart = match.suffix().first;  
    }

    return result;
}

int main() {
    
    string model;
    std::cout << "Enter LLM identifier: ";
    getline(cin, model);

    const string prompt_suffix = "Answer this question in a sinle line, Question: ";

    while (true) {
        RestClient client;
        const string url = "http://localhost:11434/api/generate";
        string user_query;
        cout << "$$$ ";
        getline(cin, user_query);

        if(user_query == "quit()") break;
        user_query = prompt_suffix+user_query;

        string jsonData = R"({
            "model": ")" + model + R"(",
            "prompt": ")" + string(user_query) + R"(",
            "stream":)" + string("false") + R"( 
    })";;
        
        //make request using our own wrapper.
        string response = client.post(url, jsonData);
        map<string, string> parsedJson = parseJsonWithRegex(response);
        cout << "====================\n";
        string key = "response";
        auto it = parsedJson.find(key);
        cout << model<<" says" << ": ";
        if (it != parsedJson.end()) {
            cout<< it->second;
        } else {
            std::cerr << "Error: Key 'response' not found in the response." << std::endl;
            throw std::runtime_error("Key 'response' not found");
        }
        std::cout << "\n====================\n" << std::endl;

    }

    return 0;
}
