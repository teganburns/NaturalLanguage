
# Natural Language API

This repo provides an example ) of how to use [Google's NaturalLanguage API](https://cloud.google.com/natural-language/) in C++ with [libcurl]. This was testing using Arch linux and should work with other linux distros.

Please note that the Natural Language API is being updated fairly requently so this example likely to become void (until updated) in the future.


# Building
To get started you will want to follow the directions from the [Getting Started](https://cloud.google.com/natural-language/docs/getting-started) section of the API. 

- Most importantly you will need to use [gcloud] for the authentication process. 
- After you are able to make a cURL request go ahead and download [libcurl] for your system.
- To compile you will need [make] so grab that if you don't already have it. 

```
cd NaturalLanguage/
make
./main_cpp [YOUR_REQUEST_HERE]
```

[gcloud]: https://cloud.google.com/sdk/docs/
[libcurl]: https://curl.haxx.se/libcurl/
[make]: https://www.gnu.org/software/make/

