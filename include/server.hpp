#include <httplib.h>
#include <util.hpp>

namespace LocationServer {
void handle_requests(httplib::Server&& svr) {
  svr.Get("/hi", [](const httplib::Request& req, httplib::Response& res) {
    res.set_content("Hello Bitch!!", "text/plain");
  });

  svr.Get("/nodes", [](const httplib::Request& req, httplib::Response& res) {
    auto node_string = fetchNodes();
    res.set_content(node_string, "text/plain");
  });

  // svr.Get("/vdi", [](const httplib::Request& req, httplib::Response& res) {
  //   std::string names_string{};
  //   for (const auto& name : app.fetchVDINames()) {
  //     names_string += name + "\n";
  //   }
  //   res.set_content(names_string, "text/plain");
  // });

  // svr.Get("/characters", [](const Request& req, Response& res) {
  //   std::string names_string{};
  //   for (const auto& name : app.fetchCharacterTypes()) {
  //     names_string += name + "\n";
  //   }
  //   res.set_content(names_string, "text/plain");
  // });

  // svr.Get("/vdi/character", [](const Request& req, Response& res) {
  //   auto param_it = req.params.find("name");
  //   if (param_it != req.params.end()) {
  //     auto name = param_it->second;
  //     auto character = app.fetchCharacterForName(name);
  //     std::string return_string{name + "'s character: " + character + "\n"};
  //     res.set_content(return_string, "text/plain");
  //   }
  // });

  // svr.Get("/vdi/character/update", [](const Request& req, Response& res) {
  //   auto name_it = req.params.find("name");
  //   auto char_it = req.params.find("character");
  //   if (name_it != req.params.end() && char_it != req.params.end()) {
  //     auto update_result =
  //         app.updateCharacterForName(name_it->second, char_it->second);
  //     res.set_content(update_result ? "Success" : "Failure", "text/plain");
  //   }
  // });

  svr.Get("/stop", [&](const httplib::Request& req, httplib::Response& res) { svr.stop(); });
}  // namespace TestServer

void start_http_server() {
  httplib::Server svr{};
  handle_requests(std::move(svr));
  std::cout << "Starting HTTP server.." << std::endl;
  std::cout << "Connect to http://localhost:9820" << std::endl;
  svr.listen("localhost", 9820);
}
}  // namespace TestServer