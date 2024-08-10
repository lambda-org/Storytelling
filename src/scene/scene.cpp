#include "scene.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/System/String.hpp>
#include <fmt/core.h>
#include <iostream>
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
	bufferTreeNode = sceneDocument->child("scene").child("tree");

	if (!bufferTreeNode) {
		spdlog::error("Missing 'tree' node in XML"); // !!! No exception !!!
		return;
	}

	treeActions = bufferTreeNode.attribute("actions").as_int();

	if (treeActions == 0) {
		spdlog::warn("attribute 'actions' not set in first tree. Scene could be unoptimized");
	}

	spdlog::debug("Preloading tree with {} actions", treeActions);

	for (pugi::xml_node node : bufferTreeNode.children("action")) {
		sceneDialogs->push_back(node.text().as_string());
	}
}

tl::expected<st::ActionData, st::SceneException> st::Scene::getActionData(bool reverse) {
	ActionData ret = {
		.currentString = this->sceneDialogs->at(this->actionID),
		.endOfScene	   = false
	};

	if (this->actionID == this->treeActions - 1) {
		auto dialogs = preloadDialogs(reverse);

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

tl::expected<bool, st::SceneException> st::Scene::preloadDialogs(bool reverse) {
	if (reverse)
		bufferTreeNode = bufferTreeNode.next_sibling();
	else
		bufferTreeNode = bufferTreeNode.previous_sibling();

	if (!bufferTreeNode)
		return true;

	treeID = bufferTreeNode.attribute("actions").as_int(-1);

	if (treeID == -1) {
		return tl::unexpected(st::TreeIDNotSetException);
	}

	if (std::distance(bufferTreeNode.children("action").begin(), bufferTreeNode.children("action").end()) == 0)
		return tl::unexpected(st::EmptyTreeException);

	this->actionID = 0;
	sceneDialogs->clear();

	for (pugi::xml_node node : bufferTreeNode.children("action")) {
		sceneDialogs->push_back(node.text().as_string());
	}

	return false;
}
