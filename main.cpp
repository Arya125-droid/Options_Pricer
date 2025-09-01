#include "crow_all.h"
#include "option_pricer.h"
#include <iostream>

// --- CORS Middleware ---
struct CORS {
    struct context {};

    void before_handle(crow::request&, crow::response& res, context&) {
        res.add_header("Access-Control-Allow-Origin", "*");
        res.add_header("Access-Control-Allow-Methods", "POST, OPTIONS");
        res.add_header("Access-Control-Allow-Headers", "Content-Type");
    }

    void after_handle(crow::request&, crow::response& res, context&) {
        // Ensure headers persist even if overwritten later
        if (!res.get_header_value("Access-Control-Allow-Origin").size()) {
            res.add_header("Access-Control-Allow-Origin", "*");
            res.add_header("Access-Control-Allow-Methods", "POST, OPTIONS");
            res.add_header("Access-Control-Allow-Headers", "Content-Type");
        }
    }
};

int main() {
    crow::App<CORS> app;   // <-- Enable middleware
    app.loglevel(crow::LogLevel::Info);

    CROW_LOG_INFO << "Starting C++ Option Pricer Server...";

    // --- Main Pricing Route ---
    CROW_ROUTE(app, "/price").methods(crow::HTTPMethod::Post)
    ([](const crow::request& req){
        CROW_LOG_INFO << "Received POST request for /price";
        
        auto body = crow::json::load(req.body);
        if (!body) {
            CROW_LOG_ERROR << "POST /price - Invalid JSON received";
            return crow::response(400, "{\"error\": \"Invalid JSON\"}");
        }

        OptionInput params;
        try {
            params.S = body["S"].d();
            params.K = body["K"].d();
            params.T = body["T"].d();
            params.r = body["r"].d();
            params.v = body["v"].d();
            params.num_sims = body["sims"].i();
            std::string type_str = body["type"].s();
            params.type = (type_str == "CALL") ? OptionInput::CALL : OptionInput::PUT;
        } catch (const std::exception& e) {
            CROW_LOG_ERROR << "POST /price - Error parsing parameters: " << e.what();
            return crow::response(400, "{\"error\": \"Missing or invalid parameters\"}");
        }

        double price = monteCarloPricer(params);
        CROW_LOG_INFO << "Calculation complete. Price: " << price;

        crow::json::wvalue response_json;
        response_json["price"] = price;

        crow::response res(200);
        res.set_header("Content-Type", "application/json");
        res.body = response_json.dump();
        return res;
    });

    // --- Preflight Route ---
    CROW_ROUTE(app, "/price").methods(crow::HTTPMethod::Options)
    ([](const crow::request&){
        CROW_LOG_INFO << "Received OPTIONS request for /price";
        return crow::response(200);
    });

app.bindaddr("0.0.0.0").port(18080).multithreaded().run();
    return 0;
}
