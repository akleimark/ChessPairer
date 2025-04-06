#ifndef INTERFACES_H
#define INTERFACES_H

/**
 * @interface PrintInterface
 * @brief Gränssnitt för klasser som stödjer utskrift av objektets innehåll.
 */
class PrintInterface
{
public:
    /**
     * @brief Virtuell destruktor för att säkerställa korrekt polymorfism.
     */
    virtual ~PrintInterface() = default;

    /**
     * @brief Skriver ut objektets innehåll.
     *
     * Denna metod måste implementeras av alla klasser som ärver från PrintInterface.
     */
    virtual void print() const = 0;
};

/**
 * @interface ResetInterface
 * @brief Gränssnitt för klasser som stödjer återställning av sitt tillstånd.
 */
class ResetInterface
{
public:
    /**
     * @brief Virtuell destruktor för att säkerställa korrekt polymorfism.
     */
    virtual ~ResetInterface() = default;

    /**
     * @brief Återställer objektets tillstånd till standardvärden.
     *
     * Denna metod måste implementeras av alla klasser som ärver från ResetInterface.
     */
    virtual void reset() = 0;
};

class ValidateInterface
{
public:

    virtual ~ValidateInterface() = default;
    virtual bool isValid() const = 0;
};

#endif // INTERFACES_H
