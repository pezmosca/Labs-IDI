#define GLM_FORCE_RADIANS
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLWidget>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QKeyEvent>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "model.h"
#include <QLineEdit>

class MyGLWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core 
{
  Q_OBJECT

  public:
    MyGLWidget (QWidget *parent=0);
    ~MyGLWidget ();

  protected:
    // initializeGL - Aqui incluim les inicialitzacions del contexte grafic.
    virtual void initializeGL ( );
    // paintGL - Mètode cridat cada cop que cal refrescar la finestra.
    // Tot el que es dibuixa es dibuixa aqui.
    virtual void paintGL ( );
    // resizeGL - És cridat quan canvia la mida del widget
    virtual void resizeGL (int width, int height);
    // keyPressEvent - Es cridat quan es prem una tecla
    virtual void keyPressEvent (QKeyEvent *event);

  private:
    void createBuffers ();
    void carregaShaders ();
    void modelTransform ();

    // --------------------------------
    // ----- LES MEVES FUNCIONS -------
    // --------------------------------

    void projectTransform();
    void viewTransform();
    void iniCamera();
    void carregarModel();
    void pintaHomer();
    void pintaTerra();
    void carregaTerra();
    void modelTransformTerra();

    // Sessio 5
    void calculaCapsaContenidoraHomer();
    void calculaCentreRadi();
    void calculaCapsaContenidoraPatricio();
    void carregarPatricio();
    void pintaPatricio();
    void mousePressEvent (QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *e);
        typedef  enum {NONE, ROTATE} InteractiveAction;
        InteractiveAction DoingInteractive;

    // Sessio 6
    void modelTransformPatricio2();
    void pintaPatricio2();
    void calculaCapsaEscena();
    void calculaCentreRadiEscena();
    
    void pintaLego();
    void pintaLego2();
    void carregaLego();
    void modelLegoMan2();
    void modelLegoMan();
    void calculaCapsaLego();

    GLuint projLoc, viewLoc;
    glm::vec3 VRP, OBS, UP;
    float ra, zNear, zFar, FOV;
    float radi, radiEscena;
    glm::vec3 modelMinim, modelMaxim, centre, escenaMaxim, escenaMinim, centreEscena;
    glm::vec3 legoMinim, legoMaxim, centrelego; 

    Model homer;
    Model patricio;
    Model lego;
    GLuint VAOhomer, VBOhomerVertex, VBOhomerMaterial;
    GLuint VAOpatricio, VBOpatricioVertex, VBOpatricioMaterial;
    float antigaX, antigaY, rotaX, rotaY;

    float rotacio;
    float left, right, bottom, top;

    GLuint VAOterra, VBOterraVertex, VBOterraColor, VAOlego, VBOlegoVertex, VBOlegoMaterial;
    
    bool perspective;
    bool legoman;
    
    
    // --------------------------------

    // attribute locations
    GLuint vertexLoc, colorLoc;
    // uniform locations
    GLuint transLoc;
    // VAO i VBO names
    //GLuint VAO_Casa, VBO_CasaPos, VBO_CasaCol;
    // Program
    QOpenGLShaderProgram *program;
    // Internal vars
    float scale;
    glm::vec3 pos;  
    
public slots:
   void canviarCamera();
   void canviaLegoMan();
};

