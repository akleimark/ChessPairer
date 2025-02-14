#ifndef PLAYERLISTVIEW_H
#define PLAYERLISTVIEW_H

#include "MVC.h"
#include <QTableWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include "PlayerModel.h"

class PlayerListView : public View
{
    public:
        PlayerListView(PlayerModel *model);
        virtual void updateView() const override;
        virtual void addListeners() override;
        virtual void resizeEvent(QResizeEvent *event) override;

    private:
        QTableWidget *tableWidget;
        void createUI();
        QWidget *buttonWidget; // Widget som innehåller knappar
        QPushButton *addPlayerButton; // Knapp för att lägga till en spelare
};

#endif // PLAYERLISTVIEW_H
