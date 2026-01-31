#include "Todo.hpp"
#include <string>

Todo::Todo(int id, const std::string& title, Priority priority) {
    this->id = id;
    this->title = title;
    this->done = false; 
    this->priority = priority;
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

Priority Todo::getPriority() const {
    return this->priority;
}

void Todo::setPriority(Priority newPriority) {
    this->priority = newPriority;
}