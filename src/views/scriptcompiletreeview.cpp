/*
** scriptcompiletreeview.cpp
**
** Copyright © Beyond Skyrim Development Team, 2017.
** This file is part of OPENCK (https://github.com/Beyond-Skyrim/openck)
**
** OpenCK is free software; this file may be used under the terms of the GNU
** General Public License version 3.0 or later as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.
**
** OpenCK is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
**
** Please review the following information to ensure the GNU General Public
** License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** You should have received a copy of the GNU General Public License version
** 3.0 along with OpenCK; if not, write to the Free Software Foundation,
** Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
**
** Created Date: 18-Jul-2017
*/

#include <views/scriptcompiletreeview.h>
#include <data/scriptmanagerdata.h>
#include <QDropEvent>
#include <QMimeData>
#include <QMenu>
#include <QProxyStyle>
#include <QPen>
#include <QPainter>
#include <QStyleOption>
#include <QDebug>

#include <qsortfilterproxymodel.h>

class ScriptCompileStyleProxy : public QProxyStyle
{
public:
    ScriptCompileStyleProxy(QStyle* style = Q_NULLPTR);

    virtual void drawPrimitive(QStyle::PrimitiveElement element, const QStyleOption* option, QPainter* painter, const QWidget* widget = Q_NULLPTR) const override;
};

ScriptCompileStyleProxy::ScriptCompileStyleProxy(QStyle* style)
    : QProxyStyle(style)
{
}

/**
* Proxy changes the default style of the drop indicator to a solid black underline.
* @brief Changes drop indicator style.
*/
void ScriptCompileStyleProxy::drawPrimitive(QStyle::PrimitiveElement element, const QStyleOption* option, QPainter* painter, const QWidget* widget) const
{
    if (element == QStyle::PE_IndicatorItemViewItemDrop && !option->rect.isNull()) {
        
        if (widget) {
            QStyleOption opt(*option);
            opt.rect.setLeft(0);

            QColor c(Qt::black);
            QPen pen(c);
            pen.setWidth(2);
            painter->setPen(pen);

            painter->drawLine(option->rect.bottomLeft(), option->rect.bottomRight());
        }
        return;
    }

    QProxyStyle::drawPrimitive(element, option, painter, widget);
}

ScriptCompileTreeView::ScriptCompileTreeView(QWidget* parent)
    : QTreeView(parent)
{
    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(showContextMenu(const QPoint&)));

    // Drag and Drop functionality.
    setDragEnabled(true);
    viewport()->setAcceptDrops(true);
    //setDropIndicatorShown(true);
    setDragDropMode(QAbstractItemView::InternalMove);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setDragDropOverwriteMode(false);

    // Set custom style. Overrides the horrible looking drop indicator.
    setStyle(new ScriptCompileStyleProxy(style()));
}

void ScriptCompileTreeView::initActions()
{

}

/**
* Shows context menu related to compiler queue items.
* @brief Show compiler context menu.
*/
void ScriptCompileTreeView::showContextMenu(const QPoint& pos)
{
    QMenu menu(tr(""), this);

    auto index = indexAt(pos);

    if (index.isValid()) {

        auto c = model()->index(index.row(), 2);
        model()->setData(c, static_cast<int>(ScriptStatus::NONE), Qt::UserRole);

    }

    menu.exec();
}

/**
* Sets the underlying model of this tree view with additional options for selection and drag-drop.
* @brief Sets underlying model.
*/
void ScriptCompileTreeView::setModel(QAbstractItemModel* model)
{
    QTreeView::setModel(model);
    setDragDropMode(QAbstractItemView::InternalMove);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setDragEnabled(true);
    viewport()->setAcceptDrops(true);
    setDragDropOverwriteMode(false);
}