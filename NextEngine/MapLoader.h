#pragma once
#include "DrawableObject.h"
#include "SimpleObject.h"
#include "Transform.h"
#include <string>
#include <utility>
#include <vector>

using namespace std;

constexpr unsigned int DEFAULT_SIZE = 100;

class MapLoader {
	private:
		enum ObjectType {
			AIR = 0,
			GROUND,
			PLAYER,
			PHYSICS_OBJ,
			PROCESSED
		};

		struct ObjectProperty {
			ObjectProperty(ObjectType type, Transform transform, float width, float height);
			ObjectType type;
			Transform transform;
			float width;
			float height;
		};

		struct RawMapData {
			vector<vector<ObjectType>> data;
			vector<ObjectType>& operator[](int i);
			int size();
			void clear();
		};

		RawMapData rawMapData;
		vector<ObjectProperty> processedMapData;

		/// Helper functions ///
		void alignData(int length);
		pair<pair<int, int>, pair<int, int>> getObjectRange(int x, int y, ObjectType type);
		void markAsProcessed(int startX, int endX, int startY, int endY, ObjectType type);
		ObjectProperty getObjectProperty(int x, int y, ObjectType type);

	public:
		MapLoader();
		~MapLoader();
		void readData(string fileName);
		void loadDataToScene(list<DrawableObject*>& objectList, DrawableObject*& player);
		void appendDataToScene(list<DrawableObject*>& objectList, DrawableObject*& player);
		void offsetMap(list<DrawableObject*>& objectList, glm::vec3 offset);
		void offsetMapToCenter(list<DrawableObject*>& objectList);
		void clearData();
};