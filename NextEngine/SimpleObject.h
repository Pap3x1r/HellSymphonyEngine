#pragma once

#include "DrawableObject.h"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

/**
 * @class SimpleObject
 * @brief A simple drawable object with color and transparency support.
 *
 * Extends DrawableObject to include color and alpha (transparency) properties.
 */
class SimpleObject :public DrawableObject {
	glm::vec3 color;
	float alpha = 1.0f; //Default alpha
public:
	/**
	 * @brief Default constructor.
	 * Initializes a SimpleObject with default settings.
	 */
	SimpleObject();

	/**
	 * @brief Constructor with a name.
	 * @param name The name identifier for the object.
	 */
	SimpleObject(string name);

	/**
	 * @brief Destructor.
	 */
	~SimpleObject();
    /**
     * @brief Sets the RGB color of the object.
     * @param r Red component (0.0 to 1.0).
     * @param g Green component (0.0 to 1.0).
     * @param b Blue component (0.0 to 1.0).
     */
    void setColor(float r, float g, float b);

    /**
     * @brief Renders the object with a given global transformation matrix.
     * @param globalModelTransform The global model transformation matrix.
     */
    void render(glm::mat4 globalModelTransform);

    /**
     * @brief Sets the alpha (transparency) value.
     * @param value Alpha value between 0.0 (fully transparent) and 1.0 (fully opaque).
     */
    void setAlpha(float value) {
        alpha = value;
    }

    /**
     * @brief Gets the current alpha (transparency) value.
     * @return The alpha value.
     */
    float getAlpha() const {
        return alpha;
    }
};

