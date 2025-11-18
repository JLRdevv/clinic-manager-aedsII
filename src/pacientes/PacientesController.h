#pragma once
#include "crow.h"


class PacientesController {
public:
    static crow::Blueprint& get_routes() {
        static crow::Blueprint bp("pacientes");

        //get
        CROW_BP_ROUTE(bp, "/<int>").methods(crow::HTTPMethod::Get)
        ([](int id){
            return crow::response(200, "placeholder")
        });

        //post
        CROW_BP_ROUTE(bp, "/").methods(crow::HTTPMethod::Post)
        ([](const crow::request& req){
            auto body = req.body;

            return crow::response(201, "placeholder");
        });
        
        //patch
        CROW_BP_ROUTE(bp, "/").methods(crow::HTTPMethod::Patch)
        ([](){
            return crow::response(201, "placeholder");
        });

        //del
        CROW_BP_ROUTE(bp, "/hello")([](){
            return crow::response(200, "placeholder");
        });

        return bp;
    }
};