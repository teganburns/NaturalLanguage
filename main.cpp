#include <iostream>
#include <unistd.h>
#include <thread>
#include <string.h>
#include <stdio.h>


// LIBCURL //
#include <curl/curl.h>

using namespace std;


std::string exec(const char* cmd) {
    char buffer[128];
    std::string result = "";
    std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
    if (!pipe) throw std::runtime_error("popen() failed!");
    while (!feof(pipe.get())) {
        if (fgets(buffer, 128, pipe.get()) != NULL)
            result += buffer;
    }

    result += "\b\b";
    return result;
}

struct MemoryStruct {
  char *memory;
  size_t size;
};

static size_t
WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)userp;

  mem->memory = (char *)realloc(mem->memory, mem->size + realsize + 1);
  if(mem->memory == NULL) {
    /* out of memory! */
    printf("not enough memory (realloc returned NULL)\n");
    return 0;
  }

  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;

  return realsize;
}

int main(int argc, char** argv) {


    string my_request = "";
    if (argc < 2){
        cout << "Usage: ./main_cpp [STRING_TO_SEND]" << endl;
        my_request = "Who is Linus Torvalds?";
    }else{
        for (int i=1;i!=argc;i++){
            my_request += argv[i];
            my_request += " ";
        }
    }

    string acess_key = exec("gcloud auth print-access-token");

    my_request = " {\"document\" :{\"type\" :\"PLAIN_TEXT\" ,\"content\":\"" + my_request + "\"}, \"encodingType\":\"UTF8\" }";
    //static const char *data = " {\"document\" :{\"type\" :\"PLAIN_TEXT\" ,\"content\":\"Michelangelo Caravaggio, Italian painter, is known for 'The Calling of Saint Matthew'.\"}, \"encodingType\":\"UTF8\" }";
    static const char *data = my_request.c_str();

    string url_analyzeEntities = "https://language.googleapis.com/v1beta1/documents:analyzeEntities";
    string url_analyzeSentiment = "https://language.googleapis.com/v1beta1/documents:analyzeSentiment";
    string url_annotateText = "https://language.googleapis.com/v1beta1/documents:annotateText";

    // CURL //

    string auth = ("Authorization: Bearer " + acess_key );

    cout << "Auth : " << auth << "\nData: " << data << endl;

    struct MemoryStruct chunk;
    chunk.memory = (char*)malloc(1);  /* will be grown as needed by realloc above */
    chunk.size = 0;

    CURL *curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if(curl) {
        struct curl_slist *headers=NULL; /* init to NULL is important */
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, auth.c_str());

        curl_easy_setopt(curl, CURLOPT_URL, url_analyzeEntities.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

        res = curl_easy_perform(curl);
        cout << "request sent waiting for response" << endl;
        if(res != CURLE_OK){
          cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;
        }else{
            cout << "Result: " << chunk.memory << endl;
        }

        /* always cleanup */
        curl_slist_free_all(headers); /* free the header list */
        curl_easy_cleanup(curl);
      }

      curl_global_cleanup();

    // END OF CURL //

    return 0;
}
