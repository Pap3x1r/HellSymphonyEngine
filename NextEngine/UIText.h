#pragma once
#include <GL/glew.h>
#include "GameEngine.h"
#include "SquareMeshVbo.h"
#include "DrawableObject.h"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include <SDL_ttf.h>
#include <SDL.h>
#include "imgui.h"

class UIText :public DrawableObject
{
private:
    string name;
    unsigned int texture;
    string text;
    SDL_Color color;
    int fontSize;
    float alpha = 1.0f;
    glm::vec3 textOffset = { 0.0f,0.0f,0.0f };
    float xPosition;
    float yPosition;
    float xScale;
    float yScale;

public:
    UIText(string name) {
        this->name = name;
        setTag(Tag::UI);
    }

    ~UIText() {}

    void render(glm::mat4 globalModelTransform) {
        SquareMeshVbo* squareMesh = dynamic_cast<SquareMeshVbo*>(
            GameEngine::getInstance()->getRenderer()->getMesh(SquareMeshVbo::MESH_NAME));

        GLuint modelMatrixId = GameEngine::getInstance()->getRenderer()->getModelMatrixAttrId();
        GLuint renderModeId = GameEngine::getInstance()->getRenderer()->getModeUniformId();
        GLuint colorId = GameEngine::getInstance()->getRenderer()->getColorUniformId();
        GLuint alphaOverrideId = GameEngine::getInstance()->getRenderer()->getAlphaOverrideUniformId();

        GLuint offsetXId = GameEngine::getInstance()->getRenderer()->getOffsetXUniformId();
        GLuint offsetYId = GameEngine::getInstance()->getRenderer()->getOffsetYUniformId();
        GLuint scaleXId = GameEngine::getInstance()->getRenderer()->getScaleXUniformId();
        GLuint scaleYId = GameEngine::getInstance()->getRenderer()->getScaleYUniformId();

        if (!squareMesh || modelMatrixId == -1 || renderModeId == -1) {
            std::cerr << "UIText render setup error" << std::endl;
            return;
        }

        // Enable transparency
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // Set uniforms
        glm::mat4 currentMatrix = transform.getTransformMat4();
        currentMatrix = glm::translate(currentMatrix, textOffset);
        currentMatrix = globalModelTransform * currentMatrix;

        glUniformMatrix4fv(modelMatrixId, 1, GL_FALSE, glm::value_ptr(currentMatrix));
        glUniform1i(renderModeId, 1);  // Textured render mode
        glUniform4f(colorId, 1.0f, 1.0f, 1.0f, 1.0f);  // Pure white color
        glUniform1f(alphaOverrideId, alpha);

        // Bind texture
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);

        // Render mesh
        squareMesh->render();
    }

    void update(float dt) {
        //cout << "Alpha: " << alpha << endl;
        //cout << "scale x: " << getColliderComponent()->getTransform().getScale().x << " scale y: " << getColliderComponent()->getTransform().getScale().y << endl;
        //offsetX = getTransform().getScale().x * 0.25f;
        //offsetY = -getTransform().getScale().y * 0.25f;
        //cout << "offsetX: " << offsetX << " offsetY: " << offsetY << endl;

        const char* stateNames[] = { "NONE", "MAIN", "OPTIONS", "AUDIO", "CONTROLS", "CREDITS", "IGNORE"};

        int stateIndex = static_cast<int>(getMenuState());

        glm::vec3 pos = getTransform().getPosition();
        xPosition = pos.x;
        yPosition = pos.y;

        glm::vec3 scale = getTransform().getScale();
        xScale = scale.x;
        yScale = scale.y;
    }

    void loadText(string text, SDL_Color textColor, int fontSize, bool bold = false) {
        this->text = text;
        this->color = textColor;
        this->fontSize = fontSize;
        //this->alpha = static_cast<float>(textColor.a) / 255.0f;

        TTF_Font* font = nullptr;

        if (bold) {
            font = TTF_OpenFont("../Resource/Font/EBGaramond-Bold.ttf", fontSize);
        }
        else {
            font = TTF_OpenFont("../Resource/Font/EBGaramond.ttf", fontSize);
        }

        if (!font) {
            cerr << "Failed to load font: " << TTF_GetError() << endl;
            return;
        }

        SDL_Surface* textSurface = TTF_RenderText_Blended(font, text.c_str(), textColor);
        if (!textSurface) {
            cerr << "Failed to render text: " << TTF_GetError() << endl;
            TTF_CloseFont(font);
            return;
        }

        int potW = 1;
        int potH = 1;
        while (potW < textSurface->w) potW <<= 1;
        while (potH < textSurface->h) potH <<= 1;

        SDL_Surface* potSurface = SDL_CreateRGBSurface(0, potW, potH, 32,
            0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

        if (!potSurface) {
            cerr << "Failed to create POT surface." << endl;
            SDL_FreeSurface(textSurface);
            TTF_CloseFont(font);
            return;
        }

        SDL_BlitSurface(textSurface, nullptr, potSurface, nullptr);

        if (texture != 0) {
            glDeleteTextures(1, &texture);
        }

        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1); 
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, potW, potH, 0, GL_RGBA, GL_UNSIGNED_BYTE, potSurface->pixels);

        glm::vec3 currentScale = getTransform().getScale();
        if (currentScale == glm::vec3(1.0f)) {
            float w = textSurface->w / 100.0f;
            float h = textSurface->h / 100.0f;
            this->getTransform().setScale(glm::vec3(w, h, 1.0f));
        }
        
        SDL_FreeSurface(textSurface);
        SDL_FreeSurface(potSurface);
        TTF_CloseFont(font);
    }

    void setText(const string& newText) {
        if (newText != text) {
            loadText(newText, color, fontSize);
        }
    }

    void setColor(const SDL_Color& newColor) {
        if (newColor.r != color.r || newColor.g != color.g || newColor.b != color.b || newColor.a != color.a) {
            loadText(text, newColor, fontSize);
        }
    }

    void setFont(const int& newSize) {
        if (newSize != fontSize) {
            loadText(text, color, newSize);
        }
    }

    void setAlpha(float newAlpha) override {
        alpha = newAlpha;
    }

    void setOffset(const glm::vec3& newVec) {
        textOffset = newVec;
    }
};
