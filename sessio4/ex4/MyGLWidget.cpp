#include "MyGLWidget.h"
#include <iostream>

// ANA MESTRE: VERSIÓ FINAL PER L'EXAMEN DE LAB.

MyGLWidget::MyGLWidget (QWidget* parent) : QOpenGLWidget(parent)
{
  setFocusPolicy(Qt::ClickFocus);  // per rebre events de teclat
  scale = 1.0f;
}

MyGLWidget::~MyGLWidget ()
{
  if (program != NULL)
    delete program;
}


void MyGLWidget::initializeGL ()
{
  // Cal inicialitzar l'ús de les funcions d'OpenGL
  initializeOpenGLFunctions();  

  glClearColor(0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
  glEnable(GL_DEPTH_TEST);
  carregaShaders();
  createBuffers();
  iniCamera();
}

void MyGLWidget::paintGL () 
{
  // Esborrem el frame-buffer
  glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

  // Carreguem la transformació de model
  modelTransform ();

  // Activem el VAO per a pintar la caseta 
  glBindVertexArray (VAOhomer);

  // pintem
  glDrawArrays(GL_TRIANGLES, 0, homer.faces().size()*3);

  glBindVertexArray (0);
}

void MyGLWidget::modelTransform () 
{
  // Matriu de transformació de model
  glm::mat4 transform (1.0f);
  transform = glm::scale(transform, glm::vec3(scale));
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &transform[0][0]);
}

void MyGLWidget::resizeGL (int w, int h) 
{
  glViewport(0, 0, w, h);
}

void MyGLWidget::keyPressEvent(QKeyEvent* event) 
{
  switch (event->key()) {
    makeCurrent();
    case Qt::Key_S: { // escalar a més gran
      scale += 0.05;
      break;
    }
    case Qt::Key_D: { // escalar a més petit
      scale -= 0.05;
      break;
    }
    default: event->ignore(); break;
  }
  update();
}

void MyGLWidget::createBuffers () {
  carregarModel();
  glBindVertexArray (0);
}

void MyGLWidget::carregaShaders()
{
  // Creem els shaders per al fragment shader i el vertex shader
  QOpenGLShader fs (QOpenGLShader::Fragment, this);
  QOpenGLShader vs (QOpenGLShader::Vertex, this);
  // Carreguem el codi dels fitxers i els compilem
  //fs.compileSourceFile("shaders/fragshad.frag");
  //vs.compileSourceFile("shaders/vertshad.frag");
  fs.compileSourceFile("E:/Documents/EXAMEN IDI/versio neta/ex4/shaders/fragshad.frag");
  vs.compileSourceFile("E:/Documents/EXAMEN IDI/versio neta/ex4/shaders/vertshad.vert");
  // Creem el program
  program = new QOpenGLShaderProgram(this);
  // Li afegim els shaders corresponents
  program->addShader(&fs);
  program->addShader(&vs);
  // Linkem el program
  program->link();
  // Indiquem que aquest és el program que volem usar
  program->bind();

  // Obtenim identificador per a l'atribut “vertex” del vertex shader
  vertexLoc = glGetAttribLocation (program->programId(), "vertex");
  // Obtenim identificador per a l'atribut “color” del vertex shader
  colorLoc = glGetAttribLocation (program->programId(), "color");
  // Uniform locations
  transLoc = glGetUniformLocation(program->programId(), "TG");


  // Sessio 4: exercici 1.
  projLoc = glGetUniformLocation(program->programId(), "proj");
  viewLoc = glGetUniformLocation(program->programId(), "view");


}

// --------------------------------
// ----- LES MEVES FUNCIONS -------
// --------------------------------

// Sessio 4: exercici 1.
void MyGLWidget::projectTransform(){
    //glm::mat4 Proj = glm::perspective ((float)M_PI/2.0f, 1.0f, 1.0f, 3.0f); // <-- Sessio 4, exercici 1.
    glm::mat4 Proj = glm::perspective (FOV, ra, zNear, zFar); // <-- Sessio 4, exercici 2.
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, &Proj[0][0]);
}

// Sessio 4: exercici 2.
void MyGLWidget::viewTransform(){
  //glm::mat4 View = glm::lookAt(glm::vec3(0,0,1), glm::vec3(0,0,0), glm::vec3(0,1,0)); // <-- Sessio 4, exercici 1.
  glm::mat4 View = glm::lookAt(OBS, VRP, UP); // <-- Sessio 4, exercici 2.
  glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &View[0][0]);
}

// Sessio 4: exercici 2.
void MyGLWidget::iniCamera(){
    FOV = M_PI/2.0;
    ra = 1.0;
    zNear = 1.0;
    zFar = 3.0;

    OBS = glm::vec3(0,0,2);
    VRP = glm::vec3(0,0,0);
    UP = glm::vec3(0,1,0);

    projectTransform();
    viewTransform();
}

// Sessio 4: exercici 4.
void MyGLWidget::carregarModel(){
    homer.load("E:/Documents/EXAMEN IDI/versio neta/ex4/models/HomerProves.obj");
    glGenVertexArrays(1, &VAOhomer);
    glBindVertexArray(VAOhomer);

    glGenBuffers(1, &VBOhomerVertex);
    glBindBuffer(GL_ARRAY_BUFFER, VBOhomerVertex);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*homer.faces().size()*3*3, homer.VBO_vertices(), GL_STATIC_DRAW);

    // Activem l'atribut vertexLoc
    glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(vertexLoc);

    glGenBuffers(1, &VBOhomerMaterial);
    glBindBuffer(GL_ARRAY_BUFFER, VBOhomerMaterial);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*homer.faces().size()*3*3, homer.VBO_matdiff(), GL_STATIC_DRAW);

    // Activem l'atribut colorLoc
    glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(colorLoc);

}
