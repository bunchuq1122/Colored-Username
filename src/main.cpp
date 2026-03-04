#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/GameManager.hpp>
#include <Geode/modify/LeaderboardsLayer.hpp>
#include <Geode/modify/GJScoreCell.hpp>
#include <Geode/modify/ProfilePage.hpp>
#include <Geode/modify/GJUserCell.hpp>
#include <Geode/modify/MenuLayer.hpp>

class $modify (coloredName, GJScoreCell) {
	void loadFromScore(GJUserScore* score) {
		GJScoreCell::loadFromScore(score);
		auto gm = GameManager::sharedState();
		ccColor3B col = gm->colorForIdx(score->m_color1);
		ccColor3B col2 = gm->colorForIdx(score->m_color2);

		auto mm = this->getChildByIDRecursive("main-menu");
		if(!mm) return;
		auto nick = mm->getChildByID("player-name");
		if(!nick) return;
		auto nickLabel = nick->getChildByType<CCLabelBMFont>(0);
		if(!nickLabel) return;

		nickLabel->setColor({col.r,col.g, col.b});
		nickLabel->setCascadeColorEnabled(true);

		// todo: Correcting yellow ig

		if (!Mod::get()->getSettingValue<bool>("mixcolor")) return;
		for (int i = 0; i < nickLabel->getChildrenCount()/2; i++) {
			auto letter = static_cast<CCSprite*>(nickLabel->getChildren()->objectAtIndex(i));

			letter->setColor({col2.r, col2.g, col2.b});
		}
		return;
	}
};

class $modify(coloredName2, ProfilePage) {
	void getUserInfoFinished(GJUserScore* score) {
		ProfilePage::getUserInfoFinished(score);
		auto gm = GameManager::sharedState();
		ccColor3B col = gm->colorForIdx(score->m_color1);
		ccColor3B col2 = gm->colorForIdx(score->m_color2);

		auto nickL = this->m_usernameLabel;
		if(!nickL) return;
		nickL->setColor({col.r,col.g,col.b});
		
		if (!Mod::get()->getSettingValue<bool>("mixcolor")) return;
		for (int i = 0; i < nickL->getChildrenCount()/2; i++) {
			auto letter = static_cast<CCSprite*>(nickL->getChildren()->objectAtIndex(i));
			if(!letter) return;

			letter->setColor({col2.r, col2.g,col2. b});
		}

		return;
	}
};

class $modify(coloredName3, GJUserCell) {
	void loadFromScore(GJUserScore* score) {
		GJUserCell::loadFromScore(score);
		auto gm = GameManager::sharedState();
		ccColor3B col = gm->colorForIdx(score->m_color1);
		ccColor3B col2 = gm->colorForIdx(score->m_color2);

		auto mm = this->getChildByIDRecursive("main-menu");
		if(!mm) return;
		auto nick = mm->getChildByID("player-name");
		if(!nick) return;
		auto nickLabel = nick->getChildByType<CCLabelBMFont>(0);
		if(!nickLabel) return;

		nickLabel->setColor({col.r,col.g, col.b});
		nickLabel->setCascadeColorEnabled(true);

		if (!Mod::get()->getSettingValue<bool>("mixcolor")) return;
		for (int i = 0; i < nickLabel->getChildrenCount()/2; i++) {
			auto letter = static_cast<CCSprite*>(nickLabel->getChildren()->objectAtIndex(i));

			letter->setColor({col2.r, col2.g, col2.b});
		}
		return;
	}
};

class $modify(coloredName4, MenuLayer) {
	bool init() {
		if (!MenuLayer::init()) return false;
		auto nick = static_cast<CCLabelBMFont*>(this->getChildByID("player-username"));
		if(!nick) return true;
		auto newNick = CCLabelBMFont::create(nick->getString(), "bigFont.fnt");
		newNick->setScale(0.35f);
		newNick->setContentSize(nick->getContentSize());
		newNick->setPosition({nick->getPosition()});
		newNick->setAlignment(CCTextAlignment::kCCTextAlignmentCenter);
		newNick->setAnchorPoint({0.5f,0.5f});
		newNick->setID(Mod::get()->getID() + "/custom-nick");
		
		auto gm = GameManager::sharedState();

		ccColor3B col = gm->colorForIdx(gm->getPlayerColor());
		ccColor3B col2 = gm->colorForIdx(gm->getPlayerColor2());
		newNick->setColor({col.r,col.g,col.b});
		
		if (Mod::get()->getSettingValue<bool>("mixcolor")) {
			for (int i = 0; i < newNick->getChildrenCount()/2; i++) {
				auto letter = static_cast<CCSprite*>(newNick->getChildren()->objectAtIndex(i));

				letter->setColor({col2.r, col2.g, col2.b});
			}
		}
		nick->removeFromParent();
		this->addChild(newNick);

		return true;
	}
};