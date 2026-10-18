

#include "router.hpp"

HttpResponse handle_request(const HttpRequest& request)
{
    HttpResponse response;

    if (request.method == "GET" &&
        request.path == "/api/people") {
        response.body = "List of people";
    }
    else if (request.method == "GET" &&
             request.path == "/api/items") {
        response.body = "List of items";
    }
    else {
        response.status = 404;
        response.body = "Not Found";
    }

    return response;
}
