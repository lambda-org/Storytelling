#pragma once

#include <SFML/Window/Keyboard.hpp>
#include <memory>
#include <pugixml.hpp>
#include <string>
#include <tl/expected.hpp>
#include <vector>

namespace st {
	typedef struct {
		std::string currentString;
		bool endOfScene;
	} ActionData;

	enum SceneException {
		FileOpenException,
		EmptyTreeException,
		TreeIDNotSetException
	};

	class Scene {
	  private:
		std::unique_ptr<pugi::xml_document> sceneDocument;
		std::unique_ptr<std::vector<std::string>> sceneDialogs;
		pugi::xml_node bufferTreeNode;
		// pugi::xml_node bufferActionNode;
		int treeID	 = 0;
		int actionID = 0;
		int treeActions;

	  public:
		Scene(std::unique_ptr<pugi::xml_document> doc);
		tl::expected<ActionData, SceneException> getActionData();
		tl::expected<bool, st::SceneException> preloadDialogs();
		void setTreeID(int id);
		void setActionID(int id);
	};
}
