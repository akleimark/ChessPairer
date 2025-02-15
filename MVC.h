#ifndef MVC_H
#define MVC_H

#include <QObject>
#include <QWidget>
#include <vector>

// Forward-deklarationer
class View;
class Model;

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
    Controller(Model *model, View *view);

protected:
    Model *model;   ///< Pekare till den associerade modellen.
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
    virtual void reset() = 0;

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
    Controller *controller;  ///< Pekare till den associerade controllern.
    Model *model;            ///< Pekare till den associerade modellen.
    const static QFont HEADER_FONT;
    const static QFont LABEL_FONT;
    const static QFont NORMAL_FONT;

public:
    /**
     * @brief Standardkonstruktor.
     *
     * Skapar en vy utan en tilldelad modell eller controller.
     */
    View() : controller(nullptr) {}

    /**
     * @brief Konstruktor som associerar en modell med vyn.
     *
     * @param model Pekare till modellen som används av vyn.
     */
    View(Model *model) : controller(nullptr), model(model) {}

    /**
     * @brief Uppdaterar vyn baserat på modellens data.
     *
     * Denna metod måste implementeras av underklasser.
     */
    virtual void updateView() const = 0;

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
