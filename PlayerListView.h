#ifndef PLAYERLISTVIEW_H
#define PLAYERLISTVIEW_H

#include "MVC.h"
#include <QTableWidget>
#include <QVBoxLayout>
#include "PlayerModel.h"

class PlayerListView : public View
{
    public:
        PlayerListView(PlayerModel *model);

        virtual void updateView() override;
        virtual void resizeEvent(QResizeEvent *event) override;

    private:
        QTableWidget *tableWidget;
        void createUI();
};

#endif // PLAYERLISTVIEW_H
