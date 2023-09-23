import glfw
import numpy as np
from OpenGL.GL import *

primitive_type = GL_LINE_LOOP

def render(primitive_type):
    glClear(GL_COLOR_BUFFER_BIT)
    glLoadIdentity()
    glBegin(primitive_type)
    # glBegin(GL_LINES)
    # glBegin(GL_LINE_STRIP)
    #glBegin(GL_LINE_LOOP)
    # ...
    
    x = np.linspace(0,360,12,endpoint = False)
    x = list(x)

    for i in range(len(x)):
        tmp = x[i]*(np.pi)*1/180
        glVertex2f(np.cos(tmp),np.sin(tmp))

    glEnd()

def key_callback(window, key, scancode, action, mods):
    global primitive_type

    if key == glfw.KEY_1:
        if action == glfw.PRESS:
            primitive_type = GL_POINTS
    elif key==glfw.KEY_2:
        if action == glfw.PRESS:
            primitive_type = GL_LINES
    elif key==glfw.KEY_3:
        if action == glfw.PRESS:
            primitive_type = GL_LINE_STRIP
    elif key==glfw.KEY_4:
        if action == glfw.PRESS:
            primitive_type = GL_LINE_LOOP
    elif key==glfw.KEY_5:
        if action == glfw.PRESS:
            primitive_type = GL_TRIANGLES
    elif key==glfw.KEY_6:
        if action == glfw.PRESS:
            primitive_type = GL_TRIANGLE_STRIP
    elif key==glfw.KEY_7:
        if action == glfw.PRESS:
            primitive_type = GL_TRIANGLE_FAN
    elif key==glfw.KEY_8:
        if action == glfw.PRESS:
            primitive_type = GL_QUADS
    elif key==glfw.KEY_9:
        if action == glfw.PRESS:
            primitive_type = GL_QUAD_STRIP
    elif key==glfw.KEY_0:
        if action == glfw.PRESS:
            primitive_type = GL_POLYGON

def main():
    # Initialize the library
    if not glfw.init():
        return
    # Create a windowed mode window and its OpenGL context
    window = glfw.create_window(480,480,"2018008922-2-2", None,None)
    if not window:
        glfw.terminate()
        return
    
    glfw.set_key_callback(window, key_callback)
    # Make the window's context current  
    glfw.make_context_current(window)
    # Loop until the user closes the window
    while not glfw.window_should_close(window):
        # Poll events
        glfw.poll_events()
        # Render here, e.g. using pyOpenGL
        render(primitive_type)
 
        # Swap front and back buffers
        glfw.swap_buffers(window)
    
    glfw.terminate()

if __name__ == "__main__":
 main()

