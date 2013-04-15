/*
 * Copyright (C) 2013 Canonical, Ltd.
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 3, as published
 * by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef ACTION_MODEL_HPP_
#define ACTION_MODEL_HPP_

#include <QAbstractListModel>
#include <QSharedPointer>

#include "action.h"

struct ActionModelPrivate;

enum ActionsRoles {
    RoleLabel  = Qt::UserRole + 1,
    RoleAction = Qt::UserRole + 2
};

class ActionModel : public QAbstractListModel  {
	Q_OBJECT

public:
    ActionModel(QObject *parent=nullptr);
    virtual ~ActionModel();

    virtual int rowCount(const QModelIndex &index) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual QHash<int, QByteArray> roleNames() const;

    void insertAction(QSharedPointer<Action> action);

private:
    QScopedPointer<ActionModelPrivate> p;

};

#endif /* ACTION_MODEL_HPP_ */
