# Natural Language API

This repo provides an example of how to use (Google's NaturalLanguage 
API)[https://cloud.google.com/natural-language/] in c++ with 
(libcurl)[https://curl.haxx.se/libcurl/].

Please note that the  Natural Language API is still in Beta so this is likely to become void 
(until updated) in the future.

# Building
To get started you will want to follow the directions from the (Getting 
Started)[https://cloud.google.com/natural-language/docs/getting-started] section of the API.

After you are able to make a cURL request go ahead and download 
(libcurl)[https://curl.haxx.se/libcurl/] for your system.

To compile you will need (make)[https://www.gnu.org/software/make/] so grab that if you don't 
already have it. 

```
cd NaturalLanguage/
make
./main_cpp [YOUR_REQUEST_HERE]
```

Clean up with
```
make clean
```
