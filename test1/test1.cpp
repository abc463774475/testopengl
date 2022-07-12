//// testgl.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
////
//
//#include <iostream>
//#include <gl/glew.h>
//#include <GLFW/glfw3.h>
//
//using namespace std;
//
//void printProgramInfoLog(GLuint program)
//{
//    int infoLogLen = 0;
//    int charsWritten = 0;
//    char* infoLog;
//
//    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLen);
//
//    if (infoLogLen > 0)
//    {
//        infoLog = new char[infoLogLen];
//        glGetProgramInfoLog(program, infoLogLen, &charsWritten, infoLog);
//        cout << infoLog << endl;
//        delete[] infoLog;
//    }
//}
//
//void printShaderLog(GLuint shader) {
//    int len = 0;
//    int chWrittn = 0;
//    char* log;
//    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
//    if (len > 0)
//    {
//        log = (char*)malloc(len);
//        glGetShaderInfoLog(shader, len, &chWrittn, log);
//
//        printf("getshader err log %s\n", log);
//        free(log);
//    }
//    else {
//        printf("no error\n");
//    }
//}
//
//
//bool checkOpenGLError() {
//    bool foundError = false;
//    int glError = glGetError();
//    while (glError != GL_NO_ERROR) {
//        foundError = true;
//        cout << "glError: " << glError << endl;
//        glError = glGetError();
//    }
//    return foundError;
//}
//
//
//#define numVAOs 1
//
//GLuint renderingProgram;
//GLuint vao[numVAOs];
//
//GLuint createShaderProgram() {
//    //    const char* vshaderSource = "#version 430\n"
//    //        "void main(void)\n"
//    //        "{\n"
//    //        "   gl_Position = vec4(0.0,0.0,0.0,1.0);\n"
//    //        "}";
//
//    //    auto vshaderSource = "#version 430\n"
//    //        "void main(){\n"
//    //        "    if (gl_VertexID == 0)\n"
//    //        "        gl_Position = vec4(0.25, -0.25, 0.0, 1.0);\n"
//    //        "    else if (gl_VertexID == 1)\n"
//    //        "        gl_Position = vec4(-0.25, -0.25, 0.0, 1.0);\n"
//    //        "    else\n"
//    //        "        gl_Position = vec4(0.25, 0.25, 0.0, 1.0);\n"
//    //        "}";
//
//    auto vshaderSource = "#version 430\n"
//        "uniform float offset;\n"
//        "\n"
//        "void main(){\n"
//        "    if (gl_VertexID == 0)\n"
//        "        gl_Position = vec4(0.25 + offset, -0.25, 0.0, 1.0);\n"
//        "    else if (gl_VertexID == 1)\n"
//        "        gl_Position = vec4(-0.25 + offset, -0.25, 0.0, 1.0);\n"
//        "    else\n"
//        "        gl_Position = vec4(0.25 + offset, 0.25, 0.0, 1.0);\n"
//        "}";
//
//    const char* fshaderSource = "#version 430 \n"
//        "out vec4 color; \n"
//        "void main(void) \n"
//        "{color = vec4(1.0,0.0,0.0,1.0);}"
//        ;
//
//    auto sz = "#version 430\n"
//        "out vec4 color;\n"
//        "void main(void)\n"
//        "{\n"
//        "\tif (gl_FragCoord.x < 200){\n"
//        "\t\tcolor = vec4(1.0,1.0,0.0,1.0) ;\n"
//        "\t}else {\n"
//        "\t\tcolor = vec4(0.0,0.0,1.0,1.0) ;\n"
//        "\t}\n"
//        "}";
//
//
//    auto vSharder = glCreateShader(GL_VERTEX_SHADER);
//    auto fSharder = glCreateShader(GL_FRAGMENT_SHADER);
//
//    glShaderSource(vSharder, 1, &vshaderSource, NULL);
//    glShaderSource(fSharder, 1, &fshaderSource, NULL);
//
//    glCompileShader(vSharder);
//    glCompileShader(fSharder);
//
//    checkOpenGLError();
//
//    printShaderLog(vSharder);
//    printShaderLog(fSharder);
//
//    auto vfProgram = glCreateProgram();
//    glAttachShader(vfProgram, vSharder);
//    glAttachShader(vfProgram, fSharder);
//    glLinkProgram(vfProgram);
//
//    return vfProgram;
//}
//
//void init(GLFWwindow* window) {
//    renderingProgram = createShaderProgram();
//    glGenVertexArrays(numVAOs, vao);
//    glBindVertexArray(vao[0]);
//}
//
////void display(GLFWwindow* window, double currentTime)
////{
////	/*glClearColor(1.0, 1.0, 0.0, 0.0);
////	glClear(GL_COLOR_BUFFER_BIT);*/
////    glUseProgram(renderingProgram);
////
////    glPointSize(100.f);
////
////    // glDrawArrays(GL_POINTS, 0, 1);
////    glDrawArrays(GL_TRIANGLES, 0, 3);
////}
//float x = 0.0f;
//float inc = 0.01f;
//
//void display(GLFWwindow* window, double currentTime)
//{
//    glClear(GL_DEPTH_BUFFER_BIT);
//    glClearColor(0.0, 0.0, 0.0, 1.0);
//    glClear(GL_COLOR_BUFFER_BIT);
//
//    glUseProgram(renderingProgram);
//    x += inc;
//    if (x > 1.0f) inc = -0.05f;
//    if (x < -1.0f) inc = 0.05f;
//    auto offsetLoc = glGetUniformLocation(renderingProgram, "offset");
//    glProgramUniform1f(renderingProgram, offsetLoc, x);
//    glDrawArrays(GL_TRIANGLES, 0, 3);
//}
//
//int main()
//{
//    if (!glfwInit())
//    {
//        printf("glfwinit failed\n");
//        return 0;
//    }
//
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//
//    auto window = glfwCreateWindow(600, 600, "chapter2 - program1", NULL, NULL);
//    glfwMakeContextCurrent(window);
//
//    if (glewInit() != GLEW_OK)
//    {
//        printf("glew init failed \n");
//        return 0;
//    }
//
//    glfwSwapInterval(1);
//
//    init(window);
//
//    while (!glfwWindowShouldClose(window))
//    {
//        display(window, glfwGetTime());
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//
//    glfwDestroyWindow(window);
//    glfwTerminate();
//}
