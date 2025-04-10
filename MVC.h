#ifndef MVC_H
#define MVC_H

#include <QObject>
#include <QWidget>
#include <vector>

// Forward-deklarationer
class View;
class Model;
class SettingsModel;
/**
 * @class Controller
 * @brief Hanterar kommunikationen mellan Model och View.
 *
 * Controller fungerar som en mellanhand som hanterar händelser från View och uppdaterar Model vid behov.
 */
class Controller : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Skapar en Controller-instans.
     *
     * @param model Pekare till modellen som ska hanteras.
     * @param view Pekare till vyn som ska hanteras.
     */
    Controller(Model &model, View *view);

protected:
    Model &model;   ///< Pekare till den associerade modellen.
    View *view;     ///< Pekare till den associerade vyn.
};

/**
 * @class Model
 * @brief Representerar applikationens data och logik.
 *
 * Model lagrar data och hanterar affärslogik. Den informerar också registrerade vyer om förändringar.
 */
class Model
{
public:
    /**
     * @brief Standardkonstruktor.
     */
    Model() {}

    /**
     * @brief Standarddestruktor.
     */
    virtual ~Model() {}

    /**
     * @brief Lägger till en vy som ska uppdateras vid förändringar i modellen.
     *
     * @param view Pekare till vyn som ska läggas till.
     */
    void addView(View* view) { views.push_back(view); }

    /**
     * @brief Informerar en specifik vy om att modellen har uppdaterats.
     *
     * @param view Pekare till vyn som ska uppdateras.
     */
    void notifyView(View *view);

    /**
     * @brief Informerar alla registrerade vyer om att modellen har uppdaterats.
     */
    void notifyAllViews();

protected:
    std::vector<View*> views;  ///< Lista över registrerade vyer.
};

/**
 * @class View
 * @brief Representerar användargränssnittet och visar data från modellen.
 *
 * View ansvarar för att visa information och tar emot användarinteraktioner som sedan vidarebefordras till Controller.
 */
class View : public QWidget
{
protected:
    Controller *controller;
    Model &model;
    /**
 * @brief Standardfonten som används för rubriker.
 *
 * Denna statiska `QFont` används för att definiera det förvalda typsnittet för rubriker i
 * användargränssnittet.
 */
    const static QFont DEFAULT_HEADER_FONT;

    /**
 * @brief Standardfonten som används för etiketter.
 *
 * Denna statiska `QFont` används för att definiera det förvalda typsnittet för etiketter
 * (labels) i användargränssnittet.
 */
    const static QFont DEFAULT_LABEL_FONT;

    /**
 * @brief Standardfonten som används för vanlig text.
 *
 * Denna statiska `QFont` används för att definiera typsnittet för vanlig text
 * i användargränssnittet.
 */
    const static QFont DEFAULT_NORMAL_FONT;

    virtual void resizeEvent(QResizeEvent *event) override
    {
        updateView();
        QWidget::resizeEvent(event);
    }

public:
    /**
     * @brief Standardkonstruktor.
     *
     * Skapar en vy utan en tilldelad modell eller controller.
     */


    /**
     * @brief Konstruktor som associerar en modell med vyn.
     *
     * @param model Pekare till modellen som används av vyn.
     */
    View(Model &model) : model(model), controller(nullptr) {}

    /**
     * @brief Uppdaterar vyn baserat på modellens data.
     *
     * Denna metod måste implementeras av underklasser.
     */
    virtual void updateView() = 0;

    /**
     * @brief Lägger till eventlyssnare för användarinteraktioner.
     *
     * Denna metod måste implementeras av underklasser.
     */
    virtual void addListeners() = 0;

    /**
     * @brief Kopplar en controller till vyn.
     *
     * @param controller Pekare till controllern som ska användas av vyn.
     */
    void setController(Controller *controller) { this->controller = controller; }
};

#endif // MVC_H
