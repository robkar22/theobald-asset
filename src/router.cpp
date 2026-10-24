

#include "router.hpp"
#include "database.hpp"
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

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
  } else if (request.method == "POST" && request.path == "/api/people") {
    //parse the json
    auto json = nlohmann::json::parse(request.body, nullptr, false);

    if (json.is_discarded() || !json.is_object() || !json.contains("name") ||
        !json["name"].is_string()) {
      response.status = 400;
      response.body = "Invalid JSON or missing name";
      return response;
    }
    //extract name and validate name 
    std::string name = json["name"].get<std::string>();
    bool only_spaces = std::all_of(
      name.begin(),
      name.end(),
      [](unsigned char c){
        return::isspace(c);
      }
    );
    if (only_spaces){
      response.status = 400;
      response.body = "Name cannot be empty";
    return response;
    }
    //add person
    if (db.add_person(name)) {
      response.status = 201;
      response.body = "Person added";
    } else {
      response.status = 500;
      response.body = "Database error";
    }

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
