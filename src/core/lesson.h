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

#ifndef LESSON_H
#define LESSON_H

#include <QObject>
#include <QString>
#include <QList>

class LessonLine;

class Lesson : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(QString characters READ characters WRITE setCharacters NOTIFY charactersChanged)
    Q_PROPERTY(int lineCount READ lineCount NOTIFY lineCountChanged)

public:
    explicit Lesson(QObject *parent = 0);
    QString id() const;
    void setId(const QString& id);
    QString title() const;
    void setTitle(const QString& title);
    QString characters() const;
    void setCharacters(const QString& characters);
    int lineCount() const;
    Q_INVOKABLE LessonLine* line(int index) const;
    Q_INVOKABLE void addLine(LessonLine* line);
    Q_INVOKABLE void removeLine(int index);
    Q_INVOKABLE void clearLines();
    Q_INVOKABLE void copyFrom(Lesson* source);

signals:
    void idChanged();
    void titleChanged();
    void charactersChanged();
    void lineCountChanged();

private:
    Q_DISABLE_COPY(Lesson)
    QString m_id;
    QString m_title;
    QString m_characters;
    QList<LessonLine*> m_lines;
};

#endif // LESSON_H
