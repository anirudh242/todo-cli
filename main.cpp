#include "CLI11.hpp"
#include <iostream>

int main(int argc, char const **argv)
{
    CLI::App app;

    // NEW TODO
    auto newCmd = app.add_subcommand("new", "Create new todo item");
    std::string name;
    newCmd->add_option("name", name, "Name of the todo")->required();
    newCmd->callback([&]() {
        std::cout << "Creating todo: " << name << std::endl;
    });
    

    // DELETE TODO
    auto deleteCmd = app.add_subcommand("delete", "Delete specific todo item");
    int todoID; 
    deleteCmd->add_option("ID", todoID, "ID of the todo to delete")->required();
    deleteCmd->callback([&]() {
        std::cout << "Deleting todo " << todoID << std::endl;
    });
    
    app.require_subcommand(1);
    CLI11_PARSE(app, argc, argv);

    return 0;
}
