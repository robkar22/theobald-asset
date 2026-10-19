

#pragma once
#include "database.hpp"
#include "http.hpp"

HttpResponse handle_request(const HttpRequest& request,Database& db);

std::string escape_json(const std::string &input);
