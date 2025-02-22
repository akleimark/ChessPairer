#include "SettingsView.h"
#include <QLabel>
#include "SettingsController.h"

SettingsView::SettingsView(SettingsModel *settingsModel):
    settingsModel(settingsModel)
{
    createUI();
}

void SettingsView::updateView() const
{
    fontComboBox->setCurrentFont(QFont(settingsModel->getSettingByType("font")));
}

void SettingsView::addListeners()
{
    SettingsController* settingsController = dynamic_cast<SettingsController*>(controller);
    connect(fontComboBox, &QFontComboBox::currentFontChanged, settingsController, &SettingsController::onFontChanged);
}

void SettingsView::createUI()
{
    const unsigned int SPACE_VALUE = 20;
    layout = new QVBoxLayout;
    setLayout(layout);

    QLabel *header = new QLabel("Inställningar");
    header->setFont(View::DEFAULT_HEADER_FONT);
    layout->addWidget(header);
    layout->addSpacing(SPACE_VALUE);

    QGridLayout *settingsLayout = new QGridLayout;
    QLabel *label1 = new QLabel("Typsnitt: ");
    label1->setFont(View::DEFAULT_LABEL_FONT);
    settingsLayout->addWidget(label1, 0, 0);

    fontComboBox = new QFontComboBox(this);
    settingsLayout->addWidget(fontComboBox, 0, 1);

    settingsLayout->setRowStretch(1, 1);
    layout->addLayout(settingsLayout);
}
