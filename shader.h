#pragma once

#include <GL/glew.h>
#include <stdio.h>
#include <glm/ext.hpp>
class Shader {

public:
   int  id()  { return program; }
   bool use() { glUseProgram(program); return(glGetError() == GL_NO_ERROR); }

   void setXform(const GLfloat *mvp) {
      glUniformMatrix4fv(MVPid, 1, GL_FALSE, mvp);
   }

   void setLightPos1(const GLfloat* lightpos){
      glUniform3fv(lightPosid1,1,lightpos);
   }
   
   void setLightPos2(const GLfloat* lightpos){
      glUniform3fv(lightPosid2,1,lightpos);
   }

   void setMVmatrix(const GLfloat * mv){
      glUniformMatrix4fv(MVid, 1, GL_FALSE, mv);
   }

   // void setMVinvmatrix(const GLfloat * mv){
   //    glUniformMatrix4fv(MVinvid, 1, GL_FALSE, mv);
   // }
   void setViewMatrix(const GLfloat * mv){
      glUniformMatrix4fv(Viewid,1,GL_FALSE,mv);
   }

   void setCameraPos(const GLfloat* camPos){
      glUniform3fv(cameraid,1,camPos);
   }
   void setDiffusion(const GLfloat diff){
      glUniform1f(diffuseId,diff);
   }
   void setShininess(const GLfloat shiniess){
      glUniform1f(shineId,shiniess);
   }
   void setSpecularCeoff(const GLfloat specCoef){
      glUniform1f(specCoeffid,specCoef);
   }
   void setLightIntensity1(const GLfloat* light1){
      glUniform3fv(lightIntensity1,1,light1);
   }
   void setLightIntensity2(const GLfloat* light2){
      glUniform3fv(lightIntensity2,1,light2);
   }

   void setClipPlane(const GLfloat * clipPlane){
      glUniform4fv(clipPlaneid, 1,clipPlane);
   }

   Shader(const char *vsfile=NULL, const char *fsfile=NULL);

protected:
   GLuint program;
   GLuint MVPid; // Every shader must have at least an MVP.
   GLuint MVid; // Every shader must have at least an MVP.
   GLuint Viewid;
   GLuint lightPosid1;
   GLuint lightPosid2;
   GLuint cameraid;
   GLuint diffuseId;
   GLuint shineId;
   GLuint specCoeffid;
   GLuint lightIntensity1;
   GLuint lightIntensity2;
   GLuint clipPlaneid;

   void defaults();
   void makeProgram(GLuint vs, GLint fs);
   virtual void getUniformIDs();
   GLuint vsFromsrc(char *vs_src, bool dofree=true);
   GLuint fsFromsrc(char *fs_src, bool dofree=true);
   void programFromsrc(char *vs_src, char *fs_src, bool dofree=true);
   void programFromfile(const char *vs_file, const char *fs_file);
};

