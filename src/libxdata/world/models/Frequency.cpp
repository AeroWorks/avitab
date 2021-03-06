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
#include "Frequency.h"

namespace xdata {

Frequency::Frequency(int frq, Unit unit, const std::string& desc):
    frequency(frq),
    unit(unit),
    description(desc)
{
}

const std::string& Frequency::getDescription() const {
    return description;
}

std::string Frequency::getFrequencyString() const {
    if (unit == Unit::MHZ) {
        int beforeDot = frequency / 100;
        int afterDot = frequency % 100;
        return std::to_string(beforeDot) + "." + std::to_string(afterDot) + " MHz";
    } else if (unit == Unit::KHZ) {
        return std::to_string(frequency) + " kHz";
    } else {
        return "<unit error>";
    }
}

Frequency::operator bool() const {
    return unit != Unit::NONE;
}

} /* namespace xdata */
