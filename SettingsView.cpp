#include "SettingsView.h"
#include <QLabel>
#include "SettingsController.h"

SettingsView::SettingsView(SettingsModel *model):
    model(model)
{
    createUI();
}

void SettingsView::updateView() const
{
    qDebug() << model->getSettingByType("font");
    fontComboBox->setCurrentFont(QFont(model->getSettingByType("font")));
}

void SettingsView::addListeners()
{
    SettingsController* settingsController = dynamic_cast<SettingsController*>(controller);
    connect(fontComboBox, &QFontComboBox::currentFontChanged, settingsController, &SettingsController::onFontChanged);
}

void SettingsView::createUI()
{
    layout = new QVBoxLayout;
    setLayout(layout);

    QLabel *header = new QLabel("Inställningar");
    header->setFont(View::HEADER_FONT);
    layout->addWidget(header);
    layout->addSpacing(20); // Lägg till 20 pixlar mellan header och typsnitt

    QGridLayout *settingsLayout = new QGridLayout;
    QLabel *label1 = new QLabel("Typsnitt: ");
    label1->setFont(View::LABEL_FONT);
    settingsLayout->addWidget(label1, 0, 0);

    fontComboBox = new QFontComboBox(this);
    settingsLayout->addWidget(fontComboBox, 0, 1);

    settingsLayout->setRowStretch(1, 1);
    layout->addLayout(settingsLayout);
}
