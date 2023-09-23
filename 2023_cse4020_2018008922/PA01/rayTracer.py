#!/usr/bin/env python3
# -*- coding: utf-8 -*
# sample_python aims to allow seamless integration with lua.
# see examples below

import glfw
from OpenGL.GL import *

import os
import sys
import pdb  # use pdb.set_trace() for debugging
import code # or use code.interact(local=dict(globals(), **locals()))  for debugging.
import xml.etree.ElementTree as ET
import numpy as np
import math
from PIL import Image

class Light:
    def __init__(self, position, intensity):
        self.m_position = position
        self.m_intensity = intensity

class Shader:
    def __init__(self, name, type, diffuseColor, specularColor, exponent):
        self.m_name = name
        self.m_type = type
        self.m_diffuseColor = diffuseColor
        self.m_specularColor = specularColor
        self.m_exponent = exponent

class CalculateVector:
    def __init__(self):
        self.m_limit = 0.000000001

    def CalEqual(self, a, b):
        if (abs(a - b) < self.m_limit):
            return True
        else :
            return False

    def CalUnitVector(self, v):
        result = (1./np.sqrt(v[2]**2 + v[1]**2 + v[0]**2))*v 
        return result
    
    def CalPixelVector(self, viewDir, imageHeight, imageWidth, heightPixelSize, widthPixelSize, d, i, j, viewUp):
        x = self.CalUnitVector(np.cross(viewDir, viewUp))
        y = self.CalUnitVector(np.cross(viewDir, x))
        index = (d * viewDir)+(-(imageWidth/2)+(imageWidth/widthPixelSize)/2+(imageWidth/widthPixelSize)*j)*x + (-(imageHeight)/2+(imageHeight/heightPixelSize)/2+(imageHeight/heightPixelSize)*i)*y
        return self.CalUnitVector(index)

    def CalDiscriminant(self, startPt, ray, r):
        if(np.dot(startPt, ray)*np.dot(startPt, ray)-np.dot(startPt, startPt)+ r**2 < 0):
            return False
        else:
            return True
    
calVec = CalculateVector()

class Sphere:
    def __init__(self, center, r, shader):
        self.center = center
        self.r = r
        self.shader = shader

    def GetNormalVector(self, surfacePt):
        return calVec.CalUnitVector(surfacePt - self.center)

    def InterSectSpherePoint(self, ray, eyePt):
        startPt = self.center-eyePt
        if((np.dot(startPt, ray)*np.dot(startPt, ray)-np.dot(startPt, startPt)+self.r**2) > 0):
            result = np.dot(startPt,ray) -np.sqrt(np.dot(startPt,ray)*np.dot(startPt,ray)-np.dot(startPt,startPt)+self.r**2)
            return result
        else:
            return -1
    
    def bCheckintersect(self, ray, eyePt):
        startPt = self.center - eyePt
        return calVec.CalDiscriminant(startPt, ray, self.r)

class Box:
    def __init__(self, minPt, maxPt, shader):
        self.m_minPt = minPt
        self.m_maxPt = maxPt
        self.shader = shader
        self.m_center = (minPt + maxPt)*(1./2.)
        self.m_min_t = 0
        self.m_max_t = 0
        self.m_min_y = 0
        self.m_max_y = 0
        self.m_min_z = 0
        self.m_max_z = 0

    def GetNormalVector(self, surfacePt):
        if(calVec.CalEqual(self.m_minPt[0], surfacePt[0])):
            if(np.dot(np.array([-1.,0.,0.]),(surfacePt-self.m_center)) > 0):
               return np.array([-1.,0.,0.])
            else:
               return np.array([1,0,0])
        elif(calVec.CalEqual(self.m_maxPt[0], surfacePt[0])):
            if(np.dot(np.array([1.,0.,0.]),(surfacePt-self.m_center)) > 0):
                return np.array([1.,0.,0.])
            else:
                return np.array([-1,0,0])
        elif(calVec.CalEqual(self.m_minPt[1], surfacePt[1])):
            if(np.dot(np.array([0.,-1.,0.]),(surfacePt-self.m_center)) > 0):
                return np.array([0.,-1.,0.])
            else:
                return np.array([0,1,0])
        elif(calVec.CalEqual(self.m_maxPt[1], surfacePt[1])):
            if(np.dot(np.array([0.,1.,0.]) , (surfacePt - self.m_center)) > 0):
                return np.array([0.,1.,0.])
            else:
                return np.array([0,-1,0])
        elif(calVec.CalEqual(self.m_minPt[2], surfacePt[2])):
            if(np.dot(np.array([0,0.,-1]),(surfacePt-self.m_center)) > 0):
                return np.array([0,0.,-1])
            else:
                return np.array([0,0,1])
        elif(calVec.CalEqual(self.m_maxPt[2], surfacePt[2])):
            if(np.dot(np.array([0,0,1]),(surfacePt-self.m_center)) > 0):
                return np.array([0,0,1])
            else:
                return np.array([0,0,-1])


    def InterSectBoxPoint(self, ray, eyePt):
        tmp = np.Infinity
        if(ray[0] == 0. or ray[1] == 0. or ray[2] == 0.):
            return tmp
        
        self.m_min_t = (self.m_minPt[0] - eyePt[0])/ray[0]
        self.m_max_t = (self.m_maxPt[0] - eyePt[0])/ray[0]
        
        if(self.m_min_t > self.m_max_t):
            self.m_min_t, self.m_max_t = self.m_max_t, self.m_min_t

        self.m_min_y = (self.m_minPt[1] - eyePt[1])/ray[1]
        self.m_max_y = (self.m_maxPt[1] - eyePt[1])/ray[1]
        
        if(self.m_min_y > self.m_max_y):
            self.m_min_y, self.m_max_y = self.m_max_y, self.m_min_y

        if(self.m_min_t > self.m_max_y or self.m_max_t < self.m_min_y):
            return tmp
        
        self.m_min_t = max(self.m_min_y, self.m_min_t)
        self.m_max_t = min(self.m_max_y, self.m_max_t) 

        self.m_min_z = (self.m_minPt[2] - eyePt[2])/ray[2]
        self.m_max_z = (self.m_maxPt[2] - eyePt[2])/ray[2]
        
        if(self.m_min_z >self.m_max_z):
            self.m_min_z, self.m_max_z = self.m_max_z, self.m_min_z

        if(self.m_min_t > self.m_max_z or self.m_max_t < self.m_min_z):
            return tmp

        self.m_min_t = max(self.m_min_z, self.m_min_t)
        self.m_max_t = min(self.m_max_z, self.m_max_t) 

        return self.m_min_t

    
class Shape(Sphere, Box):
    def __init__(self):
        self.m_surfaceType = None
        self.m_arrSphere = []
        self.m_arrBox = []
        self.m_numSphere = 0
        self.m_numBox = 0
        self.m_shapeT = np.Infinity
        self.m_surfaceP = None
        self.m_rendered = None

    def SurfaceSetting(self, root):
        for i in root.findall('surface'):
            self.m_surfaceType = i.get('type')
            for j in i.iter('shader'):
                ref_c = j.get('ref')
            if(self.m_surfaceType == 'Sphere'):  
                center_c = np.array(i.findtext('center').split()).astype(np.float64)
                r_c = np.array(i.findtext('radius').split()).astype(np.float64)
                self.m_arrSphere.append(Sphere(center_c , r_c[0] , ref_c ))
            elif(self.m_surfaceType == 'Box'): 
                minPt_c = np.array(i.findtext('minPt').split()).astype(np.float64)
                maxPt_c = np.array(i.findtext('maxPt').split()).astype(np.float64)
                self.m_arrBox.append(Box(minPt_c, maxPt_c, ref_c ))

    def GetSurface(self, arrSphere, arrBox, pixelVec, viewPoint):
        self.m_shapeT = np.Infinity
        for s in np.arange(len(arrSphere)):
            if(arrSphere[s].bCheckintersect(pixelVec,viewPoint)):   
                if(self.m_shapeT > arrSphere[s].InterSectSpherePoint(pixelVec,viewPoint)):
                    self.m_shapeT = arrSphere[s].InterSectSpherePoint(pixelVec,viewPoint)
                    self.m_surfaceP = self.m_shapeT*pixelVec+viewPoint
                    self.m_rendered = arrSphere[s]

        for b in np.arange(len(arrBox)):
            if(self.m_shapeT > arrBox[b].InterSectBoxPoint(pixelVec, viewPoint)):
                self.m_shapeT = arrBox[b].InterSectBoxPoint(pixelVec, viewPoint)
                self.m_surfaceP = self.m_shapeT*pixelVec+viewPoint
                self.m_rendered = arrBox[b]

    def CheckBlockFlag(self, light, surfaceP, type):
        tmp = True
        tmp2 = np.Infinity
        if type == 'Sphere':
            for s in np.arange(self.m_numSphere):
                if(self.m_arrSphere[s].InterSectSpherePoint(light, surfaceP) > 0 and self.m_arrSphere[s].InterSectSpherePoint(light, surfaceP) != tmp2):
                    return tmp
        elif type == 'Box':
            for b in np.arange(self.m_numBox):
                if(self.m_arrBox[b].InterSectBoxPoint(light, surfaceP) > 0 and self.m_arrBox[b].InterSectBoxPoint(light, surfaceP) != tmp2):
                    return tmp
        tmp = False
        return tmp

class Setting:
    def __init__(self, np_viewPoint, np_viewDir, np_viewUp, np_projNormal, np_viewWidth, np_viewHeight, np_projDistance):
        self.m_viewPoint = np_viewPoint
        self.m_viewDir = np_viewDir
        self.m_viewUp = np_viewUp
        self.m_projNormal = np_projNormal
        self.m_viewWidth = np_viewWidth
        self.m_viewHeight = np_viewHeight
        self.m_projDistance = np_projDistance
        self.m_arrLight = []

    def CameraSetiing(self, root):
        for c in root.findall('camera'):
            self.m_viewPoint = np.array(c.findtext('viewPoint').split()).astype(np.float64)                                 #point
            self.m_viewDir = calVec.CalUnitVector( np.array(c.findtext('viewDir').split()).astype(np.float64))              #vector
            self.m_projNormal = calVec.CalUnitVector( np.array(c.findtext('projNormal').split()).astype(np.float64))
            self.m_viewUp = calVec.CalUnitVector(np.array(c.findtext('viewUp').split()).astype(np.float64))
            np_tempViewWidth = np.array(c.findtext('viewWidth').split()).astype(np.float64)                                 #viewplane size
            np_tempViewHeight = np.array(c.findtext('viewHeight').split()).astype(np.float64)                               #viewplane size
            
            if(c.findtext('projDistance')!=None):
                temp_projDistance = np.array(c.findtext('projDistance').split()).astype(np.float64)
                self.m_projDistance = temp_projDistance[0]
            self.m_viewWidth = np_tempViewWidth[0]
            self.m_viewHeight = np_tempViewHeight[0]

    def ImageSizeSetting(self, root):
        result = np.array(root.findtext('image').split()).astype(np.int32)
        return result
    
    def ShaderSetting(self, root, arrShader):
        for c in root.findall('shader'):
            shader_c = c.get('name')
            shader_type_c = c.get('type')
            diffuseColor_c = np.array(c.findtext('diffuseColor').split()).astype(np.float64)
            
            if(shader_type_c == "Phong"):
                specularColor_c = np.array(c.findtext('specularColor').split()).astype(np.float64)
                exponent_c = np.array(c.findtext('exponent').split()).astype(np.int32)
            else:
                specularColor_c = np.array([0.,0.,0.])
                exponent_c = np.array([0])
            arrShader[shader_c] = Shader(shader_c, shader_type_c, diffuseColor_c ,specularColor_c ,exponent_c)
                
    def LightSetting(self, root):
        for c in root.findall('light'):
            position_c = np.array(c.findtext('position').split()).astype(np.float64)
            intensity_c = np.array(c.findtext('intensity').split()).astype(np.float64)
            self.m_arrLight.append(Light(position_c ,intensity_c))
    
    
class Color:
    def __init__(self, R, G, B):
        self.color=np.array([R,G,B]).astype(np.float64)

    # Gamma corrects this color.
    # @param gamma the gamma value to use (2.2 is generally used).
    def gammaCorrect(self, gamma):
        inverseGamma = 1.0 / gamma
        self.color=np.power(self.color, inverseGamma)

    def toUINT8(self):
        return (np.clip(self.color, 0,1)*255).astype(np.uint8)

def main():
    tree = ET.parse(sys.argv[1])
    root = tree.getroot()

    # set default values
    viewDir=np.array([0,0,-1]).astype(np.float64)
    viewUp=np.array([0,1,0]).astype(np.float64)
    ProjNormal=-1*viewDir  # you can safely assume this. (no examples will use shifted perspective camera)
    viewWidth=1.0
    viewHeight=1.0
    projDistance=1.0
    intensity=np.array([1,1,1]).astype(np.float64)  # how bright the light is.
    viewPoint = np.array([0, 0, 0])
    imgSize = 0

    #Setting
    m_Setting = Setting(viewPoint, viewDir, viewUp, ProjNormal, viewWidth, viewHeight, projDistance)

    #CameraSetting
    m_Setting.CameraSetiing(root)
    viewPoint = m_Setting.m_viewPoint
    viewDir = m_Setting.m_viewDir
    ProjNormal = m_Setting.m_projNormal
    viewUp = m_Setting.m_viewUp
    viewWidth = m_Setting.m_viewWidth
    viewHeight = m_Setting.m_viewHeight
    projDistance = m_Setting.m_projDistance

    #LightSetting
    m_Setting.LightSetting(root)

    #ShaderSetting
    arrShader = {}
    m_Setting.ShaderSetting(root, arrShader)
    
    #ImageSizeSetting
    imgSize = m_Setting.ImageSizeSetting(root)

    #SurfaceSetting
    shape = Shape()
    shape.SurfaceSetting(root)
    if(shape.m_surfaceType == 'Sphere'):
        shape.m_numSphere = len(shape.m_arrSphere)
    elif(shape.m_surfaceType == 'Box'):
        shape.m_numBox = len(shape.m_arrBox)
    
    
    # Create an empty image
    channels=3
    img = np.zeros((imgSize[1], imgSize[0], channels), dtype=np.uint8)
    img[:,:]=0
    
    # replace the code block below!
    for y in np.arange(imgSize[1]):
        for x in np.arange(imgSize[0]):
            
            pixelVector = calVec.CalPixelVector(viewDir, viewHeight, viewWidth, imgSize[1], imgSize[0], projDistance, y, x, viewUp)
            pixelColor = np.array([0,0,0])
            color = np.array([0,0,0])
            
            shape.GetSurface(shape.m_arrSphere, shape.m_arrBox, pixelVector, viewPoint)

            if (shape.m_rendered is not None and shape.m_surfaceP is not None):
                surfaceN = shape.m_rendered.GetNormalVector(shape.m_surfaceP)
                pixelShader = arrShader[shape.m_rendered.shader]
            else:
                pixelShader = None
            
            if(shape.m_shapeT != np.Infinity):
                for i in np.arange(len(m_Setting.m_arrLight)):
                    light = calVec.CalUnitVector(m_Setting.m_arrLight[i].m_position - shape.m_surfaceP)
                    bSphereBlock = shape.CheckBlockFlag(light, shape.m_surfaceP, 'Sphere')
                    if (bSphereBlock == False):
                        bBoxBlock = shape.CheckBlockFlag(light, shape.m_surfaceP, 'Box')
                        if(bBoxBlock == False):
                            if(pixelShader.m_type == "Phong"):
                                color = max(0,np.dot(surfaceN,light)) * m_Setting.m_arrLight[i].m_intensity * pixelShader.m_diffuseColor + math.pow((max(0,np.dot(surfaceN,calVec.CalUnitVector(light - viewDir)))), pixelShader.m_exponent[0]) * m_Setting.m_arrLight[i].m_intensity*pixelShader.m_specularColor
                            elif(pixelShader.m_type == "Lambertian"):
                                color = max(0,np.dot(surfaceN,light)) * m_Setting.m_arrLight[i].m_intensity * pixelShader.m_diffuseColor
                        else:
                            color = np.array([0,0,0])
                    
                    pixelColor = pixelColor + color
            
            color = Color(pixelColor[0], pixelColor[1], pixelColor[2])
            color.gammaCorrect(2.2)
            img[y][x]=color.toUINT8()

    rawimg = Image.fromarray(img, 'RGB')
    rawimg.save('out.png')
    rawimg.save(sys.argv[1]+'.png')
    
if __name__=="__main__":
    main()