#pragma once

#include "GameEngine.h"
#include "SquareMeshVbo.h"
#include "DrawableObject.h"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include <SDL_ttf.h>
#include <SDL.h>

class UIText :public DrawableObject
{
private:
    unsigned int texture;
    string text;
    SDL_Color color;
    int fontSize;
public:
    UIText() {
    }

    ~UIText() {}

    void render(glm::mat4 globalModelTransform) {
        SquareMeshVbo* squareMesh = dynamic_cast<SquareMeshVbo*>(
            GameEngine::getInstance()->getRenderer()->getMesh(SquareMeshVbo::MESH_NAME));

        GLuint modelMatrixId = GameEngine::getInstance()->getRenderer()->getModelMatrixAttrId();
        GLuint renderModeId = GameEngine::getInstance()->getRenderer()->getModeUniformId();
        GLuint colorId = GameEngine::getInstance()->getRenderer()->getColorUniformId();

        if (!squareMesh || modelMatrixId == -1 || renderModeId == -1) {
            std::cerr << "UIText render setup error" << std::endl;
            return;
        }

        // Enable transparency
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // Set uniforms
        glm::mat4 currentMatrix = globalModelTransform * this->getTransformMat4();
        glUniformMatrix4fv(modelMatrixId, 1, GL_FALSE, glm::value_ptr(currentMatrix));
        glUniform1i(renderModeId, 1);  // Textured render mode
        glUniform4f(colorId, 1.0f, 1.0f, 1.0f, 1.0f);  // Pure white color

        // Bind texture
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);

        // Render mesh
        squareMesh->render();
    }

    void update(float dt) {

    }

    void loadText(string text, SDL_Color textColor, int fontSize) {
        this->text = text;
        this->color = textColor;
        this->fontSize = fontSize;

        TTF_Font* font = TTF_OpenFont("../Resource/Font/DragonHunter.ttf", fontSize);
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

        float w = textSurface->w / 100.0f;
        float h = textSurface->h / 100.0f;
        this->getTransform().setScale(glm::vec3(w, h, 1.0f)); 

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
};
