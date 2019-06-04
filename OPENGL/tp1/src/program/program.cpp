#include "program.hh"

Program::Program()
{}

Program::~Program()
{}

void
Program::add_log(std::string log) {
    log_.append(log);
    log_.append("\n");
}

std::string
Program::log_get() const {
    return log_;
}

bool
Program::is_ready() {
    return ready_;
}

void
Program::use() {
    // Utilisation of program
}

Program make_program(std::string& vertex_shader_src, std::string& fragment_shader) {
    GLuint vertex_shader = glCreateShader(GL_VERTEX_ARRAY);
    GLint compile_status = GL_TRUE;
    glShaderSource(vertex_shader, 1, (const GLchar**)&(vertex_shader_src), 0);check_error();
    glCompileShader(vertex_shader);check_error();
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &compile_status);check_error();
    if(compile_status != GL_TRUE) {
      std::cerr << "ERROR" << std::endl;
      return false;
    }

    auto program = glCreateProgram(); check_error();
    if (program == 0)
        return false;

    GLint link_status=GL_TRUE;
    glAttachShader(program, vertex_shader); check_error();
    glLinkProgram(program);check_error();
    glGetProgramiv(program, GL_LINK_STATUS, &link_status);

    glUseProgram(program);
    return true;
}
