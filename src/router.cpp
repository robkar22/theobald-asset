

#include "router.hpp"
#include "database.hpp"
#include <string>
#include <vector>

HttpResponse handle_request(const HttpRequest &request, Database &db) {
  HttpResponse response;

  if (request.method == "GET" && request.path == "/api/people") {
    std::vector<Person> people = db.get_people();
    response.content_type = "application/json";
    response.body = "[";
    bool first = true;

    for (const Person &p : people) {
      if (!first) {
        response.body += ",";
      }
      response.body += "{\"id\":";
      response.body += std::to_string(p.id);
      response.body += ",\"name\": \"";
      response.body += escape_json(p.name);
      response.body += "\"}";
      first = false;
    }
    response.body += "]";
  } else if (request.method == "GET" && request.path == "/api/items") {
    response.body = "List of items";
  } else {
    response.status = 404;
    response.body = "Not Found";
  }

  return response;
}

std::string escape_json(const std::string &input) {
  std::string output;

  for (char c : input) {
    if (c == '"') {
      output += "\\\"";
    } else if (c == '\n') {

      output += "\\n";
    } else if (c == '\\') {
      output += "\\\\";
    } else if (c == '\t') {
      output += "\\t";
    } else if (c == '\r') {
      output += "\\r";

    } else {
      output += c;
    }
  }

  return output;
}
