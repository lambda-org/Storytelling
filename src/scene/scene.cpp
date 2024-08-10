#include "scene.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/System/String.hpp>
#include <fmt/core.h>
#include <iterator>
#include <memory>
#include <pugixml.hpp>
#include <spdlog/spdlog.h>
#include <tl/expected.hpp>
#include <utility>
#include <vector>

st::Scene::Scene(std::unique_ptr<pugi::xml_document> doc) :
	sceneDocument(std::move(doc)), sceneDialogs(std::make_unique<std::vector<std::string>>()) {
	spdlog::info("Parsing current scene data file");
	this->bufferTreeNode = sceneDocument->child("scene").child("tree");

	if (!this->bufferTreeNode) {
		spdlog::error("Missing 'tree' node in XML"); // !!! No exception !!!
		return;
	}

	this->treeActions = this->bufferTreeNode.attribute("actions").as_int();
	this->treeID	  = this->bufferTreeNode.attribute("id").as_int(-1);

	if (this->treeID == -1) {
		spdlog::error("Missing attribute 'id' at scene tree"); // !!! No exception !!!
		return;
	}

	if (this->treeActions == 0) {
		spdlog::warn("Tree ID {} is not optimized (missing 'actions' attribute)", treeID);
		this->treeActions = std::distance(this->bufferTreeNode.children("action").begin(), this->bufferTreeNode.children("action").end());
		spdlog::info("Counted {} actions", this->treeActions);
	}

	spdlog::debug("Preloading tree with {} actions", this->treeActions);

	for (pugi::xml_node node : this->bufferTreeNode.children("action")) {
		this->sceneDialogs->push_back(node.text().as_string());
	}
}

tl::expected<st::ActionData, st::SceneException> st::Scene::getActionData() {
	ActionData ret = {
		.currentString = this->sceneDialogs->at(this->actionID),
		.endOfScene	   = false
	};

	if (this->actionID >= this->treeActions - 1) {
		auto dialogs = preloadDialogs();

		if (!dialogs.has_value()) {
			spdlog::error("Error with scene ID {}", this->treeID);
			return tl::unexpected(dialogs.error());
		}

		ret.endOfScene = dialogs.value();
		return ret;
	}

	this->actionID += 1;

	return ret;
}

tl::expected<bool, st::SceneException> st::Scene::preloadDialogs() {
	spdlog::debug("Changing scene tree");
	this->bufferTreeNode = this->bufferTreeNode.next_sibling();

	if (!this->bufferTreeNode) {
		spdlog::debug("End of scene reached");
		return true;
	}

	this->treeID	  = this->bufferTreeNode.attribute("id").as_int(-1);
	this->treeActions = this->bufferTreeNode.attribute("actions").as_int(0);

	if (this->treeID == -1)
		return tl::unexpected(st::TreeIDNotSetException);

	if (this->treeActions == 0) {
		spdlog::warn("Tree ID {} is not optimized (missing 'actions' attribute)", this->treeID);
		this->treeActions = std::distance(this->bufferTreeNode.children("action").begin(), this->bufferTreeNode.children("action").end());
		spdlog::info("Counted {} actions", this->treeActions);
	}

	spdlog::debug("Preloading tree data");
	if (this->treeActions == 0)
		return tl::unexpected(st::EmptyTreeException);

	this->actionID = 0;
	this->sceneDialogs->clear();

	for (pugi::xml_node node : this->bufferTreeNode.children("action")) {
		this->sceneDialogs->push_back(node.text().as_string());
	}

	return false;
}
