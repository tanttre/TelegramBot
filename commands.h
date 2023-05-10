#include "includes.h"

std::string get_time_as_string()
{
    time_t now = time(NULL);
    tm* pointer = localtime(&now);
    char buffer[32];
    strftime(buffer, 32, "%c", pointer);
    return buffer;
}

static size_t Writer(char* buffer, size_t size, size_t nmemb, std::string *html)
{
    int result = 0;

    if (buffer != NULL)
    {
        html->append(buffer, size * nmemb);
        result = size * nmemb;
    }
    return result;
}

std::string get_request(std::string link)
{
    CURL* curl;
    std::string data;
    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, link.c_str()); 
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, Writer);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    return data;
}

float get_currency(char what)
{
    auto js_obj = nlohmann::json::parse(get_request("https://www.cbr-xml-daily.ru/daily_json.js"));
    if (what == 'u')
        return js_obj["Valute"]["USD"]["Value"].get<float>();
    else
        return js_obj["Valute"]["EUR"]["Value"].get<float>();
    return -1;
}