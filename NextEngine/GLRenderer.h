#ifndef GLRENDERER_H
#define GLRENDERER_H

#include <iostream>
#include <GL\glew.h>
#include "Shader.h"
#include <map>
#include <vector>
#include <string>
#include "MeshVbo.h"
#include "glm.hpp"
#include "DrawableObject.h"
#include "Camera.h"

using namespace std;

/**
 * @class GLRenderer
 * @brief Handles OpenGL-based rendering, including mesh drawing, shaders, viewport control, and camera logic.
 *
 * This class encapsulates OpenGL initialization, shader handling, orthographic projection setup,
 * texture caching, and rendering of 2D drawable objects using VBOs.
 */
class GLRenderer {
protected:
    int winWidth;
    int winHeight;
    glm::mat4 projectionMatrix;
    glm::mat4 modelMatrix;
    GLuint mMatrixId = -1;
    GLuint pMatrixId = -1;
    GLuint colorUniformId = -1;
    GLuint renderModeUniformId = -1;
    GLuint offsetXUniformId = -1;
    GLuint offsetYUniformId = -1;
    GLuint scaleXUniformId = -1;
    GLuint scaleYUniformId = -1;

    GLuint colorOverrideUniformId = -1;
    GLuint hitEffectStrengthUniformId = -1;
    GLuint alphaOverrideUniformId = -1;

    GLuint gProgramId;
    int gPos2DLocation;
    int gTex2DLocation;
    void printProgramLog(GLuint program);
    bool initialize(string vertexShaderFile, string fragmentShaderFile);
    Shader* vertexShader;
    Shader* fragmentShader;
    map <string, MeshVbo*> shapes;
    void setMeshAttribId(MeshVbo* shape);
    Camera camera;
    bool isViewportEnabled;
    float zoomRatio = 3;

    map<string, GLuint> textureCache;
public:
    /**
     * @brief Constructs a GLRenderer with the specified window size.
     * @param w Window width.
     * @param h Window height.
     */
    GLRenderer(int w, int h);

    /**
     * @brief Constructs a GLRenderer with a custom camera.
     * @param w Window width.
     * @param h Window height.
     * @param cam Camera object to use.
     */
    GLRenderer(int w, int h, const Camera& cam);

    /**
     * @brief Initializes OpenGL and loads the provided shaders.
     * @param vertexShaderFile Path to vertex shader.
     * @param fragmentShaderFile Path to fragment shader.
     * @return True if initialization is successful.
     */
    bool initGL(string vertexShaderFile, string fragmentShaderFile);

    /**
     * @brief Adds a mesh to the internal cache.
     * @param name Unique mesh name.
     * @param shape Pointer to MeshVbo.
     */
    void addMesh(string name, MeshVbo* shape);

    /**
     * @brief Gets a mesh by name.
     * @param name Name of the mesh.
     * @return Pointer to the mesh if found.
     */
    MeshVbo* getMesh(string name);

    /**
     * @brief Clears all loaded meshes.
     */
    void clearMesh();

    /**
     * @brief Destructor. Cleans up OpenGL resources.
     */
    ~GLRenderer();

    /**
     * @brief Increases zoom ratio for the camera view.
     * @param newRatio Amount to increase.
     */
    void increaseZoomRatio(float newRatio);

    /**
     * @brief Decreases zoom ratio for the camera view.
     * @param newRatio Amount to decrease.
     */
    void decreaseZoomRatio(float newRatio);

    /**
     * @brief Sets up orthographic projection.
     */
    void setOrthoProjection(float left, float right, float bottom, float top);

    /**
     * @brief Sets the OpenGL viewport.
     */
    void setViewPort(int x, int y, int w, int h);

    /**
     * @brief Sets the OpenGL clear (background) color.
     */
    void setClearColor(float r, float g, float b);

    // === Uniform Getters ===
    GLuint getModelMatrixAttrId();
    GLuint getProjectionMatrixAttrId();
    GLuint getColorUniformId();
    GLuint getModeUniformId();
    GLuint getOffsetXUniformId();
    GLuint getOffsetYUniformId();
    GLuint getScaleXUniformId();
    GLuint getScaleYUniformId();

    GLuint getColorOverrideUniformId();
    GLuint getHitEffectUniformId();
    GLuint getAlphaOverrideUniformId();

    /**
     * @brief Loads a texture from file and returns its OpenGL ID.
     */
    GLuint LoadTexture(string path);

    /**
     * @brief Sets a custom view matrix.
     */
    void setViewMatrix(const glm::mat4& viewMatrix);
    
    /**
     * @brief Enables or disables viewport rendering.
     */
    void toggleViewport(); 

    /**
     * @brief Updates the OpenGL viewport.
     */
    void updateViewport(); 

    /**
     * @brief Moves the camera to follow a target position.
     * @param playerPosition The position to follow.
     */
    void updateCamera(const glm::vec3& playerPosition);

    /**
     * @brief Applies the current camera view matrix.
     */
    void applyViewMatrix();

    /**
     * @brief Renders a list of drawable objects.
     */
    void render(list <DrawableObject*>& objList);

    /**
     * @brief Gets the current camera position.
     */
    glm::vec3 camPos();

    /**
     * @brief Draws a debug outline around the camera viewport.
     */
    void drawCameraOutline();
    
    /**
     * @brief Clears all cached textures.
     */
    void clearTextureCache();

    /**
     * @brief Preloads textures from file paths.
     */
    void preloadTextures(const vector<string>& texturePaths);

    /**
     * @brief Loads all textures from a directory.
     */
    void loadTextureFromDir(const std::string& dir);

    /**
     * @brief Finds a texture in the cache or loads it.
     */
    GLuint findTexture(const std::string path);

    /**
     * @brief Normalizes texture file paths (e.g., backslashes to slashes).
     */
    string normalizePath(const std::string& path);

    /**
     * @brief Returns the current texture cache.
     */
    map<string, GLuint> getTextureCache() const;
};

#endif