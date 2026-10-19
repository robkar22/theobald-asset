#pragma once

#include <string>
#include <optional>

struct HttpRequest {
    std::string method;
    std::string path;
    std::string version;
    std::string body;
};

struct HttpResponse {
    int status = 200;
    std::string body;
    std::string content_type = "text/plain";
};


std::string build_http_response(const HttpResponse& response);
std::optional<HttpRequest> parse_http_request(const std::string &raw_request);



