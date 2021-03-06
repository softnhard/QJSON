/*************************************************************************
 * QJSON : A Qt5 like JSON library that can be used in Qt 4.8+
 * Copyright (C) 2012-2014  S.Mohammad M. Ziabary <mehran.m@aut.ac.ir>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *************************************************************************/
/**
 @author S.Mohammad M. Ziabary <mehran.m@aut.ac.ir>
 */

#if QT_VERSION >= 0x050000
    #include <QJsonDocument>
#else
/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/
**
** This file is part of the QtCore module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/
#ifndef QJSONDOCUMENT_H
#define QJSONDOCUMENT_H

#include "JSONValue.h"

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

class QDebug;

namespace QJsonPrivate {
    class Parser;
}

struct /*Q_JSONRPC_EXPORT*/ QJsonParseError
{
    enum ParseError {
        NoError = 0,
        UnterminatedObject,
        MissingNameSeparator,
        UnterminatedArray,
        MissingValueSeparator,
        IllegalValue,
        EndOfNumber,
        IllegalNumber,
        StringEscapeSequence,
        StringUTF8Scan,
        EndOfString,
        MissingObject
    };

    int        offset;
    ParseError error;
    QString    errorString() const;
};

class /*Q_JSONRPC_EXPORT*/ QJsonDocument
{
public:
#ifdef Q_LITTLE_ENDIAN
    static const uint BinaryFormatTag = ('q') | ('b' << 8) | ('j' << 16) | ('s' << 24);
#else
    static const uint BinaryFormatTag = ('q' << 24) | ('b' << 16) | ('j' << 8) | ('s');
#endif

    QJsonDocument();
    explicit QJsonDocument(const QJsonObject &object);
    explicit QJsonDocument(const QJsonArray &array);
    ~QJsonDocument();

    QJsonDocument(const QJsonDocument &other);
    QJsonDocument &operator =(const QJsonDocument &other);

    enum DataValidation {
        Validate,
        BypassValidation
    };

    static QJsonDocument fromRawData(const char *data, int size, DataValidation validation = Validate);
    const char *rawData(int *size) const;

    static QJsonDocument fromBinaryData(const QByteArray &data, DataValidation validation  = Validate);
    QByteArray toBinaryData() const;

    static QJsonDocument fromVariant(const QVariant &variant);
    QVariant toVariant() const;

    static QJsonDocument fromJson(const QByteArray &json, QJsonParseError *error = 0);
    QByteArray toJson() const;

    bool isEmpty() const;
    bool isArray() const;
    bool isObject() const;

    QJsonObject object() const;
    QJsonArray array() const;

    void setObject(const QJsonObject &object);
    void setArray(const QJsonArray &array);

    bool operator==(const QJsonDocument &other) const;
    bool operator!=(const QJsonDocument &other) const { return !(*this == other); }

    bool isNull() const;

private:
    friend class QJsonValue;
    friend class QJsonPrivate::Data;
    friend class QJsonPrivate::Parser;
    friend /*Q_JSONRPC_EXPORT*/ QDebug operator<<(QDebug, const QJsonDocument &);

    QJsonDocument(QJsonPrivate::Data *data);

    QJsonPrivate::Data *d;
};

#ifndef QT_NO_DEBUG_STREAM
/*Q_JSONRPC_EXPORT*/ QDebug operator<<(QDebug, const QJsonDocument &);
#endif

QT_END_NAMESPACE

QT_END_HEADER

#endif // QJSONDOCUMENT_H

#endif //QT_VERSION

