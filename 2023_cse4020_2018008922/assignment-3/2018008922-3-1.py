import glfw
import numpy as np
from OpenGL.GL import *

gComposedM = np.identity(3)

def render(T):
    glClear(GL_COLOR_BUFFER_BIT)
    glLoadIdentity()
    # draw cooridnate
    glBegin(GL_LINES)
    glColor3ub(255, 0, 0)
    glVertex2fv(np.array([0.,0.]))
    glVertex2fv(np.array([1.,0.]))
    glColor3ub(0, 255, 0)
    glVertex2fv(np.array([0.,0.]))
    glVertex2fv(np.array([0.,1.]))
    glEnd()
    # draw triangle
    glBegin(GL_TRIANGLES)
    glColor3ub(255, 255, 255)
    glVertex2fv( (T @ np.array([.0,.5,1.]))[:-1] )
    glVertex2fv( (T @ np.array([.0,.0,1.]))[:-1] )
    glVertex2fv( (T @ np.array([.5,.0,1.]))[:-1] )
    glEnd()

def key_callback(window, key, scancode, action, mods):
    global gComposedM
    M = np.identity(3)
    flag = 0 
    if action == glfw.PRESS or action == glfw.REPEAT:    
        if key == glfw.KEY_Q:
            M[:2, 2] = [-0.1, 0.]
            flag = 1
        elif key==glfw.KEY_E:
            M[:2, 2] = [0.1, 0.]
            flag = 1
        elif key==glfw.KEY_A:
            th = np.radians(10)
            M[:2, :2] = [[np.cos(th), -np.sin(th)], [np.sin(th), np.cos(th)]]
            flag = 2        
        elif key==glfw.KEY_D:
            th = np.radians(-10)
            M[:2, :2] = [[np.cos(th), -np.sin(th)], [np.sin(th), np.cos(th)]]
            flag = 2        
        elif key==glfw.KEY_W:
            M[:1, :1] = [0.9] 
            flag = 1
        elif key==glfw.KEY_S:
            th = np.radians(10)
            M[:2, :2] = [[np.cos(th), -np.sin(th)], [np.sin(th), np.cos(th)]]
            flag = 1
        elif key==glfw.KEY_1:
            gComposedM = np.identity(3)
        
        if flag == 1:
            gComposedM = M@gComposedM    
        elif flag == 2:
            gComposedM = gComposedM@M            

def main():
    # Initialize the library
    if not glfw.init():
        return
    # Create a windowed mode window and its OpenGL context
    window = glfw.create_window(480,480,"2018008922-3-1", None,None)
    if not window:
        glfw.terminate()
        return
    global T
    glfw.set_key_callback(window, key_callback)
    # Make the window's context current  
    glfw.make_context_current(window)
    # Loop until the user closes the window
    while not glfw.window_should_close(window):
        # Poll events
        glfw.poll_events()
        # Render here, e.g. using pyOpenGL
        
        render(gComposedM)
 
        # Swap front and back buffers
        glfw.swap_buffers(window)
    
    glfw.terminate()

if __name__ == "__main__":
 main()
