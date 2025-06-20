#include "MapLoader.h"
#include <cstdlib>
#include <fstream>
#include <iostream>

using namespace std;

MapLoader::ObjectProperty::ObjectProperty(ObjectType type, Transform transform, float width, float height) :
	type(type), transform(transform), width(width), height(height) {}

MapLoader::MapLoader() {}

MapLoader::~MapLoader() {
	clearData();
}

vector<MapLoader::ObjectType>& MapLoader::RawMapData::operator[](int i) {
	return data[data.size() - 1 - i];
}

int MapLoader::RawMapData::size() {
	return this->data.size();
}

void MapLoader::RawMapData::clear() {
	this->data.clear();
}

void MapLoader::alignData(int length) {
	for (vector<ObjectType>& slice : rawMapData.data) {
		while (slice.size() < length) {
			slice.emplace_back(AIR);
		}
	}
}

pair<pair<int, int>, pair<int, int>> MapLoader::getObjectRange(int x, int y, ObjectType type) {
	/// Assuming a rectangle object ///
	int size = rawMapData[y].size();
	int maxX = x;
	int minX = x;
	while (maxX + 1 < size && rawMapData[y][maxX + 1] == type) { // Check right until of different type
		maxX++;
	}
	while (minX - 1 >= 0 && rawMapData[y][minX - 1] == type) { // Check left until of different type
		minX--;
	}

	size = rawMapData.size();
	int maxY = y;
	int minY = y;
	while (maxY + 1 < size && rawMapData[maxY + 1][x] == type) { // Check up until of different type or mismatch horizontal length
		bool isValid = true;
		for (int i = x; i <= maxX; i++) {
			if (rawMapData[maxY + 1][i] != type) {
				isValid = false;
				break;
			}
		}
		if (!isValid) {
			break;
		}
		maxY++;
	}
	while (minY - 1 >= 0 && rawMapData[minY - 1][x] == type) { // Check down until of different type or mismatch horizontal length
		bool isValid = true;
		for (int i = x; i >= minX; i--) {
			if (rawMapData[minY - 1][i] != type) {
				isValid = false;
				break;
			}
		}
		if (!isValid) {
			break;
		}
		minY--;
	}

	return pair<pair<int, int>, pair<int, int>>(
		pair<int, int>(maxX + 1, minX), 
		pair<int, int>(maxY + 1, minY)
	);
}

void MapLoader::markAsProcessed(int startX, int endX, int startY, int endY, ObjectType type) {
	for (int y = startY; y < endY; y++) {
		for (int x = startX; x < endX; x++) {
			if (rawMapData[y][x] != PROCESSED && rawMapData[y][x] == type) {
				rawMapData[y][x] = PROCESSED;
			}
		}
	}
}

MapLoader::ObjectProperty MapLoader::getObjectProperty(int x, int y, ObjectType type) {
	/// Assuming a rectangular object ///
	pair<pair<int, int>, pair<int, int>> minMaxPair = getObjectRange(x, y, type);
	pair<int, int> xPair = minMaxPair.first;
	pair<int, int> yPair = minMaxPair.second;

	int xMax = xPair.first;
	int xMin = xPair.second;
	int yMax = yPair.first;
	int yMin = yPair.second;

	markAsProcessed(xMin, xMax, yMin, yMax, type);

	float width = xMax - xMin;
	float height = yMax - yMin;

	if (width <= 0.0f) {
		width = 1.0f;
	}
	if (height <= 0.0f) {
		height = 1.0f;
	}

	float posX = (float)(xMax + xMin) / 2.0f;
	float posY = (float)(yMax + yMin) / 2.0f;

	Transform transform;
	transform.setPosition(posX, posY);
	transform.setScale(width, height); // may need to remove after testing as object itself should not be scaled

	return ObjectProperty(type, transform, width, height);
}

void MapLoader::readData(string fileName) {
	string filePath = "../Resource/Map/" + fileName;
	ifstream file(filePath);

	if (!file) {
		cout << "Error reading file: " << fileName << endl;
		return;
	}

	clearData();

	string line;
	int maxLength = -1;
	while (!file.eof()) {
		if (!getline(file, line)) {
			break;
		}

		cout << "reading: " << line << endl;
		vector<ObjectType> slice;
		int length = 0;
		for (char c : line) {
			if ('0' <= c && c <= '9') {
				ObjectType type = (ObjectType)(c - '0');
				slice.emplace_back(type);
				length++;
			}
		}
		maxLength = max(maxLength, length);

		rawMapData.data.emplace_back(slice);
	}

	file.close();

	alignData(maxLength);

	for (int y = 0; y < rawMapData.size(); y++) {
		for (int x = 0; x < rawMapData[y].size(); x++) {
			if (rawMapData[y][x] == PROCESSED) {
				continue;
			}

			ObjectProperty obj = getObjectProperty(x, y, rawMapData[y][x]);
			processedMapData.emplace_back(obj);
		}
	}
}

void MapLoader::loadDataToScene(list<DrawableObject*>& objectList, DrawableObject*& player) {
	for (DrawableObject* obj : objectList) {
		delete obj;
	}
	objectList.clear();
	player = nullptr;
	for (ObjectProperty& objProperty : processedMapData) {
		cout << "obj: " << objProperty.type << " width: " << objProperty.width << " height: " << objProperty.height << " pos: " << objProperty.transform.getPosition().x << " " << objProperty.transform.getPosition().y << endl;
		DrawableObject* obj = nullptr;
		SimpleObject* sObj = nullptr;
		switch (objProperty.type) {
			case GROUND:
				obj = new SimpleObject("Ground");
				obj->getTransform() = objProperty.transform;
				obj->addColliderComponent();
				obj->getColliderComponent()->setDimension(1,1);
				//obj->getColliderComponent()->setDimension(objProperty.width, objProperty.height); // Add this instead of scaling the object
				sObj = dynamic_cast<SimpleObject*>(obj);
				if (sObj != NULL) {
					sObj->setColor(0.59, 0.3, 0.0); // for debug
				}
				obj->setDrawCollider(true);
				break;

			case PLAYER:
				obj = new SimpleObject("Player");
				obj->getTransform() = objProperty.transform;
				obj->addColliderComponent();
				obj->getColliderComponent()->setDimension(1,1);
				obj->addPhysicsComponent();
				//obj->getColliderComponent()->setDimension(objProperty.width, objProperty.height); // Add this instead of scaling the object
				sObj = dynamic_cast<SimpleObject*>(obj);
				if (sObj != NULL) {
					sObj->setColor(0.0, 1.0, 0.0); // for debug
					player = sObj;
				}
				obj->setDrawCollider(true);
				break;

			case PHYSICS_OBJ:
				obj = new SimpleObject("PhysicsObject");
				obj->getTransform() = objProperty.transform;
				obj->addColliderComponent();
				obj->getColliderComponent()->setDimension(1, 1);
				obj->addPhysicsComponent();
				//obj->getColliderComponent()->setDimension(objProperty.width, objProperty.height); // Add this instead of scaling the object
				sObj = dynamic_cast<SimpleObject*>(obj);
				if (sObj != NULL) {
					sObj->setColor(0.5, 0.5, 0.5); // for debug
				}
				obj->setDrawCollider(true);
				break;
		}
		if (obj != nullptr) {
			objectList.emplace_back(obj);
		}
	}

	if (player != nullptr) {
		cout << "player exists" << endl;
		glm::vec3 offset = player->getTransform().getPosition();
		offset = -offset;

		for (DrawableObject* obj : objectList) {
			obj->getTransform().translate(offset);

			if (obj == player) {
				cout << "move player" << endl;
			}
		}
	}

	cout << "Finished loading" << endl;
}

void MapLoader::appendDataToScene(list<DrawableObject*>& objectList, DrawableObject*& player) {
	bool skipPlayer = false;
	if (player != nullptr) {
		skipPlayer = true;
	}

	for (ObjectProperty& objProperty : processedMapData) {
		cout << "obj: " << objProperty.type << " width: " << objProperty.width << " height: " << objProperty.height << " pos: " << objProperty.transform.getPosition().x << " " << objProperty.transform.getPosition().y << endl;
		DrawableObject* obj = nullptr;
		SimpleObject* sObj = nullptr;
		switch (objProperty.type) {
		case GROUND:
			obj = new SimpleObject("Ground");
			obj->getTransform() = objProperty.transform;
			obj->addColliderComponent();
			obj->getColliderComponent()->setDimension(1, 1);
			//obj->getColliderComponent()->setDimension(objProperty.width, objProperty.height); // Add this instead of scaling the object
			sObj = dynamic_cast<SimpleObject*>(obj);
			if (sObj != NULL) {
				sObj->setColor(0.59, 0.3, 0.0); // for debug
			}
			obj->setDrawCollider(true);
			break;

		case PLAYER:
			if (skipPlayer) {
				break;
			}

			obj = new SimpleObject("Player");
			obj->getTransform() = objProperty.transform;
			obj->addColliderComponent();
			obj->getColliderComponent()->setDimension(1, 1);
			obj->addPhysicsComponent();
			//obj->getColliderComponent()->setDimension(objProperty.width, objProperty.height); // Add this instead of scaling the object
			sObj = dynamic_cast<SimpleObject*>(obj);
			if (sObj != NULL) {
				sObj->setColor(0.0, 1.0, 0.0); // for debug
				player = sObj;
			}
			obj->setDrawCollider(true);
			break;

		case PHYSICS_OBJ:
			obj = new SimpleObject("PhysicsObject");
			obj->getTransform() = objProperty.transform;
			obj->addColliderComponent();
			obj->getColliderComponent()->setDimension(1, 1);
			obj->addPhysicsComponent();
			//obj->getColliderComponent()->setDimension(objProperty.width, objProperty.height); // Add this instead of scaling the object
			sObj = dynamic_cast<SimpleObject*>(obj);
			if (sObj != NULL) {
				sObj->setColor(0.5, 0.5, 0.5); // for debug
			}
			obj->setDrawCollider(true);
			break;
		}
		if (obj != nullptr) {
			objectList.emplace_back(obj);
		}
	}

	cout << "Finished loading" << endl;
}

void MapLoader::offsetMap(list<DrawableObject*>& objectList, glm::vec3 offset) {
	for (DrawableObject* obj : objectList) {
		obj->getTransform().translate(offset);
	}
}

void MapLoader::offsetMapToCenter(list<DrawableObject*>& objectList) {
	int width = rawMapData[0].size();
	int height = rawMapData.size();
	glm::vec3 offset(width / 2.0f, height / 2.0f, 0.0f);
	cout << "width: " << width << " height: " << height << endl;
	offsetMap(objectList, -offset);
}

void MapLoader::clearData() {
	for (int i = 0; i < rawMapData.size(); i++) {
		rawMapData[i].clear();
	}
	rawMapData.clear();
	processedMapData.clear();
}