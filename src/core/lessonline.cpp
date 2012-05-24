/*
 *  Copyright 2012  Sebastian Gottfried <sebastiangottfried@web.de>
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License as
 *  published by the Free Software Foundation; either version 2 of
 *  the License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "lessonline.h"

LessonLine::LessonLine(QObject* parent) :
    QObject(parent)
{
}

QString LessonLine::value() const
{
    return m_value;
}

void LessonLine::setValue(const QString& value)
{
    if(value != m_value)
    {
        m_value = value;
        emit valueChanged();
    }
}

void LessonLine::copyFrom(LessonLine* source)
{
    setValue(source->value());
}
