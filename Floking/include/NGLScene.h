#ifndef NGLSCENE_H_
#define NGLSCENE_H_
#include <ngl/BBox.h>
#include <ngl/Camera.h>
#include <ngl/Colour.h>
#include <ngl/Light.h>
#include <ngl/Text.h>
#include "WindowParams.h"
#include "Boid.h"
#include <QOpenGLWidget>
#include <QElapsedTimer>

#include <ngl/Random.h>


#include <memory>
//----------------------------------------------------------------------------------------------------------------------
/// @file NGLScene.h
/// @brief this class inherits from the Qt OpenGLWindow and allows us to use NGL to draw OpenGL
/// @author Jonathan Macey
/// @version 1.0
/// @date 10/9/13
/// Revision History :
/// This is an initial version used for the new NGL6 / Qt 5 demos
/// @class NGLScene
/// @brief our main glwindow widget for NGL applications all drawing elements are
/// put in this file
//----------------------------------------------------------------------------------------------------------------------

class NGLScene : public QOpenGLWidget
{
    Q_OBJECT


public :
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief ctor for our NGL drawing class
    /// @param [in] parent the parent window to the class
    //----------------------------------------------------------------------------------------------------------------------
    NGLScene(int _numBoids, QWidget *parent);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief dtor must close down ngl and release OpenGL resources
    //----------------------------------------------------------------------------------------------------------------------
    ~NGLScene();
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief the initialize class is called once when the window is created and we have a valid GL context
    /// use this to setup any default GL stuff
    //----------------------------------------------------------------------------------------------------------------------
    void initializeGL() override;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief this is called everytime we want to draw the scene
    //----------------------------------------------------------------------------------------------------------------------
    void paintGL() override;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief this is called everytime we resize
    //----------------------------------------------------------------------------------------------------------------------
    void resizeGL(int _w, int _h) override;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief reset the Boid array
    //----------------------------------------------------------------------------------------------------------------------


    void BoidBehavior();

    ///////////////////////////////////////     Functions used in GUI     ///////////////////////////////////////
    inline int getSeekCoef(){ return int(m_seekCoef); }
    inline int getAlignCoef(){ return int(m_alignCoef); }
    inline int getSepCoef(){ return int(m_separateCoef ); }
    inline int getVelocity(){ return int(m_velocity ); }
    inline float getBoidRadius(){return m_boidRadious;}



    void resetBoids();
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief add a new Boid
    //----------------------------------------------------------------------------------------------------------------------
    void addBoid();
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief remove the last Boid added
    //----------------------------------------------------------------------------------------------------------------------
    void removeBoid();
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief resize Boids
    //----------------------------------------------------------------------------------------------------------------------
    void resizeBoid(GLfloat _radius);
    void resetBehavior(GLfloat _seekCoef, GLfloat _alignCoef, GLfloat _separateCoef);
    void resetVelocity(float _velocity);


protected:
    WinParams m_win;

    //----------------------------------------------------------------------------------------------------------------------
    /// @brief used to store the global mouse transforms
    //----------------------------------------------------------------------------------------------------------------------
    ngl::Mat4 m_mouseGlobalTX;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief Our Camera
    //----------------------------------------------------------------------------------------------------------------------
    ngl::Camera m_cam;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief the model position for mouse movement
    //----------------------------------------------------------------------------------------------------------------------
    ngl::Vec3 m_modelPos;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief the bounding box to contain the Boids
    //----------------------------------------------------------------------------------------------------------------------
    std::unique_ptr<ngl::BBox> m_bbox;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief flag to indicate if we need to do BoidBoid checks
    //----------------------------------------------------------------------------------------------------------------------
    bool m_checkBoidBoid;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief the number of Boids we are creating
    //----------------------------------------------------------------------------------------------------------------------
    int m_numBoids;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief timer to change the Boid position by calling update()
    //----------------------------------------------------------------------------------------------------------------------
    int m_BoidUpdateTimer;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief flag to indicate if animation is active or not
    //----------------------------------------------------------------------------------------------------------------------
    bool m_animate;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief this method is called once per frame to update the Boid positions
    /// and do the collision detection
    //----------------------------------------------------------------------------------------------------------------------
    void updateScene();
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief method to load transform matrices to the shader
    //----------------------------------------------------------------------------------------------------------------------
    void loadMatricesToShader();
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief method to load transform matrices to the shader
    //----------------------------------------------------------------------------------------------------------------------
    void loadMatricesToColourShader();
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief Qt Event called when a key is pressed
    /// @param [in] _event the Qt event to query for size etc
    //----------------------------------------------------------------------------------------------------------------------
    void keyPressEvent(QKeyEvent *_event) override;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief this method is called every time a mouse is moved
    /// @param _event the Qt Event structure
    //----------------------------------------------------------------------------------------------------------------------
    void mouseMoveEvent (QMouseEvent * _event ) override;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief this method is called everytime the mouse button is pressed
    /// inherited from QObject and overridden here.
    /// @param _event the Qt Event structure
    //----------------------------------------------------------------------------------------------------------------------
    void mousePressEvent ( QMouseEvent *_event) override;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief this method is called everytime the mouse button is released
    /// inherited from QObject and overridden here.
    /// @param _event the Qt Event structure
    //----------------------------------------------------------------------------------------------------------------------
    void mouseReleaseEvent ( QMouseEvent *_event ) override;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief this method is called everytime the mouse wheel is moved
    /// inherited from QObject and overridden here.
    /// @param _event the Qt Event structure
    //----------------------------------------------------------------------------------------------------------------------
    void wheelEvent( QWheelEvent *_event) override;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief this method is called everytime the
    /// @param _event the Qt Event structure
    //----------------------------------------------------------------------------------------------------------------------
    void timerEvent( QTimerEvent *_event) override;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief check the collisions
    //----------------------------------------------------------------------------------------------------------------------
    void checkCollisions();
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief do the actual BoidBoid collisions
    /// @param[in] _pos1 the position of the first Boid
    ///	@param[in] _radius1 the radius of the first Boid
    /// @param[in] _pos2 the position of the second Boid
    ///	@param[in] _radius2 the radius of the second Boid
    //----------------------------------------------------------------------------------------------------------------------
    bool BoidBoidCollision( ngl::Vec3 _pos1, GLfloat _radius1, ngl::Vec3 _pos2, GLfloat _radius2 );
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief check the bounding box collisions
    //----------------------------------------------------------------------------------------------------------------------
    void BBoxCollision();
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief check the Boid collisions
    //----------------------------------------------------------------------------------------------------------------------
    void checkBoidCollisions();



    //temporary function that changes shpere direction
    //timer variable
    QElapsedTimer m_timer;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief timing for camera update
    //----------------------------------------------------------------------------------------------------------------------
    float m_deltaTime = 0.0f;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief frame time for camera update
    //----------------------------------------------------------------------------------------------------------------------
    float m_lastFrame = 0.0f;

    ngl::Transformation m_transform;


    ////////////    Boid Parameters ////////////
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief a dynamic array to contain our Boids
    //----------------------------------------------------------------------------------------------------------------------
    std::vector <Boid> m_BoidArray;
    float m_velocity=1;
    GLfloat m_boidRadious = 1.0f;
//    ngl::Vec4 m_boidColour=(0.5f, 0.1f, 0.8f, 1.0f);

    GLfloat m_separateCoef= 2.5f, m_alignCoef= 6.5f, m_seekCoef= 5.5f;

};



#endif
