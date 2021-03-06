/*
Copyright (C) 2011 by Ivan Safrin

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
 

#pragma once
#include "PolyString.h"
#include "PolyGlobals.h"
#include "PolySceneEntity.h"
#include "PolyCoreServices.h"
#include "PolyScene.h"
#include "PolyCamera.h"
#include "PolyMesh.h"

namespace Polycode {

	class Scene;
	class Camera;
	
	/**
	* 3D light source. Lights can be area or spot lights and can be set to different colors. 
	*/
	class _PolyExport SceneLight : public SceneEntity {
		public:
		
			/**
			* Constructs a light with parameters.
			* @param type Type of light to create. Can be SceneLight::AREA_LIGHT or SceneLight::SPOT_LIGHT
			* @param parentScene Scene to light.
			* @param intensity Light color intensity
			* @param constantAttenuation Constant falloff attenuation value	
			* @param linearAttenuation Linear falloff attenuation value	
			* @param quadraticAttenuation Quadratic falloff attenuation value				
			*/ 
			SceneLight(int type, Scene *parentScene, Number intensity, Number constantAttenuation=1, Number linearAttenuation=1, Number quadraticAttenuation=1);
			virtual ~SceneLight();
		
			/*
			* Returns the light's intensity.
			*/
			Number getIntensity();
						
			Number getConstantAttenuation() { return constantAttenuation; }
			Number getLinearAttenuation() { return linearAttenuation; }
			Number getQuadraticAttenuation() { return quadraticAttenuation; }
									
			/*
			* Returns the light's type.
			*/			
			int getType();
			
			void renderDepthMap(Scene *scene);
			
			void Render();

			Matrix4 getLightViewMatrix();
			
			static const int AREA_LIGHT = 0;
			static const int SPOT_LIGHT = 1;
			
			Texture *getZBufferTexture();
			
			/**
			* Color of the light.
			*/ 
			Color lightColor;
		
			/**
			* Sets the light color.
			* @param r Red value 0-1.
			* @param g Green value 0-1
			* @param b Blue value 0-1
			* @param a Alpha value 0-1									
			*/	
			void setLightColor(Number r, Number g, Number b) { lightColor.r = r; lightColor.g = g; lightColor.b = b; }
			
			/**
			* Sets the spotlight properties. These control the shape of the spotlight beam.
			* @param spotlightExponent Spotlight exponent size
			* @param spotlightCutoff Spotlight furstrum cutoff.
			*/
			void setSpotlightProperties(Number spotlightCutoff, Number spotlightExponent) {
				this->spotlightCutoff = spotlightCutoff;
				this->spotlightExponent = spotlightExponent;				
			}
			
			Number getSpotlightCutoff() { return spotlightCutoff; }
			Number getSpotlightExponent() { return spotlightExponent; }
						
			
			/**
			* If this is called with 'true', the light will generate a shadow map.
			* @param val If set to true, enables this light to cast shadows.
			* @param resolution Resolution of the shadow map. (defaults to 256x256).
			*/
			void enableShadows(bool val, Number resolution=256);
			
			/**
			* This sets the shadow map field of view. The larger the field of view, the more of the scene it encompasses, but the more quality it loses.
			* @param fov New field of view value.
			*/
			void setShadowMapFOV(Number fov);
		
			/**
			* Returns true if shadows are enabled.
			*/
			bool areShadowsEnabled();
		
			/**
			* Returns the light type.
			*/
			int getLightType() { return type; }
		
		private:
		
			Number spotlightExponent;
			Number spotlightCutoff;
		
			Number constantAttenuation;
			Number linearAttenuation;
			Number quadraticAttenuation;
		
			int type;
			Number intensity;
			
			Camera *spotCamera;
			Texture *zBufferTexture;

			Scene *parentScene;
			
			Matrix4 lightViewMatrix;
		
			Number shadowMapRes;
			Number shadowMapFOV;	
			bool shadowsEnabled;
		
			Number distance;
			Mesh *lightMesh;
	};
}