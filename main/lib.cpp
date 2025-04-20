#include <iostream>
#include <string>
#include <curl/curl.h>

size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string *)userp)->append((char *)contents, size * nmemb);
    return size * nmemb;
}

int main()
{
    std::cout << "🚀 Program started." << std::endl;

    CURL *curl = curl_easy_init();
    std::string response;

    if (!curl)
    {
        std::cerr << "❌ curl_easy_init failed!" << std::endl;
        std::cin.get();
        return 1;
    }

    std::cout << "🔧 curl initialized successfully." << std::endl;

    curl_easy_setopt(curl, CURLOPT_URL, "https://www.example.com");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

    std::cout << "🌐 Performing curl request..." << std::endl;

    CURLcode res = curl_easy_perform(curl);

    if (res != CURLE_OK)
    {
        std::cerr << "❌ curl_easy_perform failed: " << curl_easy_strerror(res) << std::endl;
    }
    else
    {
        std::cout << "✅ curl_easy_perform success!" << std::endl;
        std::cout << "📄 Response:\n"
                  << response << std::endl;
    }

    curl_easy_cleanup(curl);
    std::cout << "🏁 Program finished. Press Enter to exit." << std::endl;
    std::cin.get();
    return 0;
}
