#pragma once

#include <iostream>
#include <string>

#include <GL/glew.h>
#include <GL/freeglut.h>


class Program {
public:
    Program();
    ~Program();

    void add_log(std::string log);
    std::string log_get() const;
    bool is_ready();
    void use();

private:
    std::string log_;
    bool ready_;
};

Program make_program(std::string& vertex_shader_src, std::string& fragment_shader);
