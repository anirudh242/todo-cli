#include "Todo.hpp"
#include <string>

Todo::Todo(int id, const std::string& title) {
    this->id = id;
    this->title = title;
    this->done = false; 
}

int Todo::getId() const {
    return this->id;
}

std::string Todo::getTitle() const {
    return this->title;
}

void Todo::setTitle(const std::string& newTitle) {
    this->title = newTitle;
}

bool Todo::getDone() const {
    return this->done;
}

void Todo::toggleDone() {
    this->done = !this->done;
}