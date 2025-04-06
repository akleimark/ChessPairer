#ifndef PLAYER_H
#define PLAYER_H

#include "Interfaces.h"
#include <QString>

/**
 * @class Player
 * @brief Representerar en schackspelare med namn, rating och FIDE-ID.
 *
 * Klassen Player används för att lagra information om en schackspelare, inklusive spelarens namn,
 * rating och unika FIDE-ID. Den tillhandahåller getter- och setter-metoder för dessa attribut.
 */
class Player : public ValidateInterface
{
public:


    /**
     * @brief Skapar en ny spelare.
     *
     * Konstruktorn skapar en ny instans av Player med angivet namn, rating och FIDE-ID.
     *
     * @param name Spelarens namn.
     * @param rating Spelarens rating.
     * @param fideId Spelarens unika FIDE-ID.
     */
    explicit Player(const unsigned int &fideId = 0, const QString &name = "", const unsigned int &rating = Player::MINIMUM_RATING)
        : name(name), rating(rating), fideId(fideId) {}

    /**
     * @brief Hämtar spelarens namn.
     *
     * Returnerar spelarens namn.
     *
     * @return QString Namnet på spelaren.
     */
    QString getName() const { return name; }

    /**
     * @brief Hämtar spelarens rating.
     *
     * Returnerar spelarens rating.
     *
     * @return unsigned int Ratingen för spelaren.
     */
    unsigned int getRating() const { return rating; }

    /**
     * @brief Hämtar spelarens FIDE-ID.
     *
     * Returnerar spelarens unika FIDE-ID.
     *
     * @return unsigned int Spelarens FIDE-ID.
     */
    unsigned int getFideId() const { return fideId; }

    /**
     * @brief Sätter spelarens namn.
     *
     * Uppdaterar spelarens namn.
     *
     * @param newName Det nya namnet för spelaren.
     */
    void setName(const QString &newName) { name = newName; }

    /**
     * @brief Sätter spelarens rating.
     *
     * Uppdaterar spelarens rating.
     *
     * @param newRating Det nya ratingvärdet för spelaren.
     */
    void setRating(const unsigned int &newRating) { rating = newRating; }

    /**
     * @brief Sätter spelarens FIDE-ID.
     *
     * Uppdaterar spelarens unika FIDE-ID.
     *
     * @param newFideId Det nya FIDE-ID:t för spelaren.
     */
    void setFideId(const unsigned int &newFideId) { fideId = newFideId; }

    const static unsigned int getMinimumRating() {return Player::MINIMUM_RATING; }
    const static unsigned int getMaximumRating() {return Player::MAXIMUM_RATING; }

    virtual bool isValid() const override;
    bool checkName() const;
    bool checkRating() const;
    bool checkFideId() const;

protected:
    unsigned int fideId; ///< Spelarens FIDE-ID.
    QString name; ///< Spelarens namn.
    unsigned int rating; ///< Spelarens rating.
    const static unsigned int MINIMUM_RATING;
    const static unsigned int MAXIMUM_RATING;
};

#endif // PLAYER_H
