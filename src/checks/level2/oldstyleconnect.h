/*
   This file is part of the clazy static checker.

  Copyright (C) 2015 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Sérgio Martins <sergio.martins@kdab.com>

  Copyright (C) 2015 Sergio Martins <smartins@kde.org>

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Library General Public
  License as published by the Free Software Foundation; either
  version 2 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Library General Public License for more details.

  You should have received a copy of the GNU Library General Public License
  along with this library; see the file COPYING.LIB.  If not, write to
  the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
  Boston, MA 02110-1301, USA.
*/

#ifndef OLD_STYLE_CONNECT_H
#define OLD_STYLE_CONNECT_H

#include "checkbase.h"

#if !defined(IS_OLD_CLANG)

namespace clang {
class CallExpr;
class CXXMemberCallExpr;
class Expr;
}

struct PrivateSlot
{
    typedef std::vector<PrivateSlot> List;
    std::string objName;
    std::string name;
};

/**
 * Finds usages of old-style Qt connect statements.
 *
 * See README-old-style-connect for more information.
 */
class OldStyleConnect : public CheckBase
{
public:
    OldStyleConnect(const std::string &name, const clang::CompilerInstance &ci);
    void VisitStmt(clang::Stmt *) override;
    void addPrivateSlot(const PrivateSlot &);
protected:
    void VisitMacroExpands(const clang::Token &macroNameTok, const clang::SourceRange &) override;
private:
    std::string signalOrSlotNameFromMacro(clang::SourceLocation macroLoc);
    std::vector<clang::FixItHint> fixits(int classification, clang::CallExpr *);
    bool isSignalOrSlot(clang::SourceLocation loc, std::string &macroName) const;
    int classifyConnect(clang::FunctionDecl *connectFunc, clang::CallExpr *connectCall);
    bool isQPointer(clang::Expr *expr) const;
    bool isPrivateSlot(const std::string &name) const;
    PrivateSlot::List m_privateSlots;
};

#endif
#endif
