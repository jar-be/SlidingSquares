#ifndef CSQUARE_H
#define CSQUARE_H

#include <string>
#include "SlidingSquaresLib_global.h"

/**
 * \class CSquare
 * @brief The square - a piece of the sliding puzzle
 */
class SLIDINGSQUARESLIB_EXPORT CSquare
{
    int fId; //!< Unique id of the square
    std::string fDisplayName; //!< Display name of the square
    bool fIsEmpty; //!< Is this an empty square
public:
    /**
     * @brief CSquare constructor
     * @param id The id of the square
     * @param isEmpty Is this an empty square
     * @param diplayName The display name of the square
     */
    CSquare(int id, bool isEmpty, std::string diplayName);

    /**
     * @brief Get id
     * @return Id of the square
     */
    int Id() const
    {
        return fId;
    }

    /**
     * @brief Get display name
     * @return Display name of the square
     */
    std::string DisplayName() const
    {
        return fDisplayName;
    }

    /**
     * @brief Is this an empty square
     * @return Is this an empty square
     */
    bool IsEmpty() const
    {
        return fIsEmpty;
    }
};

#endif // CSQUARE_H
