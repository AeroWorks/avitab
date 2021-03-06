/*
 *   AviTab - Aviator's Virtual Tablet
 *   Copyright (C) 2018 Folke Will <folko@solhost.org>
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU Affero General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU Affero General Public License for more details.
 *
 *   You should have received a copy of the GNU Affero General Public License
 *   along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#include "src/Logger.h"
#include "AppLauncher.h"
#include "ChartsApp.h"
#include "NotesApp.h"
#include "About.h"
#include "PlaneManualApp.h"
#include "AirportApp.h"
#include "RouteApp.h"
#include "MapApp.h"
#include "src/libimg/Image.h"

namespace avitab {

AppLauncher::AppLauncher(FuncsPtr appFuncs):
    App(appFuncs)
{
    getUIContainer()->setLayoutPretty();
    std::string root = api().getDataPath() + "icons/";

    addEntry<ChartsApp>("Charts", root + "if_Airport_22906.png");
    addEntry<AirportApp>("Airports", root + "if_xmag_3617.png");
    addEntry<RouteApp>("Routes", root + "if_applications-internet_118835.png");
    addEntry<MapApp>("Maps", root + "if_starthere_18227.png");
    addEntry<PlaneManualApp>("Plane Manual", root + "if_ilustracoes_04-11_1519786.png");
    addEntry<NotesApp>("Notes", root + "if_txt2_3783.png");
    addEntry<About>("About", root + "if_Help_1493288.png");
}

void AppLauncher::show() {
    if (activeApp) {
        activeApp->suspend();
    }
    App::show();
}

template<typename T>
void AppLauncher::addEntry(const std::string& name, const std::string& icon) {
    auto app = startSubApp<T>();
    app->setOnExit([this] () {
        this->show();
    });

    img::Image iconImg;
    try {
        iconImg.loadImageFile(icon);
    } catch (const std::exception &e) {
        logger::warn("Couldn't load icon %s: %s", icon.c_str(), e.what());
    }

    Entry entry;
    entry.app = std::move(app);
    entry.button = std::make_shared<Button>(getUIContainer(), std::move(iconImg), name);
    entries.push_back(entry);

    size_t index = entries.size() - 1;
    entry.button->setCallback([this, index] (const Button &) {
        if (activeApp) {
            activeApp->suspend();
        }
        activeApp = entries[index].app;
        activeApp->resume();
        activeApp->show();
    });
}

void AppLauncher::onMouseWheel(int dir, int x, int y) {
    if (activeApp) {
        activeApp->onMouseWheel(dir, x, y);
    }
}

} /* namespace avitab */
