#include "Gui.h"

GUI::GUI() : buttons({}), score(NULL), health(NULL), result(NULL), musicBox(NULL), soundBox(NULL), life(NULL), logo(NULL)
{
}

void GUI::addButton(IGUIEnvironment *gui, ITexture *&texture, path name, const recti size, u32 id)
{
	size_t length = strlen(name.c_str()) + 1;
	wchar_t *text = new wchar_t[length];
	std::mbstowcs(text, name.c_str(), length);
	IGUIButton *button = gui->addButton(size, NULL, id, text);
	button->setImage(texture);

	buttons.push_back(button);
}

void GUI::setScore(const u32 newScore)
{
	std::wstring text = L"Score   ";
	text += std::to_wstring(newScore);

	score->setText(text.c_str());
}

void GUI::createLife(IGUIEnvironment *gui, IVideoDriver *drv) {
	life = gui->addImage(drv->getTexture("media/heart.png"), core::position2d<int>(10, 10));
}

void GUI::setHealth(const s32 newHealth)
{
	std::wstring text = std::to_wstring(newHealth);
	health->setText(text.c_str());
}

bool GUI::isButtonPressed(u32 id) const
{
	for (auto &i : buttons)
		if (i && i->getID() == id && i->isPressed())
			return true;

	return false;
}

s32 GUI::getMusicSelection() const
{
	if (musicBox)
		return musicBox->getItemData(musicBox->getSelected());
	return UNKNOWN;
}

s32 GUI::getSoundSelection() const
{
	if (soundBox)
		return soundBox->getItemData(soundBox->getSelected());
	return UNKNOWN;
}


void GUI::menu(IGUIEnvironment *gui, TextureManager *&manager, IVideoDriver *drv)
{
	drop();

	logo = gui->addImage(drv->getTexture("textures/poster.png"), core::position2d<int>(10, -65));

	addButton(gui, manager->getButtonsTexture()[0], "Start Game",
	{
		SINGLE_BUTTON_START_H,
		WINDOW_WIDTH / 2 + SCORE_HEALTH_WIDTH / 2 + BUTTON_MARGIN,
		SINGLE_BUTTON_START_H + BUTTON_WIDTH,
		WINDOW_WIDTH / 2 + SCORE_HEALTH_WIDTH / 2 + BUTTON_MARGIN + BUTTON_HEIGHT
	}, START_BUTTON);

	addButton(gui, manager->getButtonsTexture()[1], "Options",
	{
		SINGLE_BUTTON_START_H + BUTTON_WIDTH + BUTTON_MARGIN,
		WINDOW_WIDTH / 2 + SCORE_HEALTH_WIDTH / 2 + BUTTON_MARGIN,
		SINGLE_BUTTON_START_H + BUTTON_WIDTH * 2 + BUTTON_MARGIN,
		WINDOW_WIDTH / 2 + SCORE_HEALTH_WIDTH / 2 + BUTTON_MARGIN + BUTTON_HEIGHT
	}, OPTIONS_BUTTON);

	addButton(gui, manager->getButtonsTexture()[3], "Quit",
	{
		SINGLE_BUTTON_START_H + BUTTON_WIDTH * 2 + BUTTON_MARGIN * 2,
		WINDOW_WIDTH / 2 + SCORE_HEALTH_WIDTH / 2 + BUTTON_MARGIN,
		SINGLE_BUTTON_START_H + BUTTON_WIDTH * 3 + BUTTON_MARGIN * 2,
		WINDOW_WIDTH / 2 + SCORE_HEALTH_WIDTH / 2 + BUTTON_MARGIN + BUTTON_HEIGHT
	}, QUIT_BUTTON);
}

void GUI::options(IGUIEnvironment *gui, TextureManager *&manager)
{
	drop();

	musicBox = gui->addComboBox(
	{
		WINDOW_WIDTH / 2 - COMBOBOX_WIDTH / 2,
		WINDOW_HEIGHT / 2 - COMBOBOX_HEIGHT * 2 - COMBOBOX_MARGIN,
		WINDOW_WIDTH / 2 + COMBOBOX_WIDTH / 2,
		WINDOW_HEIGHT / 2 - COMBOBOX_HEIGHT - COMBOBOX_MARGIN,
	});

	soundBox = gui->addComboBox(
	{
		WINDOW_WIDTH / 2 - COMBOBOX_WIDTH / 2,
		WINDOW_HEIGHT / 2 - COMBOBOX_HEIGHT / 2,
		WINDOW_WIDTH / 2 + COMBOBOX_WIDTH / 2,
		WINDOW_HEIGHT / 2 + COMBOBOX_HEIGHT / 2 });

	musicBox->addItem(L"Enable music", MUSIC_ENABLE);
	musicBox->addItem(L"Disable Music", MUSIC_DISABLE);
	soundBox->addItem(L"Enable sound", SOUND_ENABLE);
	soundBox->addItem(L"Disable sound", SOUND_DISABLE);

	addButton(gui, manager->getButtonsTexture()[2], "Back",
	{
		TRIPLE_BUTTON_START_H,
		WINDOW_HEIGHT / 2 + COMBOBOX_HEIGHT / 2 + BUTTON_MARGIN,
		TRIPLE_BUTTON_START_H + BUTTON_WIDTH,
		WINDOW_HEIGHT / 2 + COMBOBOX_HEIGHT / 2 + BUTTON_MARGIN + BUTTON_HEIGHT
	}, BACK_BUTTON);
}

void GUI::pause(IGUIEnvironment *gui, TextureManager *&manager)
{
	drop(true, true);

	addButton(gui, manager->getButtonsTexture()[0], "Resume",
	{
		TRIPLE_BUTTON_START_H,
		TRIPLE_BUTTON_START_V,
		TRIPLE_BUTTON_START_H + BUTTON_WIDTH,
		TRIPLE_BUTTON_START_V + BUTTON_HEIGHT
	}, RESUME_BUTTON);

	addButton(gui, manager->getButtonsTexture()[2], "Back",
	{
		TRIPLE_BUTTON_START_H,
		TRIPLE_BUTTON_START_V + BUTTON_HEIGHT + BUTTON_MARGIN,
		TRIPLE_BUTTON_START_H + BUTTON_WIDTH,
		TRIPLE_BUTTON_START_V + BUTTON_HEIGHT * 2 + BUTTON_MARGIN
	}, BACK_BUTTON);

	addButton(gui, manager->getButtonsTexture()[3], "Quit",
	{
		TRIPLE_BUTTON_START_H,
		TRIPLE_BUTTON_START_V + BUTTON_HEIGHT * 2 + BUTTON_MARGIN * 2,
		TRIPLE_BUTTON_START_H + BUTTON_WIDTH,
		TRIPLE_BUTTON_START_V + BUTTON_HEIGHT * 3 + BUTTON_MARGIN * 2
	}, QUIT_BUTTON);
}

void GUI::game(IGUIEnvironment *gui, TextureManager *&manager, IVideoDriver *drv)
{
	drop(false, false); 

	life = gui->addImage(drv->getTexture("textures/heart.png"), core::position2d<int>(HEALTH_POSITION_H - 9, HEALTH_POSITION_V-10));

	score = gui->addStaticText(L"Score   was 0 but it shows nothing", { SCORE_POSITION_H, SCORE_POSITION_V, SCORE_POSITION_H + SCORE_HEALTH_WIDTH, SCORE_POSITION_V + SCORE_HEALTH_WIDTH });
	score->setOverrideColor(WHITE_COLOR);
	score->enableOverrideColor(true);

	health = gui->addStaticText(L"100", { HEALTH_POSITION_H, HEALTH_POSITION_V, HEALTH_POSITION_H + SCORE_HEALTH_WIDTH, HEALTH_POSITION_V + SCORE_HEALTH_HEIGHT });
	health->setOverrideColor(WHITE_COLOR);
	health->enableOverrideColor(true);
}

void GUI::win(IGUIEnvironment *gui, TextureManager *&manager)
{
	drop(true);

	result = gui->addStaticText(L"Good Work",
	{
		WINDOW_WIDTH / 2 - SCORE_HEALTH_WIDTH / 2,
		WINDOW_HEIGHT / 2 - SCORE_HEALTH_HEIGHT / 2 - TEXT_MARGIN - SCORE_HEALTH_HEIGHT,
		WINDOW_WIDTH / 2 + SCORE_HEALTH_WIDTH / 2,
		WINDOW_HEIGHT / 2 - SCORE_HEALTH_HEIGHT / 2 - TEXT_MARGIN
	});
	result->setOverrideColor(WHITE_COLOR);
	result->enableOverrideColor(true);

	score->setRelativePosition(
	{
		WINDOW_WIDTH / 2 - SCORE_HEALTH_WIDTH / 2,
		WINDOW_HEIGHT / 2 - SCORE_HEALTH_HEIGHT / 2,
		WINDOW_WIDTH / 2 + SCORE_HEALTH_WIDTH / 2,
		WINDOW_HEIGHT / 2 + SCORE_HEALTH_HEIGHT / 2
	});

	addButton(gui, manager->getButtonsTexture()[0], "Start Game",
	{
		SINGLE_BUTTON_START_H,
		WINDOW_WIDTH / 2 + SCORE_HEALTH_WIDTH / 2 + BUTTON_MARGIN,
		SINGLE_BUTTON_START_H + BUTTON_WIDTH,
		WINDOW_WIDTH / 2 + SCORE_HEALTH_WIDTH / 2 + BUTTON_MARGIN + BUTTON_HEIGHT
	}, START_BUTTON);

	addButton(gui, manager->getButtonsTexture()[2], "Back",
	{
		SINGLE_BUTTON_START_H + BUTTON_WIDTH + BUTTON_MARGIN,
		WINDOW_WIDTH / 2 + SCORE_HEALTH_WIDTH / 2 + BUTTON_MARGIN,
		SINGLE_BUTTON_START_H + BUTTON_WIDTH * 2 + BUTTON_MARGIN,
		WINDOW_WIDTH / 2 + SCORE_HEALTH_WIDTH / 2 + BUTTON_MARGIN + BUTTON_HEIGHT
	}, BACK_BUTTON);

	addButton(gui, manager->getButtonsTexture()[3], "Quit",
	{
		SINGLE_BUTTON_START_H + BUTTON_WIDTH * 2 + BUTTON_MARGIN * 2,
		WINDOW_WIDTH / 2 + SCORE_HEALTH_WIDTH / 2 + BUTTON_MARGIN,
		SINGLE_BUTTON_START_H + BUTTON_WIDTH * 3 + BUTTON_MARGIN * 2,
		WINDOW_WIDTH / 2 + SCORE_HEALTH_WIDTH / 2 + BUTTON_MARGIN + BUTTON_HEIGHT
	}, QUIT_BUTTON);
}

void GUI::lose(IGUIEnvironment *gui, TextureManager *&manager)
{
	drop(true);

	result = gui->addStaticText(L"Mission failed",
	{
		WINDOW_WIDTH / 2 - SCORE_HEALTH_WIDTH / 2,
		WINDOW_HEIGHT / 2 - SCORE_HEALTH_HEIGHT / 2 - TEXT_MARGIN - SCORE_HEALTH_HEIGHT,
		WINDOW_WIDTH / 2 + SCORE_HEALTH_WIDTH / 2,
		WINDOW_HEIGHT / 2 - SCORE_HEALTH_HEIGHT / 2 - TEXT_MARGIN
	});
	result->setOverrideColor(WHITE_COLOR);
	result->enableOverrideColor(true);

	score->setRelativePosition(
	{
		WINDOW_WIDTH / 2 - SCORE_HEALTH_WIDTH / 2,
		WINDOW_HEIGHT / 2 - SCORE_HEALTH_HEIGHT / 2,
		WINDOW_WIDTH / 2 + SCORE_HEALTH_WIDTH / 2,
		WINDOW_HEIGHT / 2 + SCORE_HEALTH_HEIGHT / 2
	});

	addButton(gui, manager->getButtonsTexture()[0], "Start Game",
	{
		SINGLE_BUTTON_START_H,
		WINDOW_WIDTH / 2 + SCORE_HEALTH_WIDTH / 2 + BUTTON_MARGIN,
		SINGLE_BUTTON_START_H + BUTTON_WIDTH,
		WINDOW_WIDTH / 2 + SCORE_HEALTH_WIDTH / 2 + BUTTON_MARGIN + BUTTON_HEIGHT
	}, START_BUTTON);

	addButton(gui, manager->getButtonsTexture()[2], "Back",
	{
		SINGLE_BUTTON_START_H + BUTTON_WIDTH + BUTTON_MARGIN,
		WINDOW_WIDTH / 2 + SCORE_HEALTH_WIDTH / 2 + BUTTON_MARGIN,
		SINGLE_BUTTON_START_H + BUTTON_WIDTH * 2 + BUTTON_MARGIN,
		WINDOW_WIDTH / 2 + SCORE_HEALTH_WIDTH / 2 + BUTTON_MARGIN + BUTTON_HEIGHT
	}, BACK_BUTTON);

	addButton(gui, manager->getButtonsTexture()[3], "Quit",
	{
		SINGLE_BUTTON_START_H + BUTTON_WIDTH * 2 + BUTTON_MARGIN * 2,
		WINDOW_WIDTH / 2 + SCORE_HEALTH_WIDTH / 2 + BUTTON_MARGIN,
		SINGLE_BUTTON_START_H + BUTTON_WIDTH * 3 + BUTTON_MARGIN * 2,
		WINDOW_WIDTH / 2 + SCORE_HEALTH_WIDTH / 2 + BUTTON_MARGIN + BUTTON_HEIGHT
	}, QUIT_BUTTON);
}

void GUI::drop(bool fScore, bool fHealth)
{
	for (auto &i : buttons)
	{
		if (i)
		{
			i->remove();
			i = NULL;
		}
	}
	buttons.clear();

	if (score && !fScore)
	{
		score->remove();
		score = NULL;
	}

	if (health && !fHealth)
	{
		health->remove();
		health = NULL;
	}

	if (life && !fHealth)
	{
		life->remove();
		life = NULL;
	}

	if (logo)
	{
		logo->remove();
		logo = NULL;
	}

	if (result)
	{
		result->remove();
		result = NULL;
	}

	if (musicBox)
	{
		musicBox->remove();
		musicBox = NULL;
	}

	if (soundBox)
	{
		soundBox->remove();
		soundBox = NULL;
	}

}